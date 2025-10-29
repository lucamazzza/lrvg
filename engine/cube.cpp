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
		{ -1.0f, -1.0f, -1.0f },
		{  1.0f, -1.0f, -1.0f },
		{  1.0f,  1.0f, -1.0f },
		{ -1.0f,  1.0f, -1.0f },
		{ -1.0f, -1.0f,  1.0f },
		{  1.0f, -1.0f,  1.0f },
		{  1.0f,  1.0f,  1.0f },
		{ -1.0f,  1.0f,  1.0f },

        { -1.0f,  1.0f, -1.0f },
		{ -1.0f, -1.0f, -1.0f },
		{ -1.0f, -1.0f,  1.0f },
		{ -1.0f,  1.0f,  1.0f },
		{  1.0f, -1.0f, -1.0f },
		{  1.0f,  1.0f, -1.0f },
		{  1.0f,  1.0f,  1.0f },
		{  1.0f, -1.0f,  1.0f },

		{ -1.0f, -1.0f, -1.0f },
		{  1.0f, -1.0f, -1.0f },
		{  1.0f, -1.0f,  1.0f },
		{ -1.0f, -1.0f,  1.0f },
		{  1.0f,  1.0f, -1.0f },
		{ -1.0f,  1.0f, -1.0f },
		{ -1.0f,  1.0f,  1.0f },
		{  1.0f,  1.0f,  1.0f }
	};
	std::vector<glm::vec3> normals(vertices.size());
	for (size_t i = 0; i < normals.size(); ++i) normals[i] = glm::vec3(0.0f);
	std::vector<glm::vec2> uvs = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},

		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},

		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f},
	};
	std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces = {
		{ 0,  3,  2}, 
        { 2,  1,  0},
		{ 4,  5,  6}, 
        { 6,  7,  4},

		{11,  8,  9}, 
        { 9, 10, 11},
		{12, 13, 14}, 
        {14, 15, 12},

		{16, 17, 18}, 
        {18, 19, 16},
		{20, 21, 22}, 
        {22, 23, 20}
	};
	for (const auto& f : faces) {
		uint32_t i0 = std::get<0>(f);
		uint32_t i1 = std::get<1>(f);
		uint32_t i2 = std::get<2>(f);
		glm::vec3 v0 = vertices[i0];
		glm::vec3 v1 = vertices[i1];
		glm::vec3 v2 = vertices[i2];
		glm::vec3 face_normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
		normals[i0] += face_normal;
		normals[i1] += face_normal;
		normals[i2] += face_normal;
	}
	this->set_mesh_data(vertices, faces, normals, uvs);
	this->set_cast_shadows(true);
}
