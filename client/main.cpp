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
#include <ovo_parser.h>

std::shared_ptr<lrvg::PerspectiveCamera>    saved_persp_camera = nullptr;
std::shared_ptr<lrvg::OrthoCamera>          saved_ortho_camera = nullptr;
float                                       zoom = 300.0f;

/**
 * Application entry point.
 *
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main() {
    auto root = std::make_shared<lrvg::Node>();

    // Init engine
    lrvg::Engine::init("Hanoi", 800, 600);
    lrvg::Engine::set_sky_color(0.0f,0.0f,0.15f);

    // Commands overlay
    lrvg::Engine::set_screen_text(
            "LRVG Engine - Sample Application" 
            "\n[P]    Perspective camera"
            "\n[O]    Ortho camera"
            "\n[J|K]   Ortho camera zoom");

    // Keyboard callbacks
    lrvg::Engine::set_keyboard_callback([](const unsigned char key, const int mouse_x, const int mouse_y) {
            const float step = 0.5f;
            switch (key) {
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
                default:
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

    // Main loop
    while (LIKELY(lrvg::Engine::is_running())) {
        lrvg::Engine::update();
        lrvg::Engine::clear_screen();
        lrvg::Engine::render();
        lrvg::Engine::swap_buffers();
    }

    // Free engine resources
    lrvg::Engine::free();
    return 0;
}


