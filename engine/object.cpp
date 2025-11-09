#include "object.h"

#include <sstream>
#include <string>

#include <glm/glm.hpp>

#include "common.h"

using namespace lrvg;

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
