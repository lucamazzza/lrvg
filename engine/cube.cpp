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
 * The cube is centered at the origin with a size of 1 unit in each dimension.
 */
Cube::Cube() {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces;
    
    // Define 6 faces with their normals
    struct FaceDef {
        glm::vec3 normal;
        glm::vec3 v[4];  // 4 vertices in CCW order
    };
    
    FaceDef faceDefs[6] = {
        // Front (+Z)
        { glm::vec3(0, 0, 1), {
            glm::vec3(-1, -1,  1), glm::vec3( 1, -1,  1),
            glm::vec3( 1,  1,  1), glm::vec3(-1,  1,  1)
        }},
        // Back (-Z)
        { glm::vec3(0, 0, -1), {
            glm::vec3( 1, -1, -1), glm::vec3(-1, -1, -1),
            glm::vec3(-1,  1, -1), glm::vec3( 1,  1, -1)
        }},
        // Right (+X)
        { glm::vec3(1, 0, 0), {
            glm::vec3( 1, -1,  1), glm::vec3( 1, -1, -1),
            glm::vec3( 1,  1, -1), glm::vec3( 1,  1,  1)
        }},
        // Left (-X)
        { glm::vec3(-1, 0, 0), {
            glm::vec3(-1, -1, -1), glm::vec3(-1, -1,  1),
            glm::vec3(-1,  1,  1), glm::vec3(-1,  1, -1)
        }},
        // Top (+Y)
        { glm::vec3(0, 1, 0), {
            glm::vec3(-1,  1,  1), glm::vec3( 1,  1,  1),
            glm::vec3( 1,  1, -1), glm::vec3(-1,  1, -1)
        }},
        // Bottom (-Y)
        { glm::vec3(0, -1, 0), {
            glm::vec3(-1, -1, -1), glm::vec3( 1, -1, -1),
            glm::vec3( 1, -1,  1), glm::vec3(-1, -1,  1)
        }}
    };
    
    glm::vec2 faceUVs[4] = {
        glm::vec2(0, 0), glm::vec2(1, 0),
        glm::vec2(1, 1), glm::vec2(0, 1)
    };
    
    uint32_t idx = 0;
    for (int f = 0; f < 6; f++) {
        for (int v = 0; v < 4; v++) {
            vertices.push_back(faceDefs[f].v[v]);
            normals.push_back(faceDefs[f].normal);
            uvs.push_back(faceUVs[v]);
        }
        // Two triangles per face
        faces.push_back(std::make_tuple(idx + 0, idx + 1, idx + 2));
        faces.push_back(std::make_tuple(idx + 0, idx + 2, idx + 3));
        idx += 4;
    }
    
	this->set_mesh_data(vertices, faces, normals, uvs);
	this->set_cast_shadows(true);
}
