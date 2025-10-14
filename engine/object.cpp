#include "object.h"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "common.h"

int Object::next_id = 0;

/**
 * Creates a new instance of Object with a unique ID and default name.
 * The `id` is automatically assigned and incremented for each new object.
 */
ENG_API Object::Object() : id{ Object::next_id++ } {
	std::stringstream ss;
	ss << '[' << this->get_id() << ']';
	this->name = ss.str();
}

/**
 * Returns the unique ID of the object.
 * 
 * @return The unique integer ID of the object.
 */
int ENG_API Object::get_id() const {
	return this->id;
}

/**
 * Adds a child object to this object's list of children.
 * 
 * @param child A shared pointer to the child object to be added.
 */
void ENG_API Object::add_child(const std::shared_ptr<Object> child) {
	this->children.push_back(child);
}

/**
 * Retrieves the list of child objects.
 * 
 * @return A vector of shared pointers to the child objects.
 */
std::vector<std::shared_ptr<Object>> ENG_API Object::get_children() const {
	return this->children;
}

/**
 * Creates a new instance of Object with a specified name and unique ID.
 * The `id` is automatically assigned and incremented for each new object.
 * 
 * @param name The name to assign to the object.
 */
glm::mat4 ENG_API Object::get_local_matrix() const {
	return glm::mat4(1.0f);
}

/**
 * Returns the priority of the object for rendering order.
 * Default implementation returns 0; can be overridden in derived classes.
 * 
 * @return The integer priority of the object.
 */
int ENG_API Object::get_priority() const {
	return 0;
}

/**
 * Retrieves the name of the object.
 * 
 * @return The name of the object as a string.
 */
std::string ENG_API Object::get_name() const {
	return this->name;
}

/**
 * Sets the name of the object.
 * 
 * @param name The new name to assign to the object.
 */
void ENG_API Object::set_name(const std::string name) {
	this->name = name;
}