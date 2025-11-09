#include "engine.h"
#include "common.h"
#include "material.h"
#include "mesh.h"

#ifdef _WIN32
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}
#endif 

#include <algorithm>
#include <cstdio>
#include <memory>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <FreeImage/FreeImage.h>
#include <FreeImage/stb_easy_font.h>
#include <source_location>

using namespace lrvg;

bool Engine::is_initialized_f = false;
bool Engine::is_running_f = false;
int Engine::window_id = 0;
std::shared_ptr<Node> Engine::scene;
std::shared_ptr<Camera> Engine::active_camera;
std::string Engine::screen_text;
int Engine::window_width = 0;
int Engine::window_height = 0;
std::shared_ptr<Material> Engine::shadow_material = std::make_shared<Material>();

int Engine::frames = 0;
float Engine::fps = 0.0f;

static GLFWwindow* s_window = nullptr;
static double s_last_fps_time = 0.0;
static void (*s_keyboard_cb)(const unsigned char key, const int mouse_x, const int mouse_y) = nullptr;
static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

ENG_API Engine::~Engine() {
#ifndef NDEBUG
    DEBUG("%s invoked", std::source_location::current().function_name());
#endif
}

bool ENG_API Engine::init(const std::string window_title, const int width, const int height) {
   if (UNLIKELY(Engine::is_initialized_f)) {
      ERROR("engine already initialized");
      return false;
   }
   if (UNLIKELY(!glfwInit())) {
       ERROR("Failed to initialize GLFW");
       return false;
   }
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
   s_window = glfwCreateWindow(width, height, window_title.c_str(), nullptr, nullptr);
   if (UNLIKELY(!s_window)) {
       ERROR("Failed to create GLFW window");
       glfwTerminate();
       return false;
   }
   glfwMakeContextCurrent(s_window);
   if (!gladLoadGL(glfwGetProcAddress)) {
       ERROR("Failed to initialize GLAD");
       glfwDestroyWindow(s_window);
       glfwTerminate();
       s_window = nullptr;
       return false;
   }
   int fbw, fbh;
   glfwGetFramebufferSize(s_window, &fbw, &fbh);
   Engine::window_width = fbw;
   Engine::window_height = fbh;
   glViewport(0, 0, fbw, fbh);
   glfwSetFramebufferSizeCallback(s_window, glfw_framebuffer_size_callback);
   glfwSetKeyCallback(s_window, glfw_key_callback);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glEnable(GL_CULL_FACE);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
   const glm::vec4 ambient(0.2f, 0.2f, 0.2f, 1.0f);
   glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambient));
   FreeImage_Initialise();
   Engine::shadow_material->set_ambient_color(glm::vec3(0.0f, 0.0f, 0.0f));
   Engine::shadow_material->set_diffuse_color(glm::vec3(0.0f, 0.0f, 0.0f));
   Engine::shadow_material->set_specular_color(glm::vec3(0.0f, 0.0f, 0.0f));
   Engine::shadow_material->set_shininess(0.0f);
   DEBUG("%s initialized", LIB_NAME);
   Engine::is_initialized_f = true;
   Engine::is_running_f = true;
   s_last_fps_time = glfwGetTime();
   Engine::frames = 0;
   Engine::fps = 0.0f;
   return true;
}

void ENG_API Engine::set_keyboard_callback(void (*new_keyboard_callback) (const unsigned char key, const int mouse_x, const int mouse_y)) {
    s_keyboard_cb = new_keyboard_callback;
    if (LIKELY(s_window)) {
        glfwSetKeyCallback(s_window, glfw_key_callback);
    }
}

void ENG_API Engine::set_sky_color(const float red, const float green, const float blue) {
    glClearColor(red, green, blue, 1.0f);
}

bool ENG_API Engine::is_running() {
   if (UNLIKELY(!Engine::is_initialized_f)) {
      ERROR("engine not initialized");
      return false;
   }
   glfwPollEvents();
   if (s_window && glfwWindowShouldClose(s_window)) {
       Engine::is_running_f = false;
   }
   return Engine::is_running_f;
}

bool ENG_API Engine::free() {
   if (UNLIKELY(!Engine::is_initialized_f)) {
      ERROR("engine not initialized");
      return false;
   }
   FreeImage_DeInitialise();
   if (LIKELY(s_window)) {
       glfwDestroyWindow(s_window);
       s_window = nullptr;
   }
   glfwTerminate();
   DEBUG("%s.%d deinitialized", LIB_VERSION_STRING, BUILD_DATE);
   Engine::is_initialized_f = false;
   Engine::is_running_f = false;
   return true;
}

void ENG_API Engine::render() {
    if (UNLIKELY(Engine::scene == nullptr || Engine::active_camera == nullptr)) {
        ERROR("scene or active camera not set");
        return;
	}
	Engine::active_camera->set_window_size(Engine::window_width, Engine::window_height);
    int max_lights;
	glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
	for (int i = 0; i < max_lights; i++) {
	    glDisable(GL_LIGHT0 + i);
	}
    auto render_list = Engine::build_render_list(Engine::scene, glm::mat4(1.0f));
    std::sort(
        render_list.begin(),
        render_list.end(),
        [](
            const std::pair<std::shared_ptr<Object>, glm::mat4> a,
            const std::pair<std::shared_ptr<Object>, glm::mat4> b
        ) {
            return a.first->get_priority() > b.first->get_priority();
        }
    );
    const glm::mat4 inv_camera_matrix = glm::inverse(Engine::active_camera->get_local_matrix());
    for (const auto& node : render_list) {
        node.first->render(inv_camera_matrix * node.second);
    }
    glDepthFunc(GL_LEQUAL);
    const glm::mat4 shadow_model_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.05f, 1.0f));
    for (const auto& node : render_list) {
        std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(node.first);
        if (LIKELY(mesh != nullptr) && mesh->get_cast_shadows()) {
            const std::shared_ptr<Material> original_material = mesh->get_material();
            mesh->set_material(Engine::shadow_material);
            const glm::mat4 shadow_matrix = shadow_model_scale_matrix * node.second;
            mesh->render(inv_camera_matrix * shadow_matrix);
            mesh->set_material(original_material);
        }
    }
    glDepthFunc(GL_LESS);
    std::stringstream fps;
    fps << Engine::fps << " fps";
    Engine::draw_text_overlay(
            Engine::window_width, 
            Engine::window_height, 
            fps.str().c_str(), 
            10.0f, 
            1.0f,
            0.0f, 1.0f, 0.0f
    );
    if (Engine::screen_text.empty()) {
        Engine::draw_text_overlay(
                Engine::window_width, 
                Engine::window_height,
                Engine::screen_text.c_str(), 
                16.0f, 
                (float)(Engine::window_height - 50), 
                1.0f, 1.0f, 1.0f
        );
    }
    Engine::frames++;
}

void ENG_API Engine::timer_callback(int val) {
    (void)val; 
}

void ENG_API Engine::resize_callback(const int width, const int height) {
    Engine::window_width = width;
	Engine::window_height = height;
	DEBUG("Window resized to %dx%d", width, height);
    if (UNLIKELY(Engine::active_camera != nullptr)) {
        Engine::active_camera->set_window_size(Engine::window_width, Engine::window_height);
	}
	glViewport(0, 0, width, height);
}


void ENG_API Engine::draw_text_overlay(int fb_width, int fb_height, const char *text, float x, float y, float r, float g, float b) {
    if (UNLIKELY(!text)) return;
    static std::vector<char> vbuf(1 << 16);
    int num_quads = stb_easy_font_print((float)x, (float)y, (char*)text, NULL, vbuf.data(), (int)vbuf.size());
    if (UNLIKELY(num_quads <= 0)) return;
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glm::mat4 ortho = glm::ortho(0.0f, (float)fb_width, (float)fb_height, 0.0f, -1.0f, 1.0f);
    glLoadMatrixf(glm::value_ptr(ortho));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPixelZoom(1.0f, 1.0f);
    glColor3f(r, g, b);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, vbuf.data());
    glDrawArrays(GL_QUADS, 0, num_quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

void ENG_API Engine::set_screen_text(const std::string text) {
    Engine::screen_text = text;
}

std::shared_ptr<Node> ENG_API Engine::get_scene() {
    return Engine::scene;
}

void ENG_API Engine::set_scene(const std::shared_ptr<Node> scene) {
    Engine::scene = scene;
	Engine::active_camera = nullptr;
}

void ENG_API Engine::set_active_camera(const std::shared_ptr<Camera> camera) {
    if (Engine::active_camera != nullptr) {
		Engine::active_camera->set_active(false);
    }
	camera->set_window_size(Engine::window_width, Engine::window_height);
	camera->set_active(true);
    Engine::active_camera = camera;
}

std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> Engine::build_render_list(const std::shared_ptr<Node> scene_root, const glm::mat4 parent_world_matrix) {
    std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> render_list;
    render_list.push_back(std::make_pair(scene_root, parent_world_matrix * scene_root->get_local_matrix()));
    for (const auto& child : scene_root->get_children()) {
		std::vector<std::pair<std::shared_ptr<Node>, glm::mat4>> child_render_list = Engine::build_render_list(child, parent_world_matrix * scene_root->get_local_matrix());
		render_list.insert(render_list.end(), child_render_list.begin(), child_render_list.end());
    }
    return render_list;
}

void ENG_API Engine::get_window_size(int &width, int &height) {
    width = Engine::window_width;
    height = Engine::window_height;
}

void ENG_API Engine::update() {
    if (UNLIKELY(!Engine::is_initialized_f)) {
       ERROR("engine not initialized");
       return;
    }
    glfwPollEvents();
    double now = glfwGetTime();
    if (s_last_fps_time <= 0.0) s_last_fps_time = now;
    if (now - s_last_fps_time >= 1.0) {
        Engine::fps = (float)Engine::frames;
        Engine::frames = 0;
        s_last_fps_time = now;
    }
}

void ENG_API Engine::clear_screen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ENG_API Engine::swap_buffers() {
    if (LIKELY(s_window)) {
        glfwSwapBuffers(s_window);
    }
}

void ENG_API Engine::vsync_enable() {
    if (LIKELY(s_window)) {
        glfwSwapInterval(1);
    }
}

void ENG_API Engine::stop() {
    Engine::is_running_f = false;
    if (LIKELY(s_window)) glfwSetWindowShouldClose(s_window, GLFW_TRUE);
}

std::shared_ptr<Object> ENG_API Engine::find_obj_by_name(const std::string name) {
	const auto obj = Engine::find_obj_by_name(name, Engine::scene);
    if (obj == nullptr) {
        WARN("object %s not found", name.c_str());
	}
	return obj;
}

std::shared_ptr<Object> Engine::find_obj_by_name(const std::string name, const std::shared_ptr<Node> root) {
    for (const auto& child : root->get_children()) {
        if (child->get_name() == name) {
            return child;
        }
		const auto found = Engine::find_obj_by_name(name, child);
        if (found != nullptr) {
            return found;
		}
    }
	return nullptr;
}

static void glfw_framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
    Engine::resize_callback(width, height);
}

static void glfw_key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/) {
    if (UNLIKELY(action != GLFW_PRESS)) return;
    if (UNLIKELY(!s_keyboard_cb)) return;
    const char* name = glfwGetKeyName(key, 0);
    unsigned char ascii = (name && name[0]) ? (unsigned char)name[0] : (unsigned char)key;
    double xpos = 0.0, ypos = 0.0;
    if (LIKELY(s_window)) glfwGetCursorPos(s_window, &xpos, &ypos);
    s_keyboard_cb(ascii, (int)xpos, (int)ypos);
}
