/**
 * @file	game_controller.h
 * @brief	Game controller for handling input and state
 *
 * This file defines the GameController class, which manages user input,
 * game state, and interactions with the HanoiGame logic.
 *
 * @author	Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author	Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author	Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */
#pragma once

#include "hanoi_game.h"
#include <memory>
#include <node.h>

/**
 * @class	GameController
 * @brief	Handles user input and game state for Tower of Hanoi
 *
 * The GameController class manages the interaction between the user and the
 * HanoiGame logic. It processes tower selections, resets the game, checks for
 * victory conditions, and can automatically solve the puzzle.
 */
class GameController {
private:
    HanoiGame game;
    int selected_tower;
    std::shared_ptr<lrvg::Node> disk_nodes[7];
    std::shared_ptr<lrvg::Node> pin_nodes[3];
    std::shared_ptr<lrvg::Node> disk_original_parents[7];
    
    std::vector<std::pair<int, int>> solve_moves;
    size_t current_move;
    float move_timer;
    bool is_autosolving;
    
    void update_disk_hierarchy();
    void remove_disk_from_current_parent(int disk_id);
    void highlight_disk(int disk_id, bool highlight);

public:
    GameController(int num_disks = 3);
    
    void init_scene_nodes();
    void handle_tower_selection(int tower);
    void reset_game();
    bool check_victory() const;
    void autosolve();
    void update(float dt);
};
