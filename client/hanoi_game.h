/**
 * @file	hanoi_game.h
 * @brief	Hanoi Tower game logic
 *
 * This file defines the HanoiGame class, which encapsulates the logic
 * for the Tower of Hanoi puzzle, including tower management, move validation,
 * and victory conditions.
 *
 * @author  Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author  Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author  Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */
#pragma once

#include <vector>

/**
 * @class	HanoiGame
 * @brief	Encapsulates the logic for the Tower of Hanoi game
 *
 * The HanoiGame class manages the state of the Tower of Hanoi puzzle,
 * including the towers and disks. It provides methods to reset the game,
 * validate and perform moves, and check for victory conditions.
 */
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
