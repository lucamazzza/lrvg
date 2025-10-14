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
    std::cout << "[-] " << std::source_location::current().function_name() << " invoked" << std::endl;
#endif
}

/**
 * Init internal components. 
 * @return TF
 */
bool ENG_API LRVGEngine::init(const std::string window_title, const int window_width, const int window_height) {
   if (LRVGEngine::is_initialized_f)
   {
      ERROR("ERROR: engine already initialized");
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
   
   std::cout << "[>] " << LIB_NAME << " initialized" << std::endl;
   LRVGEngine::is_initialized_f = true;
   LRVGEngine::is_running_f = true;
   return true;
}

void LRVGEngine::run() {
    // Callback

    glutMainLoop();
}

bool ENG_API LRVGEngine::is_running() {
   if (!LRVGEngine::is_initialized_f)
   {
      std::cout << "ERROR: engine not initialized" << std::endl;
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
   if (!LRVGEngine::is_initialized_f)
   {
      std::cout << "ERROR: engine not initialized" << std::endl;
      return false;
   }
   // Here you can properly dispose of any allocated resource (including third-party dependencies)...

   // Done:
   std::cout << "[<] " << LIB_NAME << " deinitialized" << std::endl;
   LRVGEngine::is_initialized_f = false;
   return true;
}

void ENG_API LRVGEngine::render() {}

void ENG_API LRVGEngine::timer_callback(int val) {}

void ENG_API LRVGEngine::resize_callback(const int height, const int width) {}
