/**
 * @file	point_light.h
 * @brief	Point light class definition
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include "common.h"
#include "light.h"

namespace lrvg {

/**
 * @brief Point light class.
 */
class ENG_API PointLight : public Light {
public:
	PointLight();
	void set_radius(const float radius);
	void render(const glm::mat4 world_matrix) const override;
private:
	float radius;
};

}
