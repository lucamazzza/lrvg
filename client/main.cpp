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
float                                       zoom = 300.0f;
GameController*                             controller = nullptr;

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
            "\n[A]    Auto-solve"
            "\n[R]    Restart game"
            "\n[P]    Perspective camera"
            "\n[O]    Ortho camera"
            "\n[J]    Zoom - (ortho)"
            "\n[K]    Zoom + (ortho)");

    // Keyboard callbacks
    lrvg::Engine::set_keyboard_callback([](const unsigned char key, const int mouse_x, const int mouse_y) {
            switch (key) {
                case '1': case '2': case '3':
                    controller->handle_tower_selection(key - '1');
                    break;
                case 'a': case 'A':
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
        camera_2->set_position(glm::vec3(-80.0f, 30.0f, 10.0f));
        camera_2->set_rotation(glm::vec3(0.0f, -80.0f, -10.0f));
        saved_ortho_camera = camera_1;
        saved_persp_camera = camera_2;
    }
    root->add_child(saved_ortho_camera);
    root->add_child(saved_persp_camera);
    lrvg::Engine::set_scene(root);
    lrvg::Engine::set_active_camera(saved_persp_camera);
    auto base = std::static_pointer_cast<lrvg::Mesh>(lrvg::Engine::find_obj_by_name("Table"));
    if (base) base->set_cast_shadows(false);
    controller->init_scene_nodes();

    // Main loop
    while (LIKELY(lrvg::Engine::is_running())) {
        controller->update(0.016f);
        
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


