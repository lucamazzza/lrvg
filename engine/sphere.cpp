#include "sphere.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "common.h"
#include "mesh.h"

Sphere::Sphere(int lat_segments, int lon_segments) {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces;
	for (int y = 0; y <= lat_segments; ++y) {
		float v = (float)y / (float)lat_segments;
		float theta = v * glm::pi<float>();
		for (int x = 0; x <= lon_segments; ++x) {
			float u = (float)x / (float)lon_segments;
			float phi = u * glm::two_pi<float>();
			float xs = sin(theta) * cos(phi);
			float ys = cos(theta);
			float zs = sin(theta) * sin(phi);
			vertices.emplace_back(xs, ys, zs);
			normals.emplace_back(xs, ys, zs); // unit sphere normals
			uvs.emplace_back(u, 1.0f - v);
		}
	}
	for (int y = 0; y < lat_segments; ++y) {
		for (int x = 0; x < lon_segments; ++x) {
			uint32_t i0 = y * (lon_segments + 1) + x;
			uint32_t i1 = i0 + 1;
			uint32_t i2 = i0 + (lon_segments + 1);
			uint32_t i3 = i2 + 1;
			faces.emplace_back(i0, i2, i1);
			faces.emplace_back(i1, i2, i3);
		}
	}
	this->set_mesh_data(vertices, faces, normals, uvs);
}

void ENG_API Sphere::render(const glm::mat4 world_matrix) const {
	Mesh::render(world_matrix);
}
