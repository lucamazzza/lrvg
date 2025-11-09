/**
 * @file	main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include <engine.h>
#include <memory>
#include <node.h>
#include <perspective_camera.h>
#include <ortho_camera.h>
#include <cube.h>
#include <sphere.h>
#include <plane.h>
#include <directional_light.h>
#include <point_light.h>

std::shared_ptr<lrvg::PerspectiveCamera>    saved_persp_camera = nullptr;
std::shared_ptr<lrvg::OrthoCamera>          saved_ortho_camera = nullptr;
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
    lrvg::Engine::set_sky_color(0.0f,0.0f,0.15f);
    auto plane = std::make_shared<lrvg::Plane>();
    plane->set_name("Ground");
    plane->set_position(glm::vec3(0.0f, -50.0f, -50.0f));
    plane->set_scale(glm::vec3(150.0f, 1.0f, 150.0f));
    root->add_child(plane);
    auto cube = std::make_shared<lrvg::Sphere>();
    cube->set_name("MySphere");
    cube->set_position(glm::vec3(0.0f, 0.0f, -50.0f));
    cube->set_rotation(glm::vec3(0.0f, 30.0f, 0.0f));
    cube->set_scale(glm::vec3(30.0f));
    cube->set_cast_shadows(false);
    root->add_child(cube);
    auto light = std::make_shared<lrvg::DirectionalLight>();
    light->set_name("Main Light");
    //light->set_position(glm::vec3(0.0f, 10.0f, 10.0f));
    //light->set_radius(2.0f);
    //light->set_direction(glm::vec3(0.0f, -1.0f, 0.0f));
    root->add_child(light);
    if (LIKELY(saved_ortho_camera == nullptr || saved_persp_camera == nullptr)) {
        std::shared_ptr<lrvg::OrthoCamera> camera_1 = std::make_shared<lrvg::OrthoCamera>();
        camera_1->set_zoom(300.0f);
        camera_1->set_name("Camera");
        camera_1->set_position(glm::vec3(0.0f, 150.0f, 0.0f));
        camera_1->set_rotation(glm::vec3(-90.0f, 0.0f, 0.0f));
        std::shared_ptr<lrvg::PerspectiveCamera> camera_2 = std::make_shared<lrvg::PerspectiveCamera>();
        camera_2->set_name("Camera 2");
        camera_2->set_position(glm::vec3(0.0f, 0.0f, 100.0f));
        camera_2->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
        saved_ortho_camera = camera_1;
        saved_persp_camera = camera_2;
    }
    root->add_child(saved_ortho_camera);
    root->add_child(saved_persp_camera);
    lrvg::Engine::set_scene(root);
    lrvg::Engine::set_active_camera(saved_persp_camera);
    while (LIKELY(lrvg::Engine::is_running())) {
        lrvg::Engine::update();
        lrvg::Engine::clear_screen();
        lrvg::Engine::render();
        lrvg::Engine::swap_buffers();
    }
    lrvg::Engine::free();
    return 0;
}


