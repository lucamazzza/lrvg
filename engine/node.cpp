#include "node.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"

using namespace lrvg;

/**
 * Creates a new instance of Node with default transformation values.
 * 
 * * Base matrix: Identity matrix
 * * Position: (0, 0, 0)
 * * Rotation: (0, 0, 0)
 * * Scale: (1, 1, 1)
 */
ENG_API Node::Node() {
	this->set_base_matrix(glm::mat4(1.0f));
	this->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
	this->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
	this->set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

/**
 * Sets the base transformation matrix for the node.
 * 
 * @param base_matrix The base transformation matrix to set.
 */
void ENG_API Node::set_base_matrix(const glm::mat4 base_matrix) {
	this->base_matrix = base_matrix;
}

/**
 * Sets the position of the node in 3D space.
 * 
 * @param position A glm::vec3 representing the new position.
 */
void ENG_API Node::set_position(const glm::vec3 position) {
	this->position = position;
}

/**
 * Sets the rotation of the node in degrees around the X, Y, and Z axes.
 * 
 * @param rotation A glm::vec3 representing the rotation angles in degrees.
 */
void ENG_API Node::set_rotation(const glm::vec3 rotation) {
	this->rotation = rotation;
}

/**
 * Sets the scale of the node along the X, Y, and Z axes.
 * 
 * @param scale A glm::vec3 representing the scaling factors.
 */
void ENG_API Node::set_scale(const glm::vec3 scale) {
	this->scale = scale;
}

/**
 * Computes and returns the local transformation matrix of the node.
 * This matrix is calculated by combining the position, rotation, scale,
 * and base transformation matrix of the node.
 * 
 * The local matrix is computed in the following order:
 * 1. base matrix
 * 2. scale matrix
 * 3. x rotation matrix
 * 4. y rotation matrix
 * 5. z rotation matrix
 * 6. translation matrix
 * 
 * @return A glm::mat4 representing the local transformation matrix.
 */
glm::mat4 ENG_API Node::get_local_matrix() const {
	const glm::mat4 model_position_matrix = glm::translate(glm::mat4(1.0f), this->position);
	const glm::mat4 model_rotation_matrix =
		glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 model_scale_matrix = glm::scale(glm::mat4(1.0f), this->scale);
	const glm::mat4 offset_matrix = model_position_matrix * model_rotation_matrix * model_scale_matrix;
	return offset_matrix * this->base_matrix;
}

/**
 * Retrieves the position of the node in 3D space.
 * 
 * @return A glm::vec3 representing the position of the node.
 */
glm::vec3 ENG_API Node::get_position() const {
	return this->position;
}

/**
 * Retrieves the rotation of the node in degrees around the X, Y, and Z axes.
 * 
 * @return A glm::vec3 representing the rotation angles in degrees.
 */
glm::vec3 ENG_API Node::get_rotation() const {
	return this->rotation;
}

/**
 * Renders the node using the provided world transformation matrix.
 * This method sets the OpenGL model-view matrix to the given world matrix
 * and prepares the node for rendering. Derived classes should override this
 * method to implement specific rendering behavior.
 * 
 * @param world_matrix A glm::mat4 representing the world transformation matrix.
 */
glm::vec3 ENG_API Node::get_scale() const {
	return this->scale;
}

/**
 * Renders the node using the provided world transformation matrix.
 * This method sets the OpenGL model-view matrix to the given world matrix
 * and prepares the node for rendering. Derived classes should override this
 * method to implement specific rendering behavior.
 *
 * This method is called automatically during the rendering process.
 * 
 * @param world_matrix A glm::mat4 representing the world transformation matrix.
 */
void ENG_API Node::render(const glm::mat4 world_matrix) const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(world_matrix));
}
