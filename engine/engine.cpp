#include "engine.h"

#include <algorithm>
#include <cstdio>
#include <memory>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <FreeImage.h>
#include <source_location>
#include <stb_easy_font.h>

#include "common.h"
#include "material.h"
#include "mesh.h"

bool LRVGEngine::is_initialized_f = false;
bool LRVGEngine::is_running_f = false;
int LRVGEngine::window_id = 0;
std::shared_ptr<Object> LRVGEngine::scene;
std::shared_ptr<Camera> LRVGEngine::active_camera;
std::string LRVGEngine::screen_text;
int LRVGEngine::window_width = 0;
int LRVGEngine::window_height = 0;
std::shared_ptr<Material> LRVGEngine::shadow_material = std::make_shared<Material>();

int LRVGEngine::frames = 0;
float LRVGEngine::fps = 0.0f;

static GLFWwindow* s_window = nullptr;
static double s_last_fps_time = 0.0;
static void (*s_keyboard_cb)(const unsigned char key, const int mouse_x, const int mouse_y) = nullptr;
static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#ifdef _WINDOWS
#include <Windows.h>
int APIENTRY DllMain(HANDLE instDLL, DWORD reason, LPVOID _reserved) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        break;
	case DLL_PROCESS_DETACH:
        break;
    }
    return true;
}
#endif

ENG_API LRVGEngine::~LRVGEngine() {
#ifdef _DEBUG
    DEBUG(std::source_location::current().function_name() << " invoked" << std::endl);
#endif
}

bool ENG_API LRVGEngine::init(const std::string window_title, const int width, const int height) {
   if (LRVGEngine::is_initialized_f) {
      ERROR("engine already initialized");
      return false;
   }
   if (!glfwInit()) {
       ERROR("Failed to initialize GLFW");
       return false;
   }
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
   glfwWindowHint(GLFW_DEPTH_BITS, 24);
   s_window = glfwCreateWindow(width, height, window_title.c_str(), nullptr, nullptr);
   if (!s_window) {
       ERROR("Failed to create GLFW window");
       glfwTerminate();
       return false;
   }
   glfwMakeContextCurrent(s_window);
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
       ERROR("Failed to initialize GLAD");
       glfwDestroyWindow(s_window);
       glfwTerminate();
       s_window = nullptr;
       return false;
   }
   int fbw, fbh;
   glfwGetFramebufferSize(s_window, &fbw, &fbh);
   LRVGEngine::window_width = fbw;
   LRVGEngine::window_height = fbh;
   glViewport(0, 0, fbw, fbh);
   glfwSetFramebufferSizeCallback(s_window, glfw_framebuffer_size_callback);
   glfwSetKeyCallback(s_window, glfw_key_callback);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnable(GL_CULL_FACE);
   glShadeModel(GL_SMOOTH);
   const glm::vec4 ambient(0.2f, 0.2f, 0.2f, 1.0f);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambient));
   glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
   FreeImage_Initialise();
   LRVGEngine::shadow_material->set_ambient_color(glm::vec3(0.0f, 0.0f, 0.0f));
   LRVGEngine::shadow_material->set_diffuse_color(glm::vec3(0.0f, 0.0f, 0.0f));
   LRVGEngine::shadow_material->set_specular_color(glm::vec3(0.0f, 0.0f, 0.0f));
   LRVGEngine::shadow_material->set_shininess(0.0f);
   DEBUG(LIB_NAME << " initialized");
   LRVGEngine::is_initialized_f = true;
   LRVGEngine::is_running_f = true;
   s_last_fps_time = glfwGetTime();
   LRVGEngine::frames = 0;
   LRVGEngine::fps = 0.0f;
   return true;
}

void ENG_API LRVGEngine::set_keyboard_callback(void (*new_keyboard_callback) (const unsigned char key, const int mouse_x, const int mouse_y)) {
    s_keyboard_cb = new_keyboard_callback;
    if (s_window) {
        glfwSetKeyCallback(s_window, glfw_key_callback);
    }
}

void ENG_API LRVGEngine::set_sky_color(const float red, const float green, const float blue) {
    glClearColor(red, green, blue, 1.0f);
}

bool ENG_API LRVGEngine::is_running() {
   if (!LRVGEngine::is_initialized_f) {
      ERROR("engine not initialized");
      return false;
   }
   glfwPollEvents();
   if (s_window && glfwWindowShouldClose(s_window)) {
       LRVGEngine::is_running_f = false;
   }
   return LRVGEngine::is_running_f;
}

bool ENG_API LRVGEngine::free() {
   if (!LRVGEngine::is_initialized_f) {
      ERROR("engine not initialized");
      return false;
   }
   FreeImage_DeInitialise();
   if (s_window) {
       glfwDestroyWindow(s_window);
       s_window = nullptr;
   }
   glfwTerminate();
   DEBUG(LIB_VERSION_STRING << 
#ifdef BUILD_DATE 
        BUILD_DATE <<
#endif 
        " deinitialized");
   LRVGEngine::is_initialized_f = false;
   LRVGEngine::is_running_f = false;
   return true;
}

void ENG_API LRVGEngine::render() {
    if (LRVGEngine::scene == nullptr || LRVGEngine::active_camera == nullptr) {
        ERROR("scene or active camera not set");
        return;
	}
	LRVGEngine::active_camera->set_window_size(LRVGEngine::window_width, LRVGEngine::window_height);
    int max_lights = 0;
	glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
	//DEBUG("Max lights: " << max_lights);
	for (int i = 0; i < max_lights; i++) {
	    glDisable(GL_LIGHT0 + i);
	}
    auto render_list = LRVGEngine::build_render_list(LRVGEngine::scene, glm::mat4(1.0f));
    if (LRVGEngine::active_camera) {
	    for (const auto& node : render_list) {
	        if (node.first == LRVGEngine::active_camera) {
	            LRVGEngine::active_camera->render(node.second);
	            break;
	        }
	    }
	}
	std::sort(render_list.begin(), render_list.end(), [](const std::pair<std::shared_ptr<Object>, glm::mat4>& a, const std::pair<std::shared_ptr<Object>, glm::mat4>& b) {
        return a.first->get_priority() < b.first->get_priority();
	});
	const glm::mat4 inv_camera_matrix = glm::inverse(LRVGEngine::active_camera->get_local_matrix());
    for (const auto& node : render_list) {
        if (node.first == LRVGEngine::active_camera) continue;
		node.first->render(inv_camera_matrix * node.second);
    }

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    const glm::mat4 shadow_model_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.05f, 1.0f));
    for (const auto& node : render_list) {
        std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(node.first);
        if (mesh != nullptr && mesh->get_cast_shadows()) {
            const std::shared_ptr<Material> original_material = mesh->get_material();
            mesh->set_material(LRVGEngine::shadow_material);
            const glm::mat4 shadow_matrix = shadow_model_scale_matrix * node.second;
            // Use same view * model approach for shadows
            mesh->render(inv_camera_matrix * shadow_matrix);
            mesh->set_material(original_material);
        }
    }
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    std::stringstream fps;
    fps << LRVGEngine::fps << " fps";
    LRVGEngine::draw_text_overlay(LRVGEngine::window_width, LRVGEngine::window_height, fps.str().c_str(), 10.0f, 15.0f, 0.0f, 1.0f, 0.0f);
    if (!LRVGEngine::screen_text.empty()) {
        LRVGEngine::draw_text_overlay(LRVGEngine::window_width, LRVGEngine::window_height, LRVGEngine::screen_text.c_str(), 16.0f, (float)(LRVGEngine::window_height - 50), 1.0f, 1.0f, 1.0f);
    }
    LRVGEngine::frames++;
}

void ENG_API LRVGEngine::timer_callback(int val) {
    (void)val; 
}

void ENG_API LRVGEngine::resize_callback(const int width, const int height) {
    LRVGEngine::window_width = width;
	LRVGEngine::window_height = height;
	DEBUG("Window resized to " << width << "x" << height);
    if (LRVGEngine::active_camera != nullptr) {
        LRVGEngine::active_camera->set_window_size(LRVGEngine::window_width, LRVGEngine::window_height);
	}
	glViewport(0, 0, width, height);
}

void ENG_API LRVGEngine::draw_text_overlay(int fb_width, int fb_height, const char *text, float x, float y, float r, float g, float b) {
    if (!text) return;
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
    glDisable(GL_LIGHTING);
    glColor3f(r, g, b);
    char buffer[99999];
    int num_quads = stb_easy_font_print((float)x, (float)y, (char*)text, NULL, buffer, sizeof(buffer));
    if (num_quads > 0) {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 16, buffer);
        glDrawArrays(GL_QUADS, 0, num_quads * 4);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

void ENG_API LRVGEngine::set_screen_text(const std::string text) {
    LRVGEngine::screen_text = text;
}

std::shared_ptr<Object> ENG_API LRVGEngine::get_scene() {
    return LRVGEngine::scene;
}

void ENG_API LRVGEngine::set_scene(const std::shared_ptr<Object> scene) {
    LRVGEngine::scene = scene;
	LRVGEngine::active_camera = nullptr;
}

void ENG_API LRVGEngine::set_active_camera(const std::shared_ptr<Camera> camera) {
    if (LRVGEngine::active_camera != nullptr) {
		LRVGEngine::active_camera->set_active(false);
    }
	camera->set_window_size(LRVGEngine::window_width, LRVGEngine::window_height);
	camera->set_active(true);
    LRVGEngine::active_camera = camera;
}

std::vector<std::pair<std::shared_ptr<Object>, glm::mat4>> LRVGEngine::build_render_list(const std::shared_ptr<Object> scene_root, const glm::mat4 parent_world_matrix) {
    std::vector<std::pair<std::shared_ptr<Object>, glm::mat4>> render_list;
    render_list.push_back(std::make_pair(scene_root, parent_world_matrix * scene_root->get_local_matrix()));
    for (const auto& child : scene_root->get_children()) {
		std::vector<std::pair<std::shared_ptr<Object>, glm::mat4>> child_render_list = LRVGEngine::build_render_list(child, parent_world_matrix * scene_root->get_local_matrix());
		render_list.insert(render_list.end(), child_render_list.begin(), child_render_list.end());
    }
    return render_list;
}

void ENG_API LRVGEngine::get_window_size(int &width, int &height) {
    width = LRVGEngine::window_width;
    height = LRVGEngine::window_height;
}

void ENG_API LRVGEngine::update() {
    if (!LRVGEngine::is_initialized_f) {
       ERROR("engine not initialized");
       return;
    }
    glfwPollEvents();
    double now = glfwGetTime();
    if (s_last_fps_time <= 0.0) s_last_fps_time = now;
    if (now - s_last_fps_time >= 1.0) {
        LRVGEngine::fps = (float)LRVGEngine::frames;
        LRVGEngine::frames = 0;
        s_last_fps_time = now;
        std::cout << "fps: " << LRVGEngine::fps << std::endl;
    }
}

void ENG_API LRVGEngine::clear_screen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ENG_API LRVGEngine::swap_buffers() {
    if (s_window) {
        glfwSwapBuffers(s_window);
    }
}

void ENG_API LRVGEngine::vsync_enable() {
    if (s_window) {
        glfwSwapInterval(1);
    }
}

void ENG_API LRVGEngine::stop() {
    LRVGEngine::is_running_f = false;
    if (s_window) glfwSetWindowShouldClose(s_window, GLFW_TRUE);
}

std::shared_ptr<Object> ENG_API LRVGEngine::find_obj_by_name(const std::string name) {
	const auto obj = LRVGEngine::find_obj_by_name(name, LRVGEngine::scene);
    if (obj == nullptr) {
        WARNING("object " << name << " not found");
	}
	return obj;
}

std::shared_ptr<Object> LRVGEngine::find_obj_by_name(const std::string name, const std::shared_ptr<Object> root) {
    for (const auto& child : root->get_children()) {
        if (child->get_name() == name) {
            return child;
        }
		const auto found = LRVGEngine::find_obj_by_name(name, child);
        if (found != nullptr) {
            return found;
		}
    }
	return nullptr;
}

static void glfw_framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
    LRVGEngine::resize_callback(width, height);
}

static void glfw_key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/) {
    if (action != GLFW_PRESS) return;
    if (!s_keyboard_cb) return;
    const char* name = glfwGetKeyName(key, 0);
    unsigned char ascii = (name && name[0]) ? (unsigned char)name[0] : (unsigned char)key;
    double xpos = 0.0, ypos = 0.0;
    if (s_window) glfwGetCursorPos(s_window, &xpos, &ypos);
    s_keyboard_cb(ascii, (int)xpos, (int)ypos);
}
