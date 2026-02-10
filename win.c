#include "win.h"
#include "board.h"

/**
 * @file win.c
 * Implements the function to check for win condition.
 */
bool check_win_condition(Board *board)
{
    for (int i = 0; i < NUM_SUITS; i++)
    {
        if (board->foundations[i].top != 12) // Each foundation should have
            return false;                    // 13 cards (index 0 to 12)
    }
    return true; // If all foundations are complete the game is won
}