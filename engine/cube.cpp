/**
 * @file	cube.cpp
 * @brief	Cube mesh class implementation
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "cube.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "mesh.h"

using namespace lrvg;

/**
 * Creates a new instance of Cube with predefined mesh data.
 * The cube is centered at the origin with a size of 2 units (from -1 to 1) in each dimension.
 * 
 * @param segments Number of subdivisions per face side (default: 1)
 */
Cube::Cube(int segments) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces;
    auto generate_face = [&](glm::vec3 normal, glm::vec3 tangent, glm::vec3 bitangent, glm::vec3 origin) {
        uint32_t base_idx = vertices.size();
        for (int y = 0; y <= segments; y++) {
            for (int x = 0; x <= segments; x++) {
                float u = (float)x / segments;
                float v = (float)y / segments;
                glm::vec3 pos = origin + tangent * (u * 2.0f - 1.0f) + bitangent * (v * 2.0f - 1.0f);
                vertices.push_back(pos);
                normals.push_back(normal);
                uvs.push_back(glm::vec2(u, v));
            }
        }
        for (int y = 0; y < segments; y++) {
            for (int x = 0; x < segments; x++) {
                uint32_t i0 = base_idx + y * (segments + 1) + x;
                uint32_t i1 = i0 + 1;
                uint32_t i2 = i0 + (segments + 1);
                uint32_t i3 = i2 + 1;
                
                faces.push_back(std::make_tuple(i0, i1, i2));
                faces.push_back(std::make_tuple(i2, i1, i3));
            }
        }
    };
    // Front (+Z)
    generate_face(glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));
    // Back (-Z)
    generate_face(glm::vec3(0, 0, -1), glm::vec3(-1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));
    // Right (+X)
    generate_face(glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));
    // Left (-X)
    generate_face(glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0));
    // Top (+Y)
    generate_face(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
    // Bottom (-Y)
    generate_face(glm::vec3(0, -1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0));
    
    this->set_mesh_data(vertices, faces, normals, uvs);
    this->set_cast_shadows(true);
}
