/**
 * @file	main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "glm/fwd.hpp"
#include <engine.h>
#include <memory>
#include <node.h>
#include <glad/glad.h>
#include <perspective_camera.h>
#include <ortho_camera.h>
#include <point_light.h>
#include <cube.h>
#include <iostream>

std::shared_ptr<PerspectiveCamera> saved_camera = nullptr;
bool perspective_camera_is_used = false;

void gl_state() {
    const unsigned char *v = glad_glGetString ? glad_glGetString(GL_VERSION) : glGetString(GL_VERSION);
    const unsigned char *renderer = glad_glGetString ? glad_glGetString(GL_RENDERER) : glGetString(GL_RENDERER);
    const unsigned char *vendor = glad_glGetString ? glad_glGetString(GL_VENDOR) : glGetString(GL_VENDOR);
    std::cout << "GL VERSION: " << (v ? (const char*)v : "NULL") << "\n";
    std::cout << "GL RENDERER: " << (renderer ? (const char*)renderer : "NULL") << "\n";
    std::cout << "GL VENDOR: " << (vendor ? (const char*)vendor : "NULL") << "\n";
    GLint viewport[4] = {0, 0, 0, 0};
    if (glad_glGetIntegerv) glad_glGetIntegerv(GL_VIEWPORT, viewport);
    else glGetIntegerv(GL_VIEWPORT, viewport);
    std::cout << "VIEWPORT: " << viewport[0] << "," << viewport[1] << " " << viewport[2] << "x" << viewport[3] << "\n";
    auto isEnabled = [](GLenum e){
        GLboolean v = glad_glIsEnabled ? glad_glIsEnabled(e) : glIsEnabled(e);
        return v == GL_TRUE ? "ENABLED" : "DISABLED";
    };
    std::cout << "DEPTH_TEST: " << isEnabled(GL_DEPTH_TEST) << "\n";
    std::cout << "CULL_FACE: "  << isEnabled(GL_CULL_FACE)  << "\n";
    GLint curprog = 0;
    if (glad_glGetIntegerv) glad_glGetIntegerv(GL_CURRENT_PROGRAM, &curprog);
    else glGetIntegerv(GL_CURRENT_PROGRAM, &curprog);
    std::cout << "CURRENT_PROGRAM: " << curprog << "\n";
    GLenum err = glad_glGetError ? glad_glGetError() : glGetError();
    std::cout << "GL_ERROR (after init): 0x" << std::hex << err << std::dec << "\n";
}

/**
 * Application entry point.
 *
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main() {
    auto root = std::make_shared<Node>();
    LRVGEngine::init("Hanoi", 800, 600);
    //LRVGEngine::vsync_enable();
    LRVGEngine::set_sky_color(0.0f,0.0f,0.15f);
    auto material = std::make_shared<Material>();
    material->set_ambient_color(glm::vec3(1, 0, 0));
    material->set_diffuse_color(glm::vec3(1, 0, 0));
    material->set_emission_color(glm::vec3(1, 0, 0));
    material->set_specular_color(glm::vec3(1, 0, 0));
    material->set_shininess(10);
    auto cube = std::make_shared<Cube>();
    cube->set_name("MyCube");
    cube->set_position(glm::vec3(0.0f, 0.0f, -3.0f));
    cube->set_scale(glm::vec3(0.1f));
    cube->set_rotation(glm::vec3(10,20,10));
    cube->set_cast_shadows(true);
    cube->set_material(material);
    root->add_child(cube);
    auto light = std::make_shared<PointLight>();
    light->set_specular_color(glm::vec3(1));
    light->set_diffuse_color(glm::vec3(1));
    light->set_ambient_color(glm::vec3(1));
    light->set_radius(2);
    light->set_position(glm::vec3(0, 1, 0));
    root->add_child(light);
    auto cam = std::make_shared<PerspectiveCamera>();
    cam->set_fov(12.0f);
    cam->set_position(glm::vec3(0.0f, 0.0f, 1.0f));
    cam->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
    root->add_child(cam);
    LRVGEngine::set_scene(root);
    LRVGEngine::set_active_camera(cam);
    gl_state();
    while (LRVGEngine::is_running()) {
        LRVGEngine::update();
        LRVGEngine::clear_screen();
        LRVGEngine::render();
        LRVGEngine::swap_buffers();
    }
    LRVGEngine::free();
    std::cout << "exiting\n";
    return 0;
}


