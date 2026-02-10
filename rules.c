#include "cards.h"
#include "board.h"
#include "rules.h"
#include <stdbool.h>

/**
 * @file rules.c
 * Implements the functions for validating moves according to the game rules.
 */

/**
 * Checks if a card can be placed on top of a foundation pile
 * A card can be placed on a foundation pile if it is the same suit
 * and one rank higher than the top card
 * or if the foundation is empty and the card is an Ace.
 */
bool can_place_on_foundation(Card card, Card top_card, Suit foundation_suit)
{
    // Suit must match foundation
    if (card.suit != foundation_suit)
        return false;
    // If foundation is empty allow an Ace
    if (top_card.rank == 0)
        return card.rank == 1;
    // Find the expected card that should be placed on the foundation based on the top card
    Card expected_card = get_next_card(top_card);

    // Check if the card being placed matches the expected card for the foundation
    return compare_cards(card, expected_card);
}

/**
 * Checks if a card can be placed on top of a tableau pile
 * A card can be placed on a tableau pile if it is one rank
 * lower and of the opposite color than the top card.
 */
bool can_place_on_tableau(Card card, Card top_card)
{
    // If tableau is empty (top_card.rank == 0), only allow King
    if (top_card.rank == 0)
        return card.rank == 13; // King
    // Otherwise, check if the card is one rank lower and of opposite color
    bool is_one_rank_lower = is_lower_rank(card, top_card);
    bool is_opposite_color = (get_card_color(card) != get_card_color(top_card));

    return is_one_rank_lower && is_opposite_color;
}