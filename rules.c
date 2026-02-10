#include "cards.h"
#include "board.h"
#include "rules.h"
#include <stdbool.h>

/**
 * Checks if a card can be placed on top of a foundation pile based on the game rules.
 * A card can be placed on a foundation pile if it is the next card in sequence and of the same suit.
 */
bool can_place_on_foundation(Card card, Card top_card, Suit foundation_suit)
{
    // Suit must match foundation
    if (card.suit != foundation_suit)
        return false;
    // If foundation is empty, allow Ace
    if (top_card.rank == 0)
        return card.rank == 1;
    Card expected_card = get_next_card(top_card);
    return compare_cards(card, expected_card);
}

/**
 * Checks if a card can be placed on top of a tableau pile
 * based on the game rules.
 * A card can be placed on a tableau pile if it is one rank
 * lower and of the opposite color than the top card.
 */
bool can_place_on_tableau(Card card, Card top_card)
{
    // If tableau is empty (top_card.rank == 0), only allow King
    if (top_card.rank == 0)
        return card.rank == 13; // King
    // Otherwise, check standard rule
    bool is_one_rank_lower = is_lower_rank(card, top_card);
    bool is_opposite_color = (get_card_color(card) != get_card_color(top_card));
    return is_one_rank_lower && is_opposite_color;
}