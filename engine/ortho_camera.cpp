#include "ortho_camera.h"

#include <algorithm>

#include <glad/glad.h>
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
    if (!this->is_active) return;
    Node::render(world_matrix);
    int fb_w = window_width; 
    int fb_h = window_height;
    if (fb_w <= 0 || fb_h <= 0) {
        fb_w = 800;
        fb_h = 600;
    }
    const float halfW = this->window_width * 0.5f;
    const float halfH = this->window_height * 0.5f;
    const glm::mat4 ortho_matrix = glm::ortho(-halfW, halfW, -halfH, halfH, this->near_clipping, this->far_clipping);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(ortho_matrix));
    const glm::mat4 view_matrix = glm::inverse(world_matrix);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view_matrix));
}
