/**
 * @file	engine.cpp
 * @brief	Graphics Engine main file
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "lrvg_engine.h"
 
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iostream>   
#include <source_location>

#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>
#include <FreeImage.h>

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

// Frames:
int LRVGEngine::frames = 0;
float LRVGEngine::fps = 0.0f;

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

/**
 * Destructor.
 */
ENG_API LRVGEngine::~LRVGEngine() {
#ifdef _DEBUG
    DEBUG(std::source_location::current().function_name() << " invoked" << std::endl);
#endif
}

/**
 * Init internal components. 
 * @return TF
 */
bool ENG_API LRVGEngine::init(const std::string window_title, const int window_width, const int window_height) {
   if (LRVGEngine::is_initialized_f) {
      ERROR("engine already initialized");
      return false;
   }
   // Init GLUT
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   int argc = 0;
   glutInit(&argc, nullptr);
   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
   LRVGEngine::window_id = glutCreateWindow(window_title.c_str());
   glutReshapeWindow(window_width, window_height);
   // Setup Callbacks
   glutDisplayFunc(render);
   glutReshapeFunc(resize_callback);
   glutTimerFunc(1000, timer_callback, 0);
   // OpenGL conf
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glEnable(GL_CULL_FACE);
   // Lighting conf
   const glm::vec4 ambient(0.2f, 0.2f, 0.2f, 1.0f);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambient));
   glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
   // FreeImage init
   FreeImage_Initialise();
   LRVGEngine::shadow_material->set_ambient_color(glm::vec3(0.0f, 0.0f, 0.0f));
   LRVGEngine::shadow_material->set_diffuse_color(glm::vec3(0.0f, 0.0f, 0.0f));
   LRVGEngine::shadow_material->set_specular_color(glm::vec3(0.0f, 0.0f, 0.0f));
   LRVGEngine::shadow_material->set_shininess(0.0f);
   DEBUG(LIB_NAME << " initialized");
   LRVGEngine::is_initialized_f = true;
   LRVGEngine::is_running_f = true;
   return true;
}

void ENG_API LRVGEngine::set_keyboard_callback(void (*new_keyboard_callback) (const unsigned char key, const int mouse_x, const int mouse_y)) {
    glutKeyboardFunc(new_keyboard_callback);
}

void ENG_API LRVGEngine::set_sky_color(const float red, const float green, const float blue) {
    glClearColor(red, green, blue, 1.0f);
}

bool ENG_API LRVGEngine::is_running() {
   if (!LRVGEngine::is_initialized_f) {
      ERROR("engine not initialized");
      return false;
   }
   glutMainLoopEvent();
   return LRVGEngine::is_running_f;
}

/**
 * Free internal components.
 * @return TF
 */
bool ENG_API LRVGEngine::free() {
   if (!LRVGEngine::is_initialized_f) {
      ERROR("engine not initialized");
      return false;
   }
   FreeImage_DeInitialise();
   glutLeaveMainLoop();
   DEBUG(LIB_NAME << " deinitialized");
   LRVGEngine::is_initialized_f = false;
   return true;
}

void ENG_API LRVGEngine::render() {
    if (LRVGEngine::scene == nullptr || LRVGEngine::active_camera == nullptr) {
        ERROR("scene or active camera not set");
        return;
	}
	LRVGEngine::active_camera->set_window_size(LRVGEngine::window_width, LRVGEngine::window_height);
    int max_lights;
	glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
	DEBUG("Max lights: " << max_lights);
    for (int i = 0; i < max_lights; i++) {
        glDisable(GL_LIGHT0 + i);
    }
	std::vector<std::pair<std::shared_ptr<Object>, glm::mat4>> render_list = LRVGEngine::build_render_list(LRVGEngine::scene, glm::mat4(1.0f));
    std::sort(render_list.begin(), render_list.end(), [](const std::pair<std::shared_ptr<Object>, glm::mat4> a, const std::pair<std::shared_ptr<Object>, glm::mat4> b) {
        return a.first->get_priority() < b.first->get_priority();
	});
	const glm::mat4 inv_camera_matrix = glm::inverse(LRVGEngine::active_camera->get_local_matrix());
    for (const auto& node : render_list) {
		node.first->render(inv_camera_matrix * node.second);
    }
    glDepthFunc(GL_LEQUAL);
    const glm::mat4 shadow_model_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.05f, 1.0f));
    for (const auto& node : render_list) {
		std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(node.first);
        if (mesh != nullptr && mesh->get_cast_shadows()) {
			const std::shared_ptr<Material> original_material = mesh->get_material();
            mesh->set_material(LRVGEngine::shadow_material);
            const glm::mat4 shadow_matrix = shadow_model_scale_matrix * node.second;
            mesh->render(inv_camera_matrix * shadow_matrix);
			mesh->set_material(original_material);
        }
    }
    glClear(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(glm::ortho(0.0f, (float)LRVGEngine::window_width, 0.0f, (float)LRVGEngine::window_height, -1.0f, 1.0f)));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(glm::mat4(1.0f)));
    glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(16.0f, 5.0f);
	std::string fps = "FPS: " + std::to_string((int)LRVGEngine::fps);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)fps.c_str());
    glEnable(GL_LIGHTING);
    LRVGEngine::frames++;
}

void ENG_API LRVGEngine::timer_callback(int val) {
    LRVGEngine::fps = LRVGEngine::frames;
    LRVGEngine::frames = 0;
    std::cout << "fps: " << LRVGEngine::fps << std::endl;
    glutTimerFunc(1000, timer_callback, 0);
}

void ENG_API LRVGEngine::resize_callback(const int height, const int width) {
    LRVGEngine::window_width = width;
	LRVGEngine::window_height = height;
	DEBUG("Window resized to " << width << "x" << height);
    if (LRVGEngine::active_camera != nullptr) {
        LRVGEngine::active_camera->set_window_size(LRVGEngine::window_width, LRVGEngine::window_height);
	}
	glViewport(0, 0, width, height);
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

void ENG_API LRVGEngine::update() {
	glutMainLoopEvent();
}

void ENG_API LRVGEngine::clear_screen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ENG_API LRVGEngine::swap_buffers() {
    glutSwapBuffers();
}

void ENG_API LRVGEngine::stop() {
    LRVGEngine::is_running_f = false;
}
