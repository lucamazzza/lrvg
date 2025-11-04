/**
 * @file	ortho_camera.h
 * @brief	Orthographic camera class definition
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <glm/glm.hpp>

#include "common.h"
#include "camera.h"

namespace lrvg {

/**
 * @brief Orthographic camera class.
 */
class ENG_API OrthoCamera : public Camera {
public:
	float get_zoom() const;
    void set_zoom(float zoom);
	void render(const glm::mat4 world_matrix) const override;
private:
	float zoom;
};

}
