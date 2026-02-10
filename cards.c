#include "cards.h"
/**
 * @file cards.c
 * Implements functions for managing cards.
 */

/**
 * Checks if a given card is valid based on its rank and suit.
 */
bool is_valid_card(Card card)
{
    bool valid_rank = (card.rank >= 1) && (card.rank <= 13);
    // Valid ranks are 1 (Ace) to 13 (King)
    bool valid_suit = (card.suit >= HEARTS) && (card.suit <= SPADES);
    // Valid suits are HEARTS, DIAMONDS, CLUBS, SPADES
    return valid_rank && valid_suit;
    // A card is valid if both its rank and suit are valid
}

/**
 * Compares two cards for equality based on their rank and suit.
 */
bool compare_cards(Card card1, Card card2)
{
    // Two cards are considered the same if they have the same rank and suit
    bool same_rank = (card1.rank == card2.rank);
    bool same_suit = (card1.suit == card2.suit);
    return same_rank && same_suit;
}

/**
 * Checks if a card is exactly 1 lower in rank than another card.
 */
bool is_lower_rank(Card card1, Card card2)
{
    // card1 is considered lower than card2 if its rank is exactly 1 less than card2's rank (descending sequence)
    return (card1.rank == card2.rank - 1);
}

/**
 * Helper function to determine the color of a card based on its suit.
 * Returns true for red cards (Hearts and Diamonds) and false for black cards (Clubs and Spades).
 */
bool get_card_color(Card card)
{
    // Hearts and Diamonds are red, Clubs and Spades are black
    if (card.suit == HEARTS || card.suit == DIAMONDS)
    {
        return true; // Red
    }
    else
    {
        return false; // Black
    }
}

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