/**
 * @file	ortho_camera.h
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

/**
 * @brief Orthographic camera class.
 */
class ENG_API OrthoCamera : public Camera {
public:
	void set_zoom(float zoom);
	float get_zoom() const;
	void render(const glm::mat4 world_matrix) const override;
private:
	float zoom;
};
