/**
 * @file	camera.cpp
 * @brief	Camera node class implementation
 * 
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "camera.h"

#include "common.h"

using namespace lrvg;

/**
 * Creates a new instance of Camera with default parameters.
 * 
 * Default parameters:
 * * Field of View (FOV): 90.0 degrees
 * * Near Clipping Plane: 0.01 units
 * * Far Clipping Plane: 1000.0 units
 */
ENG_API Camera::Camera() {
	this->set_fov(90.0f);
	this->set_clipping(0.01f, 1000.0f);
	this->is_active = false;
	this->set_window_size(0, 0);
}

/**
 * Retrieves the priority of the camera for rendering order.
 * Cameras have a very high priority to ensure they are processed before most other objects (200).
 * 
 * @return An integer representing the priority of the camera.
 */
int ENG_API Camera::get_priority() const {
	return 200; // Cameras have very high priority
}

/**
 * Sets the dimensions of the rendering window.
 * 
 * This method is automatically called by the engine when the window is resized.
 * 
 * @param width The width of the window in pixels.
 * @param height The height of the window in pixels.
 */
void ENG_API Camera::set_window_size(const int width, const int height) {
	this->window_width = width;
	this->window_height = height;
}

/**
 * Sets the field of view (FOV) of the camera in degrees.
 * 
 * @param fov The field of view angle in degrees.
 */
void ENG_API Camera::set_fov(const float fov) {
	this->fov = fov;
}

/**
 * Sets the near and far clipping planes of the camera.
 * 
 * Objects closer than the near clipping plane or farther than the far clipping plane will not be rendered.
 * 
 * @param near_clipping The distance to the near clipping plane.
 * @param far_clipping The distance to the far clipping plane.
 */
void ENG_API Camera::set_clipping(const float near_clipping, const float far_clipping) {
	this->near_clipping = near_clipping;
	this->far_clipping = far_clipping;
}

/**
 * Sets whether the camera is active.
 * An active camera is used for rendering the scene.
 * 
 * @param is_active A boolean indicating if the camera should be active.
 */
void ENG_API Camera::set_active(const bool is_active) {
	this->is_active = is_active;
}
