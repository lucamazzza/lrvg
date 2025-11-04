/**
 * @file	cube.cpp
 * @brief	Cube mesh class implementation
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "cube.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "mesh.h"

using namespace lrvg;

/**
 * Construct a unit cube (centered at origin) as a Mesh by supplying vertices,
 * indices (as triangle faces), normals and UVs to Mesh::set_mesh_data.
 */
void Cube::render(const glm::mat4 world_matrix) const {
	Mesh::render(world_matrix);
}

/**
 * Creates a new instance of Cube with predefined mesh data.
 * The cube is centered at the origin with a size of 1 unit in each dimension.
 */
Cube::Cube() {
    std::vector<glm::vec3> vertices = {
        // Back face (-Z)
        {  1.0f, -1.0f, -1.0f }, // 0
        { -1.0f, -1.0f, -1.0f }, // 1
        { -1.0f,  1.0f, -1.0f }, // 2
        {  1.0f,  1.0f, -1.0f }, // 3

        // Front face (+Z)
        { -1.0f, -1.0f,  1.0f }, // 4
        {  1.0f, -1.0f,  1.0f }, // 5
        {  1.0f,  1.0f,  1.0f }, // 6
        { -1.0f,  1.0f,  1.0f }, // 7

        // Left face (-X)
        { -1.0f, -1.0f, -1.0f }, // 8
        { -1.0f, -1.0f,  1.0f }, // 9
        { -1.0f,  1.0f,  1.0f }, // 10
        { -1.0f,  1.0f, -1.0f }, // 11

        // Right face (+X)
        {  1.0f, -1.0f,  1.0f }, // 12
        {  1.0f, -1.0f, -1.0f }, // 13
        {  1.0f,  1.0f, -1.0f }, // 14
        {  1.0f,  1.0f,  1.0f }, // 15

        // Bottom face (-Y)
        { -1.0f, -1.0f, -1.0f }, // 16
        {  1.0f, -1.0f, -1.0f }, // 17
        {  1.0f, -1.0f,  1.0f }, // 18
        { -1.0f, -1.0f,  1.0f }, // 19

        // Top face (+Y)
        { -1.0f,  1.0f,  1.0f }, // 20
        {  1.0f,  1.0f,  1.0f }, // 21
        {  1.0f,  1.0f, -1.0f }, // 22
        { -1.0f,  1.0f, -1.0f }  // 23
    };
	std::vector<glm::vec3> normals = {
        // Back
        {  0.0f,  0.0f, -1.0f },
        {  0.0f,  0.0f, -1.0f },
        {  0.0f,  0.0f, -1.0f },
        {  0.0f,  0.0f, -1.0f },
        // Front
        {  0.0f,  0.0f,  1.0f },
        {  0.0f,  0.0f,  1.0f },
        {  0.0f,  0.0f,  1.0f },
        {  0.0f,  0.0f,  1.0f },
        // Left
        { -1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        { -1.0f,  0.0f,  0.0f },
        // Right
        {  1.0f,  0.0f,  0.0f },
        {  1.0f,  0.0f,  0.0f },
        {  1.0f,  0.0f,  0.0f },
        {  1.0f,  0.0f,  0.0f },
        // Bottom
        {  0.0f, -1.0f,  0.0f },
        {  0.0f, -1.0f,  0.0f },
        {  0.0f, -1.0f,  0.0f },
        {  0.0f, -1.0f,  0.0f },
        // Top
        {  0.0f,  1.0f,  0.0f },
        {  0.0f,  1.0f,  0.0f },
        {  0.0f,  1.0f,  0.0f },
        {  0.0f,  1.0f,  0.0f }
    };
    std::vector<glm::vec2> uvs = {
        // Back
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        // Front
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        // Left
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        // Right
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        // Bottom
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        // Top
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}
    };
    std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces = {
        { 0,  1,  2}, { 0,  2,  3},    
        { 4,  5,  6}, { 4,  6,  7},    
        { 8,  9, 10}, { 8, 10, 11},   
        {12, 13, 14}, {12, 14, 15},
        {16, 17, 18}, {16, 18, 19},
        {20, 21, 22}, {20, 22, 23}
    };
	this->set_mesh_data(vertices, faces, normals, uvs);
	this->set_cast_shadows(true);
}
