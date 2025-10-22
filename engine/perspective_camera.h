/**
 * @file	perspective_camera.h
 * @brief	TODO:
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "common.h"
#include "camera.h"

namespace lrvg {

/**
 * @brief Perspective camera class.
 */
class ENG_API PerspectiveCamera : public Camera {
public:
	void render(const glm::mat4 world_matrix) const override;
};

}
