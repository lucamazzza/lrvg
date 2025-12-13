/**
 * @file	perspective_camera.h
 * @brief	Perspective camera class definition
 *
 * This file contains the definition of the PerspectiveCamera class, which represents a perspective camera
 * in a 3D rendering engine. The PerspectiveCamera class inherits from the Camera base class
 * and provides methods to render the scene from a perspective viewpoint.
 * A perspective camera simulates the way the human eye sees the world,
 * with objects appearing smaller as they are farther from the camera.
 * This type of camera is commonly used in 3D games and simulations to provide a realistic
 * view of the scene.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
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
 *
 * A perspective camera simulates the way the human eye sees the world,
 * with objects appearing smaller as they are farther from the camera.
 * This type of camera is commonly used in 3D games and simulations to provide a realistic
 * view of the scene.
 * The PerspectiveCamera class inherits from the Camera base class and provides
 * methods to render the scene from a perspective viewpoint.
 *
 * @see Camera
 */
class ENG_API PerspectiveCamera : public Camera {
public:
	void render(const glm::mat4 world_matrix) const override;
};

}
