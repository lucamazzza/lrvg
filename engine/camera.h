/**
 * @file	camera.h
 * @brief	Camera node class definition
 *
 * This file contains the definition of the Camera class, which represents a camera node in a 3D scene graph.
 * A camera defines the point of view from which the scene is rendered.
 * The Camera class provides methods to set the field of view (FOV), clipping planes,
 * window size, and active state of the camera.
 * It also defines a method to retrieve the rendering priority of the camera.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <glm/glm.hpp>

#include "common.h"
#include "node.h"

namespace lrvg {

/**
 * @brief Camera node base class. A camera defines the point of view from which the scene is rendered.
 *
 * The Camera class is an abstract base class that inherits from Node.
 * It provides common functionality for different types of cameras, such as perspective and orthographic cameras.
 * The class manages properties like field of view (FOV), clipping planes, window size,
 * and active state. It also defines a pure virtual render method that must be implemented by derived classes.
 * Cameras are essential for rendering scenes from specific viewpoints in 3D graphics applications.
 *
 * @see Node
 */
class ENG_API Camera : public Node {
public:
	Camera();
    virtual ~Camera() = default;
	int get_priority() const override;
	void set_window_size(const int width, const int height);
	void set_fov(const float fov);
	void set_clipping(const float near_clipping, const float far_clipping);
	void set_active(const bool is_active);
    virtual void render(const glm::mat4 world_matrix) const override = 0;
protected:
	float fov;
	float near_clipping;
	float far_clipping;
	int window_height;
	int window_width;
	bool is_active;
};

}
