/**
 * @file	spot_light.h
 * @brief	Spot light class definition
 *
 * This file contains the definition of the SpotLight class, which represents a spot light source in a 3D scene.
 * A spot light emits a cone of light in a specific direction, similar to a flashlight.
 * The SpotLight class inherits from the Light class and provides methods to set the light's direction
 * and properties such as cutoff angle, exponent, and radius.
 * It also includes a render method to apply the spotlight effect in the scene.
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
	 * @brief Spot light class.
	 */
	class ENG_API SpotLight : public Light {
	public:
		SpotLight();
		void set_cutoff(const float cutoff);
		void set_radius(const float radius);
		void set_exponent(const float exponent);
		void set_direction(const glm::vec3 direction);
		void render(const glm::mat4 world_matrix) const override;
	private:
		float cutoff;
		float radius;
		float exponent;
		glm::vec3 direction;
	};

}
