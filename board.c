#include "board.h"
#include "deck.h"
#include "rules.h"
#include "constants.h"
#include "pile.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file Board.c
 * Implements functions for managing the game board.
 */

/**
 * Returns a pointer to a new empty initialized game board.
 */
Board *create_board()
{
    // Allocate memory for the game board
    Board *board = malloc(sizeof(Board));
    if (board == NULL)
    {
        // If memory allocation fails print an error and exit
        fprintf(stderr, "Error: Unable to allocate memory for game board.\n");
        exit(EXIT_FAILURE);
    }
    // Initialize foundations
    for (int i = 0; i < NUM_SUITS; i++)
    {
        board->foundations[i].top = -1;       // No cards in foundation
        board->foundations[i].suit = (Suit)i; // Set the suit for foundation
    }
    // Initialize tableaus
    for (int i = 0; i < NUM_TABLEAUS; i++)
    {
        board->tableaus[i].top = -1; // No cards in tableau
    }
    // Initialize hand struct
    board->hand.size = 0;
    board->hand.origin_tableau = -1;
    board->hand.origin_position = -1;
    memset(board->hand.cards, 0, sizeof(board->hand.cards));
    return board;
}

/**
 * Frees the memory allocated for the game board.
 */
void free_board(Board *board)
{
    free(board);
}

/**
 * Generates a deck of cards and populates the game board with the appropriate cards.
 */
void initialize_board(Board *board)
{
    // Initialize deck of cards
    Card *deck = create_deck();
    // Shuffle the deck before dealing cards to the tableaus
    shuffle_deck(deck);
    // Populate the tableaus with cards from the deck according to the rules
    int deck_index = 0;
    for (int i = 0; i < NUM_TABLEAUS; i++)
    {
        // Add i face-down cards
        for (int j = 0; j < i; j++)
        {
            Card card = deck[deck_index++];
            card.is_face_down = true;
            board->tableaus[i].cards[++board->tableaus[i].top] = card;
        }
        // Add 5 face-up cards (or 1 for the first tableau)
        int num_face_up = (i == 0) ? 1 : 5;
        for (int j = 0; j < num_face_up; j++)
        {
            Card card = deck[deck_index++];
            card.is_face_down = false;
            board->tableaus[i].cards[++board->tableaus[i].top] = card;
        }
    }
    // Free the deck after initializing the board (no longer needed)
    free_deck(deck);
}
