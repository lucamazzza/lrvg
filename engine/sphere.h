#pragma once

#include "common.h"
#include "mesh.h"

/**
 * @brief Sphere mesh class.
 */
class ENG_API Sphere : public Mesh {
public:
	void render(const glm::mat4 world_matrix) const override;
};
