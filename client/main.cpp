/**
 * @file	main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include <memory>

#include <engine.h>
#include <node.h>
#include <perspective_camera.h>
#include <ortho_camera.h>
#include <cube.h>
#include <sphere.h>
#include <plane.h>
#include <directional_light.h>
#include <point_light.h>
#include <ovo_parser.h>
#include <mesh.h>

#include "game_controller.h"

std::shared_ptr<lrvg::PerspectiveCamera>    saved_persp_camera = nullptr;
std::shared_ptr<lrvg::OrthoCamera>          saved_ortho_camera = nullptr;
std::shared_ptr<lrvg::Node>                 saved_light = nullptr;
float                                       zoom = 300.0f;
GameController*                             controller = nullptr;
float                                       camera_angle = 0.0f;
float                                       light_angle = 0.0f;

void move_light() {
    if (saved_light) {
        light_angle += 1.0f; // Increment angle (degrees per frame)
        float radius = 80.0f; // Circle radius
        float rad = glm::radians(light_angle);
        glm::vec3 new_pos(radius * sin(rad), 0.0f, radius * cos(rad));
        saved_light->set_position(new_pos);
    }
}

/**
 * Application entry point.
 *
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main() {
    controller = new GameController(7);
    auto root = std::make_shared<lrvg::Node>();

    // Init engine
    lrvg::Engine::init("Hanoi", 800, 600);
    lrvg::Engine::set_sky_color(0.0f,0.0f,0.15f);

    // Commands overlay
    lrvg::Engine::set_screen_text(
            "LRVG Engine - Hanoi Tower" 
            "\n[1-3]  Select Tower (source then target)"
            "\n[S]    Auto-solve"
            "\n[R]    Restart game"
            "\n[P]    Perspective camera"
            "\n[O]    Ortho camera"
            "\n[A/D]  Rotate camera"
            "\n[J]    Zoom - (ortho)"
            "\n[K]    Zoom + (ortho)");

    // Keyboard callbacks
    lrvg::Engine::set_keyboard_callback([](const unsigned char key, const int mouse_x, const int mouse_y) {
            switch (key) {
                case '1': case '2': case '3':
                    controller->handle_tower_selection(key - '1');
                    break;
                case 's': case 'S':
                    controller->autosolve();
                    break;
                case 'o': case 'O':
                    if (saved_ortho_camera)
                        lrvg::Engine::set_active_camera(saved_ortho_camera);
                    break;
                case 'p': case 'P':
                    if (saved_persp_camera)
                        lrvg::Engine::set_active_camera(saved_persp_camera);
                    break;
                case 'j': case 'J':
                    zoom += 10.0f;
                    if (saved_ortho_camera) {
                        saved_ortho_camera->set_zoom(zoom);
                    }
                    break;
                case 'k': case 'K':
                    zoom -= 10.0f;
                    if (saved_ortho_camera) {
                        saved_ortho_camera->set_zoom(zoom);
                    }
                    break;
                case 'r': case 'R':
                    controller->reset_game();
                    break;
                case 'a': case 'A':
                    if (saved_persp_camera) {
                        camera_angle -= 5.0f;
                        float radius = 100.0f;
                        float rad = glm::radians(camera_angle);
                        glm::vec3 new_pos(radius * sin(rad), 30.0f, radius * cos(rad));
                        saved_persp_camera->set_position(new_pos);
                        saved_persp_camera->set_rotation(glm::vec3(0.0f, camera_angle, 0.0f));
                    }
                    break;
                case 'd': case 'D':
                    if (saved_persp_camera) {
                        camera_angle += 5.0f;
                        float radius = 100.0f;
                        float rad = glm::radians(camera_angle);
                        glm::vec3 new_pos(radius * sin(rad), 30.0f, radius * cos(rad));
                        saved_persp_camera->set_position(new_pos);
                        saved_persp_camera->set_rotation(glm::vec3(0.0f, camera_angle, 0.0f));
                    }
                    break;
            }
    });

    // Scene setup
    root = lrvg::OVOParser::from_file("HanoiBased.ovo");
    if (LIKELY(saved_ortho_camera == nullptr || saved_persp_camera == nullptr)) {
        std::shared_ptr<lrvg::OrthoCamera> camera_1 = std::make_shared<lrvg::OrthoCamera>();
        camera_1->set_zoom(zoom);
        camera_1->set_name("Camera");
        camera_1->set_position(glm::vec3(-100.0f, 20.0f, 0.0f));
        camera_1->set_rotation(glm::vec3(0.0f, -90.0f, 0.0f));
        std::shared_ptr<lrvg::PerspectiveCamera> camera_2 = std::make_shared<lrvg::PerspectiveCamera>();
        camera_2->set_name("Camera 2");
        camera_2->set_position(glm::vec3(0.0f, 30.0f, 100.0f));
        camera_2->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
        saved_ortho_camera = camera_1;
        saved_persp_camera = camera_2;
    }
    root->add_child(saved_ortho_camera);
    root->add_child(saved_persp_camera);
    lrvg::Engine::set_scene(root);
    lrvg::Engine::set_active_camera(saved_persp_camera);
    // Shadow Enable
    auto board = std::dynamic_pointer_cast<lrvg::Mesh>(lrvg::Engine::find_obj_by_name("Board"));
    if (board) board->set_cast_shadows(true);
    controller->init_scene_nodes();
    // Moving lights
    saved_light = std::static_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("MovingLight"));
    auto omni = std::dynamic_pointer_cast<lrvg::PointLight>(lrvg::Engine::find_obj_by_name("Omni001"));
    omni->set_radius(.6f);

    // Main loop
    while (LIKELY(lrvg::Engine::is_running())) {
        // NOTE: For Autosolver timing consistency
        controller->update(0.016f);
        move_light();
        lrvg::Engine::update();
        lrvg::Engine::clear_screen();
        lrvg::Engine::render();
        lrvg::Engine::swap_buffers();
    }

    // Free engine resources
    lrvg::Engine::free();
    delete controller;
    return 0;
}


