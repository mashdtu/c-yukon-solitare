#include <stdbool.h>

#ifndef CARDS_H
#define CARDS_H

#include "rules.h"
#include <stdbool.h>

/**
 * @file cards.h
 * Defines the structures for
 * representing playing cards, foundations, and tableaus.
 */

/**
 * Enum for the four suits in the deck of cards.
 */
typedef enum
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
} Suit;

/**
 * Represents a playing card with a rank and suit.
 */
typedef struct
{
    int rank;          // 1–13 (Ace=1, Jack=11, Queen=12, King=13)
    bool is_face_down; // Indicates if the card is facing down (default: false)
    Suit suit;
} Card;

/**
 * Represents a foundation pile in the game which holds cards of a specific suit.
 */
typedef struct
{
    Card cards[FOUNDATION_SIZE];
    int top;   // Index of the top card
    Suit suit; // Suit of the foundation
} Foundation;

/**
 * Represents a tableau pile in the game.
 */
typedef struct
{
    Card cards[TABLEAU_MAX_SIZE];
    int top; // Index of the top card
} Tableau;

bool is_valid_card(Card card);
bool compare_cards(Card card1, Card card2);
bool is_lower_rank(Card card1, Card card2);
bool get_card_color(Card card);

#endif // CARDS_H