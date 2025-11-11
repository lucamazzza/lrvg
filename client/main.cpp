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
std::shared_ptr<lrvg::Material>             saved_material = nullptr;
std::shared_ptr<lrvg::Plane>                saved_plane = nullptr;
std::shared_ptr<lrvg::Sphere>               saved_sphere = nullptr;
std::shared_ptr<lrvg::Cube>                 saved_cube = nullptr;
float                                       zoom = 300.0f;

static std::shared_ptr<lrvg::Material> gen_rand_mat() {
    auto mat = std::make_shared<lrvg::Material>();
    mat->set_ambient_color(
        glm::vec3(
            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)),
            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)),
            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX))
        )
    );
    mat->set_specular_color(glm::vec3(1.0f, 1.0f, 1.0f));
    mat->set_shininess(32.0f);
    return mat;
}

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
            "\n[M]    Change material color" 
            "\n[WASD] Move light"
            "\n[P]    Perspective camera"
            "\n[O]    Ortho camera"
            "\n[J|K]  Ortho camera zoom");

    // Keyboard callbacks
    lrvg::Engine::set_keyboard_callback([](const unsigned char key, const int mouse_x, const int mouse_y) {
            auto light = std::dynamic_pointer_cast<lrvg::PointLight>(lrvg::Engine::find_obj_by_name("Main Light"));
            if (light == nullptr) return;
            glm::vec3 pos = light->get_position();
            const float step = 0.5f;
            switch (key) {
                case 'm': case 'M':
                    saved_material->set_ambient_color(
                        glm::vec3(
                            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)),
                            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)),
                            (static_cast<float>(rand()) / static_cast<float>(RAND_MAX))
                        )
                    );
                    break;
                case 'w': case 'W':
                    pos.z -= step;
                    break;
                case 's': case 'S':
                    pos.z += step;
                    break;
                case 'a': case 'A':
                    pos.x -= step;
                    break;
                case 'd': case 'D':
                    pos.x += step;
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
                default:
                    break;
            }
            light->set_position(pos);

    });

    // Scene setup
    saved_material = gen_rand_mat();
    saved_plane =  std::make_shared<lrvg::Plane>();
    saved_plane->set_name("Ground");
    saved_plane->set_position(glm::vec3(0.0f, -1.0f, 0.0f));
    saved_plane->set_scale(glm::vec3(10.0f));
    saved_plane->set_cast_shadows(false);
    saved_plane->set_material(saved_material);
    root->add_child(saved_plane);
    saved_sphere = std::make_shared<lrvg::Sphere>();
    saved_sphere->set_name("Sphere");
    saved_sphere->set_position(glm::vec3(-2.0f, 0.0f, 0.0f));
    saved_sphere->set_cast_shadows(false);
    saved_sphere->set_material(saved_material);
    root->add_child(saved_sphere);
    saved_cube = std::make_shared<lrvg::Cube>();
    saved_cube->set_name("Cube");
    saved_cube->set_position(glm::vec3(2.0f, 0.0f, 0.0f));
    saved_cube->set_cast_shadows(false);
    saved_cube->set_material(saved_material);
    root->add_child(saved_cube);
    auto light = std::make_shared<lrvg::PointLight>();
    light->set_name("Main Light");
    light->set_position(glm::vec3(5.0f, 1.0f, 5.0f));
    root->add_child(light);
    if (LIKELY(saved_ortho_camera == nullptr || saved_persp_camera == nullptr)) {
        std::shared_ptr<lrvg::OrthoCamera> camera_1 = std::make_shared<lrvg::OrthoCamera>();
        camera_1->set_zoom(zoom);
        camera_1->set_name("Camera");
        camera_1->set_position(glm::vec3(0.0f, 10.0f, 0.0f));
        camera_1->set_rotation(glm::vec3(-90.0f, 0.0f, 0.0f));
        std::shared_ptr<lrvg::PerspectiveCamera> camera_2 = std::make_shared<lrvg::PerspectiveCamera>();
        camera_2->set_name("Camera 2");
        camera_2->set_position(glm::vec3(0.0f, 0.0f, 10.0f));
        camera_2->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
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


