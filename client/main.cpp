/**
 * @file	main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Luca Mazza (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include <engine.h>
#include <memory>
#include <node.h>
#include <perspective_camera.h>
#include <ortho_camera.h>
#include <directional_light.h>
#include <cube.h>

std::shared_ptr<lrvg::PerspectiveCamera> saved_camera = nullptr;
bool perspective_camera_is_used = false;

/**
 * Application entry point.
 *
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main() {
    auto root = std::make_shared<lrvg::Node>();
    lrvg::Engine::init("Hanoi", 800, 600);
    //lrvg::Engine::vsync_enable();
    lrvg::Engine::set_sky_color(0.0f,0.0f,0.15f);
    auto material = std::make_shared<lrvg::Material>();
    material->set_ambient_color(glm::vec3(1, 0, 0));
    material->set_diffuse_color(glm::vec3(1, 0, 0));
    material->set_specular_color(glm::vec3(1, 0, 0));
    auto cube = std::make_shared<lrvg::Cube>();
    cube->set_name("MyCube");
    cube->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
    cube->set_scale(glm::vec3(0.1f));
    cube->set_rotation(glm::vec3(10,20,10));
    cube->set_cast_shadows(true);
    cube->set_material(material);
    root->add_child(cube);
    auto light = std::make_shared<lrvg::DirectionalLight>();
    light->set_position(glm::vec3(0.0f, 0.0f, 3.0f));
    light->set_direction(glm::vec3(0.0f, 0.0f, -1.0f));
    root->add_child(light);
    auto cam = std::make_shared<lrvg::PerspectiveCamera>();
    cam->set_fov(12.0f);
    cam->set_position(glm::vec3(0.0f, 0.0f, 3.0f));
    cam->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
    root->add_child(cam);
    lrvg::Engine::set_scene(root);
    lrvg::Engine::set_active_camera(cam);
    while (lrvg::Engine::is_running()) {
        lrvg::Engine::update();
        lrvg::Engine::clear_screen();
        lrvg::Engine::render();
        lrvg::Engine::swap_buffers();
    }
    lrvg::Engine::free();
    std::cout << "exiting\n";
    return 0;
}


