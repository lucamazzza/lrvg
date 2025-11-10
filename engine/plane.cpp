/**
 * @fileplane.cpp
 * @briefPlane mesh class implementation
 *
 * @authorLuca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @authorRoeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @authorVasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "plane.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

using namespace lrvg;

/**
 * Creates a new instance of Plane with predefined mesh data.
 * The plane is centered at the origin and lies on the XZ plane.
 * The plane has a size of 2x2 units (from -1 to 1 in both X and Z dimensions).
 * 
 * @param segments Number of subdivisions along each axis (default: 10)
 */
Plane::Plane(int segments) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces;
    glm::vec3 normal_up(0, 1, 0);
    for (int z = 0; z <= segments; ++z) {
        for (int x = 0; x <= segments; ++x) {
            float xPos = -1.0f + (2.0f * x / segments);
            float zPos = -1.0f + (2.0f * z / segments);
            float u = (float)x / segments;
            float v = (float)z / segments;
            vertices.push_back(glm::vec3(xPos, 0, zPos));
            normals.push_back(normal_up);
            uvs.push_back(glm::vec2(u, v));
        }
    }
    for (int z = 0; z < segments; ++z) {
        for (int x = 0; x < segments; ++x) {
            uint32_t topLeft = z * (segments + 1) + x;
            uint32_t topRight = topLeft + 1;
            uint32_t bottomLeft = (z + 1) * (segments + 1) + x;
            uint32_t bottomRight = bottomLeft + 1;
            faces.push_back(std::make_tuple(topLeft, bottomLeft, topRight));
            faces.push_back(std::make_tuple(topRight, bottomLeft, bottomRight));
        }
    }
    this->set_mesh_data(vertices, faces, normals, uvs);
    this->set_cast_shadows(true);
}
