/**
 * @file	mesh.h
 * @brief	TODO:
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <memory>
#include <tuple>

#include "common.h"
#include "material.h"
#include "node.h"

namespace lrvg {

/**
 * @brief A mesh represents a shape renderable in the scene.
 */
class ENG_API Mesh : public Node {
public:
	Mesh();
    std::shared_ptr<Material> get_material() const;
    bool get_cast_shadows() const;
	void set_material(const std::shared_ptr<Material> material);
	void set_cast_shadows(const bool cast_shadows);
	void set_mesh_data(
		const std::vector<glm::vec3> vertices,
		const std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces,
		const std::vector<glm::vec3> normals,
		const std::vector<glm::vec2> uvs
	);
    void render(const glm::mat4 world_matrix) const override;
private:
	std::shared_ptr<Material> material;
	std::vector<glm::vec3> vertices;
	std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	bool cast_shadows;
};

}
