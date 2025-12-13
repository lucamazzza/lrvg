/**
 * @file	hanoi_game.cpp
 * @brief	Hanoi Tower game logic implementation
 *
 * This file implements the HanoiGame class, which encapsulates the logic
 * for the Tower of Hanoi puzzle, including tower management, move validation,
 * and victory conditions.
 *
 * @author  Luca Mazza          (C) SUPSI [luca.mazza@student.supsi.ch]
 * @author  Roeld Hoxha         (C) SUPSI [roeld.hoxha@student.supsi.ch]
 * @author  Vasco Silva Pereira (C) SUPSI [vasco.silvapereira@student.supsi.ch]
 */

#include "hanoi_game.h"

/**
 * Constructs a HanoiGame with the specified number of disks
 *
 * @param disks	Number of disks in the Tower of Hanoi game
 */
HanoiGame::HanoiGame(int disks) : num_disks(disks) {
    reset();
}

/**
 * Resets the game to the initial state
 */
void HanoiGame::reset() {
    towers[0].clear();
    towers[1].clear();
    towers[2].clear();
    for (int i = num_disks; i >= 1; i--) {
        towers[2].push_back(i);
    }
}

/**
 * Checks if moving a disk from one tower to another is valid
 *
 * @param from Source tower index
 * @param to Destination tower index
 * @return True if the move is valid, false otherwise
 */
bool HanoiGame::is_valid_move(int from, int to) const {
    if (towers[from].empty()) return false;
    if (towers[to].empty()) return true;
    return towers[from].back() < towers[to].back();
}

/**
 * Moves a disk from one tower to another if the move is valid
 *
 * @param from	Source tower index
 * @param to Destination tower index
 * @return True if the move was successful, false otherwise
 */
bool HanoiGame::move_disk(int from, int to) {
    if (is_valid_move(from, to)) {
        int disk = towers[from].back();
        towers[from].pop_back();
        towers[to].push_back(disk);
        return true;
    }
    return false;
}

/**
 * Checks if the game has been won
 *
 * @return True if all disks are on one of the target towers, false otherwise
 */
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

/**
 * Checks if a tower is empty
 *
 * @param tower	Tower index to check
 * @return True if the tower is empty, false otherwise
 */
bool HanoiGame::is_tower_empty(int tower) const {
    return towers[tower].empty();
}

/**
 * Gets the number of disks on a tower
 *
 * @param tower Tower index
 * @return Number of disks on the tower
 */
int HanoiGame::get_tower_size(int tower) const {
    return towers[tower].size();
}

/**
 * Gets the top disk of a tower
 *
 * @param tower	Tower index
 * @return Size of the top disk, or -1 if the tower is empty
 */
int HanoiGame::get_top_disk(int tower) const {
    if (towers[tower].empty()) return -1;
    return towers[tower].back();
}

/**
 * Gets the disks on a tower
 *
 * @param tower	Tower index
 * @return Reference to the vector of disks on the tower
 */
const std::vector<int>& HanoiGame::get_tower(int tower) const {
    return towers[tower];
}
