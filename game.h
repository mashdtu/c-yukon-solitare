#ifndef GAME_H
#define GAME_H

#include "rules.h"
#include "cards.h"
/**
 * @file game.h
 * Defines the structure for the game board, which includes foundations and tableaus.
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
void pick_up_cards(Board *board, int tableau_index, int num_cards);
void place_cards_on_tableau(Board *board, int tableau_index);
void place_card_on_foundation(Board *board, int foundation_index);
bool check_win_condition(Board *board);
void pick_up_cards(Board *board, int tableau_index, int num_cards);
#endif // GAME_H