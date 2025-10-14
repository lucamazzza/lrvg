#include "perspective_camera.h"

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"

/**
 * Renders the scene from the perspective camera's point of view.
 * This method sets up the perspective projection matrix based on the camera's field of view,
 * aspect ratio, and clipping planes, and applies it to the OpenGL context.
 * 
 * This method is called automatically during the rendering process if the camera is active.
 * 
 * @param world_matrix A glm::mat4 representing the world transformation matrix.
 */
void ENG_API PerspectiveCamera::render(const glm::mat4 world_matrix) const {
	if (!this->is_active) {
		return;
	}
	Node::render(world_matrix);
	const float aspect_ratio = static_cast<float>(this->window_width) / static_cast<float>(this->window_height);
	const glm::mat4 perspective_matrix = glm::perspective(glm::radians(this->fov), aspect_ratio, this->near_clipping, this->far_clipping);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(perspective_matrix));
}