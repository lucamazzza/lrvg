#include "ortho_camera.h"

#include <algorithm>

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"
#include "node.h"

/**
 * Sets the zoom level of the orthographic camera.
 * The zoom level must be greater than or equal to 0.1 to avoid invalid projection matrices.
 * 
 * @param zoom A float representing the desired zoom level.
 */
void ENG_API OrthoCamera::set_zoom(float zoom) {
	this->zoom = std::max(zoom, 0.1f);
}

/**
 * Retrieves the current zoom level of the orthographic camera.
 * 
 * @return A float representing the zoom level.
 */
float ENG_API OrthoCamera::get_zoom() const {
	return this->zoom;
}

/**
 * Renders the scene from the perspective of the orthographic camera.
 * This method sets up the orthographic projection matrix based on the camera's zoom level and window dimensions,
 * and applies the camera's world transformation matrix.
 * 
 * @param world_matrix A glm::mat4 representing the world transformation matrix of the camera.
 */
void ENG_API OrthoCamera::render(const glm::mat4 world_matrix) const {
	if (!this->is_active) {
		return;
	}
	Node::render(world_matrix);
	const float width = static_cast<float>(this->window_width);
	const float height = static_cast<float>(this->window_height);
	const float max = std::max(width, height);
	const float w = (width / max) * this->zoom;
	const float h = (height / max) * this->zoom;
	const glm::mat4 ortho_matrix = glm::ortho(-w / 2.0f, w / 2.0f, -h / 2.0f, h / 2.0f, this->near_clipping, this->far_clipping);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(ortho_matrix));
}
