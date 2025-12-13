/**
 * @file	mesh.h
 * @brief	Mesh class definition
 *
 * This file contains the definition of the Mesh class, which represents a 3D mesh
 * in a rendering engine. The Mesh class allows setting and retrieving the material,
 * mesh data (vertices, faces, normals, UVs), and rendering the mesh using OpenGL.
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include "common.h"
#include "material.h"
#include "node.h"

#include <memory>
#include <tuple>

namespace lrvg {

/**
 * @brief Mesh class representing a 3D mesh object.
 *
 * The Mesh class inherits from the Node class and represents a 3D mesh object in the scene.
 * It allows setting and retrieving the material, mesh data (vertices, faces, normals, UVs),
 * and rendering the mesh using OpenGL. The class also provides functionality to enable or disable
 * shadow casting for the mesh.
 *
 * @see Node
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
