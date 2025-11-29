/**
 * @file	sphere.cpp
 * @brief	Sphere mesh class implementation
 *
 * This file contains the implementation of the Sphere class, which represents a sphere mesh with procedurally
 * generated geometry.
 * The Sphere class inherits from the Mesh class and allows for the creation of a sphere mesh with
 * a specified number of latitude and longitude segments.
 *
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "sphere.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "common.h"
#include "mesh.h"

using namespace lrvg;

/**
 * Creates a new instance of Sphere with procedurally generated mesh data.
 * 
 * @param lat_segments Number of latitude segments (horizontal divisions)
 * @param lon_segments Number of longitude segments (vertical divisions)
 */
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
			normals.emplace_back(glm::normalize(glm::vec3(xs, ys, zs)));
			uvs.emplace_back(u, 1.0f - v);
		}
	}
	for (int y = 0; y < lat_segments; ++y) {
		for (int x = 0; x < lon_segments; ++x) {
			uint32_t i0 = y * (lon_segments + 1) + x;
			uint32_t i1 = i0 + 1;
			uint32_t i2 = i0 + (lon_segments + 1);
			uint32_t i3 = i2 + 1;
			faces.emplace_back(i0, i1, i2);
			faces.emplace_back(i2, i1, i3);
		}
	}
	this->set_mesh_data(vertices, faces, normals, uvs);
	this->set_cast_shadows(true);
}
