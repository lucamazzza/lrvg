#include "cube.h"

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "common.h"
#include "mesh.h"

/**
 * Renders a solid cube using GLUT's built-in function.
 * The cube is centered at the origin with a size of 1.0 unit.
 * 
 * This method is called automatically during the rendering process.
 * 
 * @param world_matrix The transformation matrix to apply to the cube before rendering.
 */
void ENG_API Cube::render(const glm::mat4 world_matrix) const {
	Mesh::render(world_matrix);
	glutSolidCube(1.0f);
}
