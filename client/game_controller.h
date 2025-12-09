/**
 * @file	game_controller.h
 * @brief	Game controller for handling input and state
 */

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "hanoi_game.h"
#include <memory>
#include <node.h>

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

#endif
