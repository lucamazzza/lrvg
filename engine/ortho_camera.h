/**
 * @file	ortho_camera.h
 * @brief	Orthographic camera class definition
 *
 * This file contains the definition of the OrthoCamera class, which represents an orthographic camera
 * in a 3D rendering engine. An orthographic camera provides a parallel projection, where
 * objects maintain their size regardless of distance from the camera. This type of camera is commonly used
 * in 2D games, architectural visualization, and technical drawings.
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
 *
 * An orthographic camera provides a parallel projection, where objects maintain their size regardless of distance i
 * from the camera. This type of camera is commonly used in 2D games, architectural visualization, and technical 
 * drawings.
 * The OrthoCamera class inherits from the Camera base class and allows for setting the zoom level to control
 * the scale of the view. The class provides methods to get and set the zoom level, as well as to render the scene from 
 * the orthographic perspective.
 */
class ENG_API OrthoCamera : public Camera {
public:
	OrthoCamera();
	float get_zoom() const;
    void set_zoom(float zoom);
	void render(const glm::mat4 world_matrix) const override;
private:
	float zoom;
};

}
