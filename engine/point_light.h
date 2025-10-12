#pragma once

#include "common.h"
#include "light.h"

/**
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
