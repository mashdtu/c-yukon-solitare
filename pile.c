#include "cards.h"
#include "board.h"
#include "rules.h"
#include "constants.h"
#include <stddef.h>

/**
 * @file pile.c
 * Implements functions for managing foundation and tableau piles
 * including picking up cards, placing cards on tableau and foundation,
 */

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

/**
 * Picks up a specified number of cards from a tableau and moves them to the hand.
 * The cards must be face-up.
 */
void pick_up_cards(Board *board, int tableau_index, int num_cards)
{
    // Check for valid tableau index
    if (tableau_index < 0 || tableau_index >= NUM_TABLEAUS)
        return;

    Tableau *tableau = &board->tableaus[tableau_index];

    // Check if there are enough cards to pick up
    if (num_cards <= 0 || num_cards > tableau->top + 1)
        return;

    // Check if all cards to be picked up are face-up
    int start = tableau->top - num_cards + 1;
    for (int i = start; i <= tableau->top; i++)
    {
        if (tableau->cards[i].is_face_down)
        {
            return; // Invalid move, do nothing
        }
    }

    // Move cards to hand struct
    board->hand.size = num_cards;
    board->hand.origin_tableau = tableau_index;
    board->hand.origin_position = start;
    for (int i = 0; i < num_cards; i++)
    {
        board->hand.cards[i] = tableau->cards[start + i];
    }
    tableau->top -= num_cards;
    // Automatic turning of face-down card after picking up cards
    if (tableau->top >= 0 && tableau->cards[tableau->top].is_face_down)
    {
        tableau->cards[tableau->top].is_face_down = false;
    }
}

/**
 * Handles the logic for putting cards back to the original tableau
 * if the move is invalid.
 * This function can be called when the player tries to move cards
 * but the move is not allowed.
 */
void return_cards_to_tableau(Board *board)
{
    if (board->hand.size == 0)
        return; // No cards in hand, nothing to return
    int tableau_index = board->hand.origin_tableau;
    int position = board->hand.origin_position;
    Tableau *tableau = &board->tableaus[tableau_index];
    for (int i = 0; i < board->hand.size; i++)
    {
        tableau->cards[position + i] = board->hand.cards[i];
    }
    tableau->top += board->hand.size;
    board->hand.size = 0; // Clear hand after returning cards
}

/**
 * Handles the logic for placing cards from the hand onto a tableau.
 */
void place_cards_on_tableau(Board *board, int tableau_index)
{
    // Check for valid tableau index
    if (tableau_index < 0 || tableau_index >= NUM_TABLEAUS)
        return;

    Tableau *tableau = &board->tableaus[tableau_index];

    // Check if the move is valid according to game rules
    if (board->hand.size == 0)
        return; // No cards in hand, nothing to place

    Card top_card = (tableau->top >= 0) ? tableau->cards[tableau->top] : (Card){0};
    // Prevent moves onto tableau with face-down top card
    if (tableau->top >= 0 && tableau->cards[tableau->top].is_face_down)
    {
        return_cards_to_tableau(board);
        return;
    }
    // Yukon rule: only require the first card in hand and the tableau's top card to be in sequence and alternate color
    // Validate placing the first card of hand on tableau
    if (tableau->top < 0)
    {
        // Tableau is empty, only allow King
        if (board->hand.cards[0].rank != 13)
        {
            return_cards_to_tableau(board);
            return;
        }
    }
    else
    {
        if (!can_place_on_tableau(board->hand.cards[0], top_card))
        {
            return_cards_to_tableau(board);
            return;
        }
    }

    // Place cards on tableau
    for (int i = 0; i < board->hand.size; i++)
    {
        tableau->cards[++tableau->top] = board->hand.cards[i];
    }
    board->hand.size = 0; // Clear hand after placing cards

    // Automatic turning of face-down card after moving all face-up cards
    if (tableau->top >= 0 && tableau->cards[tableau->top].is_face_down)
    {
        tableau->cards[tableau->top].is_face_down = false;
    }
}

/**
 * Handles the logic for placing a card from the hand onto a foundation.
 */
void place_card_on_foundation(Board *board, int foundation_index)
{
    // Check for valid foundation index
    if (foundation_index < 0 || foundation_index >= NUM_SUITS)
        return;
    Foundation *foundation = &board->foundations[foundation_index];
    // Foundation move restriction: only allow one card to be moved
    if (board->hand.size != 1)
        return;
    Card top_card = (foundation->top >= 0) ? foundation->cards[foundation->top] : (Card){0};
    if (!can_place_on_foundation(board->hand.cards[0], top_card, foundation->suit))
    {
        return_cards_to_tableau(board);
        return;
    }
    // Place card on foundation
    foundation->cards[++foundation->top] = board->hand.cards[0];
    board->hand.size = 0;
}