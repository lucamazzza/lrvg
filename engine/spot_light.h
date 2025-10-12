#pragma once

#include "common.h"
#include "light.h"

/**
 * @brief Spot light class.
 */
class ENG_API SpotLight : public Light {
public:
	SpotLight();
	void set_cutoff(const float cutoff);
	void set_radius(const float radius);
	void set_exponent(const float exponent);
	void set_direction(const glm::mat4 world_matrix);
	void render(const glm::mat4 world_matrix) const override;
private:
	float cutoff;
	float radius;
	float exponent;
	glm::vec3 direction;
};
