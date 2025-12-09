/**
 * @file	hanoi_game.h
 * @brief	Hanoi Tower game logic
 */

#ifndef HANOI_GAME_H
#define HANOI_GAME_H

#include <vector>

class HanoiGame {
private:
    std::vector<int> towers[3];
    int num_disks;

public:
    HanoiGame(int disks = 3);
    
    void reset();
    bool is_valid_move(int from, int to) const;
    bool move_disk(int from, int to);
    bool is_victory() const;
    bool is_tower_empty(int tower) const;
    int get_tower_size(int tower) const;
    int get_top_disk(int tower) const;
    const std::vector<int>& get_tower(int tower) const;
};

#endif
