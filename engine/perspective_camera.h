#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "common.h"
#include "camera.h"

/**
 * @brief Perspective camera class.
 */
class ENG_API PerspectiveCamera : public Camera {
public:
	void render(const glm::mat4 world_matrix) const override;
};
