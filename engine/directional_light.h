#pragma once

#include <glm/glm.hpp>

#include "common.h"
#include "light.h"

class ENG_API DirectionalLight : public Light {
public:
	DirectionalLight();
	void set_direction(const glm::mat4 world_matrix);
	void render(const glm::mat4 world_matrix) const override;
private:
	glm::vec3 direction;
};
