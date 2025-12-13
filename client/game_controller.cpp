/**
 * @file	game_controller.cpp
 * @brief	Game controller implementation
 *
 * This file implements the GameController class, which manages user input,
 * game state, and interactions with the HanoiGame logic.
 *
 * @author  Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author  Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author  Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "game_controller.h"
#include <engine.h>
#include <mesh.h>

/**
 * Constructs a GameController with the specified number of disks
 *
 * @param num_disks	Number of disks in the Tower of Hanoi game
 */
GameController::GameController(int num_disks) : game(num_disks), selected_tower(-1),
    current_move(0), move_timer(0.0f), is_autosolving(false) {
    disk_nodes[0] = nullptr;
    disk_nodes[1] = nullptr;
    disk_nodes[2] = nullptr;
    disk_nodes[3] = nullptr;
    disk_nodes[4] = nullptr;
    disk_nodes[5] = nullptr;
    disk_nodes[6] = nullptr;
    pin_nodes[0] = nullptr;
    pin_nodes[1] = nullptr;
    pin_nodes[2] = nullptr;
    disk_original_parents[0] = nullptr;
    disk_original_parents[1] = nullptr;
    disk_original_parents[2] = nullptr;
    disk_original_parents[3] = nullptr;
    disk_original_parents[4] = nullptr;
    disk_original_parents[5] = nullptr;
    disk_original_parents[6] = nullptr;
}

/**
 * Initializes scene nodes for disks and pins
 */
void GameController::init_scene_nodes() {
    disk_nodes[0] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Disk1"));
    disk_nodes[1] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Disk2"));
    disk_nodes[2] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Disk3"));
    disk_nodes[3] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Disk4"));
    disk_nodes[4] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Disk5"));
    disk_nodes[5] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Disk6"));
    disk_nodes[6] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Disk7"));
    
    pin_nodes[0] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Pin1"));
    pin_nodes[1] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Pin2"));
    pin_nodes[2] = std::dynamic_pointer_cast<lrvg::Node>(lrvg::Engine::find_obj_by_name("Pin3"));
    
    std::function<std::shared_ptr<lrvg::Node>(std::shared_ptr<lrvg::Node>, std::shared_ptr<lrvg::Node>)> find_parent;
    find_parent = [&find_parent](std::shared_ptr<lrvg::Node> root, std::shared_ptr<lrvg::Node> target) -> std::shared_ptr<lrvg::Node> {
        if (!root) return nullptr;
        auto children = root->get_children();
        for (auto child : children) {
            if (child == target) return root;
            auto found = find_parent(child, target);
            if (found) return found;
        }
        return nullptr;
    };
    
    auto scene_root = lrvg::Engine::get_scene();
    for (int i = 0; i < 7; i++) {
        if (disk_nodes[i]) {
            disk_original_parents[i] = find_parent(scene_root, disk_nodes[i]);
        }
    }
    
    update_disk_hierarchy();
}


/**
 * Removes a disk from its current parent node
 *
 * @param disk_id ID of the disk to remove
 */
void GameController::remove_disk_from_current_parent(int disk_id) {
    if (!disk_nodes[disk_id]) return;
    
    if (disk_original_parents[disk_id]) {
        disk_original_parents[disk_id]->remove_child(disk_nodes[disk_id]);
    }
    
    for (int i = 0; i < 3; i++) {
        if (pin_nodes[i]) {
            pin_nodes[i]->remove_child(disk_nodes[disk_id]);
        }
    }
    
    for (int i = 0; i < 7; i++) {
        if (disk_nodes[i] && disk_nodes[i] != disk_nodes[disk_id]) {
            disk_nodes[i]->remove_child(disk_nodes[disk_id]);
        }
    }
    
    disk_nodes[disk_id]->set_base_matrix(glm::mat4(1.0f));
    disk_nodes[disk_id]->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
    disk_nodes[disk_id]->set_rotation(glm::vec3(0.0f, 0.0f, 0.0f));
    disk_nodes[disk_id]->set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

/**
 * Highlights or unhighlights a disk
 *
 * @param disk_id ID of the disk to highlight/unhighlight
 * @param highlight	True to highlight, false to unhighlight
 */
void GameController::highlight_disk(int disk_id, bool highlight) {
    if (!disk_nodes[disk_id]) return;
    auto mesh = static_pointer_cast<lrvg::Mesh>(disk_nodes[disk_id]);
    
    if (highlight) {
        mesh->get_material()->set_emission_color(glm::vec3(1.0f, 1.0f, 1.0f));
    } else {
        mesh->get_material()->set_emission_color(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

/**
 * Updates the hierarchy of disks based on the game state
 */
void GameController::update_disk_hierarchy() {
    for (int disk_id = 0; disk_id < 7; disk_id++) {
        remove_disk_from_current_parent(disk_id);
    }
    
    for (int t = 0; t < 3; t++) {
        const auto& tower = game.get_tower(t);
        
        for (int i = 0; i < (int)tower.size(); i++) {
            int disk_id = tower[i] - 1;
            if (disk_id >= 0 && disk_id < 7 && disk_nodes[disk_id] && pin_nodes[t]) {
                float y_pos = i * 5.5f;
                glm::vec3 new_pos(0.0f, y_pos, 0.0f);
                disk_nodes[disk_id]->set_position(new_pos);
                pin_nodes[t]->add_child(disk_nodes[disk_id]);
            }
        }
    }
}

/**
 * Handles tower selection and disk movement
 *
 * @param tower	Index of the selected tower
 */
void GameController::handle_tower_selection(int tower) {
    if (selected_tower == -1) {
        if (!game.is_tower_empty(tower)) {
            selected_tower = tower;
            int top_disk = game.get_top_disk(tower);
            if (top_disk != -1) {
                highlight_disk(top_disk - 1, true);
            }
        }
    } else {
        int top_disk = game.get_top_disk(selected_tower);
        if (top_disk != -1) {
            highlight_disk(top_disk - 1, false);
        }
        if (tower != selected_tower) {
            if (game.move_disk(selected_tower, tower)) {
                update_disk_hierarchy();
                if (game.is_victory()) {
                    lrvg::Engine::set_center_text("You Won!");
                }
            }
        }
        selected_tower = -1;
    }
}

/**
 * Resets the game to the initial state
 */
void GameController::reset_game() {
    game.reset();
    selected_tower = -1;
    update_disk_hierarchy();
    lrvg::Engine::set_center_text("");
}

/**
 * Checks if the game has been won
 *
 * @return True if the game is won, false otherwise
 */
bool GameController::check_victory() const {
    return game.is_victory();
}

/**
 * Automatically solves the Tower of Hanoi puzzle
 */
void GameController::autosolve() {
    reset_game();
    solve_moves.clear();
    
    std::function<void(int, int, int, int)> generate_moves;
    generate_moves = [&](int n, int from, int to, int aux) {
        if (n == 1) {
            solve_moves.push_back({from, to});
            return;
        }
        generate_moves(n - 1, from, aux, to);
        solve_moves.push_back({from, to});
        generate_moves(n - 1, aux, to, from);
    };
    
    int num_disks = game.get_tower_size(0) + game.get_tower_size(1) + game.get_tower_size(2);
    generate_moves(num_disks, 2, 0, 1);
    
    current_move = 0;
    move_timer = 0.0f;
    is_autosolving = true;
}

/**
 * Updates the game state for automatic solving
 *
 * @param dt Time delta since last update
 */
void GameController::update(float dt) {
    if (!is_autosolving) return;
    
    move_timer += dt;
    if (move_timer >= 0.2f && current_move < solve_moves.size()) {
        move_timer = 0.0f;
        auto move = solve_moves[current_move];
        game.move_disk(move.first, move.second);
        update_disk_hierarchy();
        current_move++;
        
        if (current_move >= solve_moves.size()) {
            is_autosolving = false;
            lrvg::Engine::set_center_text("Solved!");
        }
    }
}
