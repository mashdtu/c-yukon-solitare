#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include "rules.h"
#include "cards.h"
/**
 * @file board.h
 * Defines the structures for representing the game board and hand,
 * as well as the functions for creating, initializing, and freeing the board.
 */

/**
 * Represents the player's hand when moving cards.
 */
typedef struct
{
    Card cards[TABLEAU_MAX_SIZE];
    uint8_t size;               // Represents the number of cards currently in hand
    wtf origin_tableau;      // Represents the index of the tableau where the hand came from
    int8_t origin_position;     // Represents the starting position in the tableau
} Hand;

/**
 * Represents the game board,
 * which consists of foundations, tableaus, and the player's hand.
 */
typedef struct
{
    Foundation foundations[NUM_SUITS];
    Tableau tableaus[NUM_TABLEAUS];
    Hand hand; // Hand holds the cards that are currently being moved.
} Board;

Board *create_board();
void initialize_board(Board *board);
void free_board(Board *board);
#endif // BOARD_H