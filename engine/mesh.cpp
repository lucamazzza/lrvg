#include "mesh.h"

#include <memory>
#include <tuple>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "common.h"
#include "glm/gtc/type_ptr.hpp"

using namespace lrvg;

/**
 * Creates a new instance of Mesh with default values.
 */
ENG_API Mesh::Mesh() {
	this->set_material(std::make_shared<Material>());
	this->set_cast_shadows(true);
}

/**
 * Sets the material used for rendering the mesh.
 *
 * NOTE: A value of `nullptr` causes undefined behavior.
 * 
 * @param material A shared pointer to the Material to set.
 */
void ENG_API Mesh::set_material(const std::shared_ptr<Material> material) {
	this->material = material;
}

/**
 * Retrieves the material used for rendering the mesh.
 * 
 * @return A shared pointer to the current Material.
 */
std::shared_ptr<Material> ENG_API Mesh::get_material() const {
	return this->material;
}

/**
 * Sets the mesh data including vertices, faces, normals, and texture coordinates (UVs).
 *
 * NOTE: Incorrectly sized vectors cause undefined behavior.
 * 
 * @param vertices A vector of glm::vec3 representing the vertex positions.
 * @param faces A vector of tuples, each containing three uint32_t indices defining a triangular face.
 * @param normals A vector of glm::vec3 representing the normal vectors for each vertex.
 * @param uvs A vector of glm::vec2 representing the texture coordinates for each vertex.
 */
void ENG_API Mesh::set_mesh_data(
	const std::vector<glm::vec3> vertices,
	const std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> faces,
	const std::vector<glm::vec3> normals,
	const std::vector<glm::vec2> uvs
) {
	this->vertices = vertices;
	this->faces = faces;
	this->normals = normals;
	this->uvs = uvs;
}

/**
 * Sets whether the mesh should cast shadows in the scene.
 * 
 * @param cast_shadows A boolean indicating if the mesh should cast shadows.
 */
void ENG_API Mesh::set_cast_shadows(const bool cast_shadows) {
	this->cast_shadows = cast_shadows;
}

/**
 * Checks if the mesh is set to cast shadows.
 * 
 * @return A boolean indicating if the mesh casts shadows.
 */
bool ENG_API Mesh::get_cast_shadows() const {
	return this->cast_shadows;
}

/**
 * Renders the mesh using OpenGL.
 * This method applies the material and iterates over each face to draw the triangles.
 * It uses the vertex positions, normals, and texture coordinates defined in the mesh data.
 *
 * This method is called automatically during the rendering process.
 * 
 * @param world_matrix A glm::mat4 representing the world transformation matrix.
 */
void ENG_API Mesh::render(const glm::mat4 world_matrix) const {
    Node::render(world_matrix);
    this->material->render(world_matrix);
    for (const auto& face : this->faces) {
        glBegin(GL_TRIANGLES);
        const glm::vec3 vertex_0 = this->vertices[std::get<0>(face)];
        const glm::vec3 vertex_1 = this->vertices[std::get<1>(face)];
        const glm::vec3 vertex_2 = this->vertices[std::get<2>(face)];
        const glm::vec3 normal_0 = this->normals[std::get<0>(face)];
        const glm::vec3 normal_1 = this->normals[std::get<1>(face)];
        const glm::vec3 normal_2 = this->normals[std::get<2>(face)];
        const glm::vec2 uv_0 = this->uvs[std::get<0>(face)];
        const glm::vec2 uv_1 = this->uvs[std::get<1>(face)];
        const glm::vec2 uv_2 = this->uvs[std::get<2>(face)];
        glTexCoord2f(uv_0.x, uv_0.y);
        glNormal3f(normal_0.x, normal_0.y, normal_0.z);
        glVertex3f(vertex_0.x, vertex_0.y, vertex_0.z);
        glTexCoord2f(uv_1.x, uv_1.y);
        glNormal3f(normal_1.x, normal_1.y, normal_1.z);
        glVertex3f(vertex_1.x, vertex_1.y, vertex_1.z);
        glTexCoord2f(uv_2.x, uv_2.y);
        glNormal3f(normal_2.x, normal_2.y, normal_2.z);
        glVertex3f(vertex_2.x, vertex_2.y, vertex_2.z);
        glEnd();
    }
}
