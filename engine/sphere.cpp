#include "sphere.h"

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "common.h"
#include "mesh.h"

/**
 * Renders a sphere mesh using OpenGL.
 * The sphere is rendered with a radius of 1.0 and is subdivided into 20 slices and 20 stacks.
 * 
 * This method is called automatically during the rendering process.
 * 
 * @param world_matrix A glm::mat4 representing the world transformation matrix.
 */
void ENG_API Sphere::render(const glm::mat4 world_matrix) const {
	Mesh::render(world_matrix);
	glutSolidSphere(1.0, 20, 20);
}