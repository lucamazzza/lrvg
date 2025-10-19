#include "mesh.h"

#include <memory>
#include <tuple>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "common.h"
#include "glm/gtc/type_ptr.hpp"

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
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(world_matrix));
    this->material->render(world_matrix);
    glBegin(GL_TRIANGLES);
    for (const auto& face : this->faces) {
        const auto i0 = std::get<0>(face);
        const auto i1 = std::get<1>(face);
        const auto i2 = std::get<2>(face);
        const glm::vec3 &v0 = this->vertices[i0];
        const glm::vec3 &v1 = this->vertices[i1];
        const glm::vec3 &v2 = this->vertices[i2];
        const glm::vec3 &n0 = this->normals[i0];
        const glm::vec3 &n1 = this->normals[i1];
        const glm::vec3 &n2 = this->normals[i2];
        const glm::vec2 &uv0 = this->uvs[i0];
        const glm::vec2 &uv1 = this->uvs[i1];
        const glm::vec2 &uv2 = this->uvs[i2];
        glTexCoord2f(uv0.x, uv0.y);
        glNormal3f(n0.x, n0.y, n0.z);
        glVertex3f(v0.x, v0.y, v0.z);
        glTexCoord2f(uv1.x, uv1.y);
        glNormal3f(n1.x, n1.y, n1.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glTexCoord2f(uv2.x, uv2.y);
        glNormal3f(n2.x, n2.y, n2.z);
        glVertex3f(v2.x, v2.y, v2.z);
    }
    glEnd();
    glPopMatrix();
}
