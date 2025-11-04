/**
 * @file	camera.h
 * @brief	Camera node class definition
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
 */
class ENG_API Camera : public Node {
public:
	Camera();
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
