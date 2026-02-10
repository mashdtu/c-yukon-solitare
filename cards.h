#ifndef CARDS_H
#define CARDS_H

#include "constants.h"
#include <stdbool.h>

/**
 * @file cards.h
 * Defines the structures and functions for managing cards in the game.
 */

/**
 * Enum representing the four suits in the deck.
 */
typedef enum
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
} Suit;

/**
 * Represents a card with a rank and suit.
 */
typedef struct
{
    int rank;          // 1–13 (Ace=1, Jack=11, Queen=12, King=13)
    bool is_face_down; // Indicates if the card is face down (true) or face up (false)
    Suit suit;
} Card;

/**
 * Represents a foundation pile in the game that holds cards of a specific suit.
 */
typedef struct
{
    Card cards[FOUNDATION_SIZE]; // Array to hold cards in the foundation
    int top;                     // Index of the top card
    Suit suit;                   // Suit of the foundation
} Foundation;

/**
 * Represents a tableau pile in the game.
 */
typedef struct
{
    Card cards[TABLEAU_MAX_SIZE]; // Array to hold cards in the tableau
    int top;                      // Index of the top card
} Tableau;

bool is_valid_card(Card card);
bool compare_cards(Card card1, Card card2);
bool is_lower_rank(Card card1, Card card2);
bool get_card_color(Card card);
Card get_next_card(Card card);

#endif // CARDS_H