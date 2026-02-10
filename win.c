#include "win.h"
#include "board.h"

/**
 * Checks if the game has been won by verifying if all foundations are complete.
 * The game is won when all foundations have 13 cards (from Ace to King).
 */
bool check_win_condition(Board *board)
{
    for (int i = 0; i < NUM_SUITS; i++)
    {
        if (board->foundations[i].top != 12) // Each foundation should have
            return false;                    // 13 cards (index 0 to 12)
    }
    return true; // All foundations are complete, game is won
}