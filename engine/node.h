/**
 * @file	node.h
 * @brief	Scene graph node class implementation
 *
 * This file contains the definition of the Mesh class, which represents a 3D mesh
 * in a rendering engine. The Mesh class allows setting and retrieving the material,
 * mesh data (vertices, faces, normals, UVs), and rendering the mesh using OpenGL.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "common.h"
#include "object.h"

namespace lrvg {

/**
 * @brief Scene graph node class.
 *
 * The Node class represents a node in the scene graph. It can have multiple child nodes,
 * and it manages its own transformation including position, rotation, scale, and a base matrix.
 * The local transformation matrix is computed based on these properties.
 * Nodes can be rendered, and they propagate rendering calls to their children.
 * This class inherits from Object, allowing it to have a name and unique ID.
 * Nodes are fundamental building blocks for constructing complex scenes in the graphics engine.
 *
 * @see Object
 */
class ENG_API Node : public Object {
public:
	Node();
	glm::mat4 get_local_matrix() const override;
	glm::vec3 get_position() const;
	glm::vec3 get_rotation() const;
	glm::vec3 get_scale() const;
    std::vector<std::shared_ptr<Node>> get_children() const;
	void add_child(const std::shared_ptr<Node> child);
    void set_base_matrix(const glm::mat4 base_matrix);
    void set_position(const glm::vec3 position);
    void set_rotation(const glm::vec3 rotation);
    void set_scale(const glm::vec3 scale);
	void render(const glm::mat4 world_matrix) const override;
	bool remove_child(const std::shared_ptr<Node> child);
protected:
	std::vector<std::shared_ptr<Node>> children;
private:
	glm::mat4 base_matrix;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

}
