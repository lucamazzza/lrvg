/**
 * @file    lrvg_engine.h
 * @brief	Graphics engine main include file
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#define LIB_NAME            "LRVGEngine"
#define LIB_VERSION_MAJOR   "0"
#define LIB_VERSION_MINOR   "1"
#define LIB_VERSION_PATCH   "0"
#define LIB_VERSION_STRING  LIB_NAME " v" LIB_VERSION_MAJOR "." LIB_VERSION_MINOR "." LIB_VERSION_PATCH "."

#include <memory> 
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "common.h"
#include "object.h"
#include "camera.h"
#include "material.h"

/**
 * @brief Base engine main class. This class is a singleton.
 */
class ENG_API LRVGEngine final {
public: 
	LRVGEngine(LRVGEngine const &) = delete;
	~LRVGEngine();
	void operator=(LRVGEngine const &) = delete;
	static bool init(const std::string window_title, const int window_width, const int window_height);
	static void run();
	static void set_keyboard_callback(void(*keyboard_callback)(const unsigned char key, const int mouse_x, const int mouse_y));
	static void set_sky_color(const float red, const float green, const float blue);
	static bool is_running();
	static void render();
	static void timer_callback(int val);
	static void update();
	static void clear_screen();
	static void swap_buffers();
	static void stop();
	static void quit();
	static std::shared_ptr<Object> get_scene();
	static void set_scene(const std::shared_ptr<Object> scene);
	static void set_active_camera(const std::shared_ptr<Camera> camera);
	static std::shared_ptr<Object> find_obj_by_name(const std::string name);
	static void set_screen_text(const std::string text);
	static bool free();
    static void resize_callback(const int width, const int height);
    static void vsync_enable();
    static void draw_text_overlay(int fb_width, int fb_height, const char* text, float x, float y, float r = 1.0f, float g = 1.0f, float b = 1.0f);
    static void get_window_size(int& width, int& height);
private: 
	static std::vector<std::pair<std::shared_ptr<Object>, glm::mat4>> build_render_list(const std::shared_ptr<Object>, const glm::mat4 par_world_matrix);
	static std::shared_ptr<Object> find_obj_by_name(const std::string name, const std::shared_ptr<Object> root);
	static int window_id;
	static int window_width;
	static int window_height;
	static std::shared_ptr<Object> scene;
	static std::shared_ptr<Camera> active_camera;
	static std::shared_ptr<Material> shadow_material;
	static std::string screen_text;
	static int frames;
	static float fps;
	static bool is_initialized_f;
	static bool is_running_f;
	LRVGEngine();
};
