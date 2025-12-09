/**
 * @file	hanoi_game.cpp
 * @brief	Hanoi Tower game logic implementation
 */

#include "hanoi_game.h"

HanoiGame::HanoiGame(int disks) : num_disks(disks) {
    reset();
}

void HanoiGame::reset() {
    towers[0].clear();
    towers[1].clear();
    towers[2].clear();
    for (int i = num_disks; i >= 1; i--) {
        towers[2].push_back(i);
    }
}

bool HanoiGame::is_valid_move(int from, int to) const {
    if (towers[from].empty()) return false;
    if (towers[to].empty()) return true;
    return towers[from].back() < towers[to].back();
}

bool HanoiGame::move_disk(int from, int to) {
    if (is_valid_move(from, to)) {
        int disk = towers[from].back();
        towers[from].pop_back();
        towers[to].push_back(disk);
        return true;
    }
    return false;
}

bool HanoiGame::is_victory() const {
    int total_disks = 0;
    for (int i = 0; i < num_disks; i++) {
        total_disks += (1 << i);
    }
    
    int tower0_sum = 0, tower1_sum = 0;
    for (int disk : towers[0]) tower0_sum += (1 << (disk - 1));
    for (int disk : towers[1]) tower1_sum += (1 << (disk - 1));
    
    return (tower0_sum == total_disks || tower1_sum == total_disks);
}

bool HanoiGame::is_tower_empty(int tower) const {
    return towers[tower].empty();
}

int HanoiGame::get_tower_size(int tower) const {
    return towers[tower].size();
}

int HanoiGame::get_top_disk(int tower) const {
    if (towers[tower].empty()) return -1;
    return towers[tower].back();
}

const std::vector<int>& HanoiGame::get_tower(int tower) const {
    return towers[tower];
}
