#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "common.h"
#include "node.h"

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
protected:
	float fov;
	float near_clipping;
	float far_clipping;
	int window_height;
	int window_width;
	bool is_active;
};