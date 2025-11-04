/**
 * @file	directional_light.h
 * @brief	Directional light class definition
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <glm/glm.hpp>

#include "common.h"
#include "light.h"

namespace lrvg {

class ENG_API DirectionalLight : public Light {
public:
	DirectionalLight();
	void set_direction(const glm::vec3 direction);
	void render(const glm::mat4 world_matrix) const override;
private:
	glm::vec3 direction;
};

}
