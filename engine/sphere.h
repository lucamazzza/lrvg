/**
 * @file	sphere.h
 * @brief	Sphere mesh class definition
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include "common.h"
#include "mesh.h"

namespace lrvg {

/**
 * @brief Sphere mesh class.
 */
class ENG_API Sphere : public Mesh {
public:
    Sphere(int lat_segments = 20, int lon_segments = 20);
	void render(const glm::mat4 world_matrix) const override;
};

}
