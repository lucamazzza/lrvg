#pragma once

#include <memory>
#include <tuple>

#include "common.h"
#include "material.h"
#include "node.h"

/**
 * @brief A mesh represents a shape renderable in the scene.
 */
class ENG_API Mesh : public Node {
public:
	Mesh();
	void render(const glm::mat4 world_matrix) const override;
	void set_material(const std::shared_ptr<Material> material);
	std::shared_ptr<Material> get_material() const;
	void set_cast_shadows(const bool cast_shadows);
	bool get_cast_shadows() const;
	void set_mesh_data(
		const std::vector<glm::vec3> vertices,
		const std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces,
		const std::vector<glm::vec3> normals,
		const std::vector<glm::vec2> uvs
	);
private:
	std::shared_ptr<Material> material;
	std::vector<glm::vec3> vertices;
	std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	bool cast_shadows;
};
