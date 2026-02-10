#include "cards.h"
#include <stddef.h>

/**
 * @file pile.c
 * Implements functions for managing foundation and tableau piles.
 */

/**
 * Returns the next card in sequence based on the current card's rank and suit.
 * If the current card is a King (rank 13), returns a null card (rank 0, suit 0).
 */
Card get_next_card(Card card)
{
    // Define a variable to hold the next card
    Card next_card;

    // If the current card's rank is less than 13, increment the rank to get the next card
    if (card.rank < 13)
    {
        next_card.rank = card.rank + 1;
        next_card.suit = card.suit;
    }
    // If the current card is a King (rank 13), there is no next card, so return a null card
    else
    {
        next_card.rank = 0;
        next_card.suit = 0;
    }

    return next_card;
}

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

/**
 * Returns a pointer to the top card of a pile
 * (foundation or tableau) given the array of cards and
 * the index of the top card.
 *
 * If the pile is empty (top index is -1), returns NULL.
 * Example usage:
 * get_top_pile_card(tableau->cards, tableau->top);
 * get_top_pile_card(foundation->cards, foundation->top);
 */
Card *get_top_pile_card(Card *cards, int top)
{
    if (top < 0)
        return NULL;
    return &cards[top];
}