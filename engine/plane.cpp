/**
 * @file	plane.cpp
 * @brief	Plane mesh class implementation
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "plane.h"

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "mesh.h"

using namespace lrvg;

/**
 * Creates a new instance of Plane with predefined mesh data.
 * The plane is centered at the origin and lies on the XZ plane.
 * The plane has a size of 2x2 units (from -1 to 1 in both X and Z dimensions).
 * The plane is double-sided (visible from both above and below).
 */
Plane::Plane() {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces;
    
    // Define 8 vertices (4 for top face, 4 for bottom face)
    // Top face (normal pointing +Y)
    vertices.push_back(glm::vec3(-1, 0, -1));  // 0: Bottom-left
    vertices.push_back(glm::vec3( 1, 0, -1));  // 1: Bottom-right
    vertices.push_back(glm::vec3( 1, 0,  1));  // 2: Top-right
    vertices.push_back(glm::vec3(-1, 0,  1));  // 3: Top-left
    
    // Bottom face (normal pointing -Y)
    vertices.push_back(glm::vec3(-1, 0, -1));  // 4: Bottom-left
    vertices.push_back(glm::vec3( 1, 0, -1));  // 5: Bottom-right
    vertices.push_back(glm::vec3( 1, 0,  1));  // 6: Top-right
    vertices.push_back(glm::vec3(-1, 0,  1));  // 7: Top-left
    
    // Normals for top face (pointing up +Y)
    glm::vec3 normal_up(0, 1, 0);
    normals.push_back(normal_up);
    normals.push_back(normal_up);
    normals.push_back(normal_up);
    normals.push_back(normal_up);
    
    // Normals for bottom face (pointing down -Y)
    glm::vec3 normal_down(0, -1, 0);
    normals.push_back(normal_down);
    normals.push_back(normal_down);
    normals.push_back(normal_down);
    normals.push_back(normal_down);
    
    // UV coordinates (same for both faces)
    uvs.push_back(glm::vec2(0, 0));
    uvs.push_back(glm::vec2(1, 0));
    uvs.push_back(glm::vec2(1, 1));
    uvs.push_back(glm::vec2(0, 1));
    uvs.push_back(glm::vec2(0, 0));
    uvs.push_back(glm::vec2(1, 0));
    uvs.push_back(glm::vec2(1, 1));
    uvs.push_back(glm::vec2(0, 1));
    
    // Top face triangles (CCW when viewed from above)
    faces.push_back(std::make_tuple(0, 1, 2));
    faces.push_back(std::make_tuple(0, 2, 3));
    
    // Bottom face triangles (CCW when viewed from below)
    faces.push_back(std::make_tuple(4, 6, 5));
    faces.push_back(std::make_tuple(4, 7, 6));
    
    this->set_mesh_data(vertices, faces, normals, uvs);
    this->set_cast_shadows(false);
}
