#pragma once

#include "common.h"
#include "mesh.h"

/**
 * @brief Cube mesh class.
 */
class ENG_API Cube : public Mesh {
public:
	void render(const glm::mat4 world_matrix) const override;
};
