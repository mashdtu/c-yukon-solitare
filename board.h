#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include "rules.h"
#include "cards.h"
/**
 * @file board.h
 * Defines the structure for the game board and hand.
 */

typedef struct
{
    Card cards[TABLEAU_MAX_SIZE];
    int size;            // Number of cards currently in hand
    int origin_tableau;  // Index of the tableau where the hand came from
    int origin_position; // Starting position in the tableau
} Hand;

typedef struct
{
    Foundation foundations[NUM_SUITS];
    Tableau tableaus[NUM_TABLEAUS];
    Hand hand; // For managing the cards that are currently being moved.
} Board;

Board *create_board();
void initialize_board(Board *board);
void free_board(Board *board);
#endif // GAME_H