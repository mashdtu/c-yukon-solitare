#include "cards.h"
#include "board.h"
#include "rules.h"
#include "constants.h"
#include <stddef.h>

/**
 * @file pile.c
 * Implements the functions for managing foundation and tableau piles
 */

/**
 * Helper function to get the top card of a pile (tableau or foundation).
 * Returns a pointer to the top card or NULL if the pile is empty.
 */
Card *get_top_pile_card(Card *cards, int top)
{
    if (top < 0)
        return NULL;
    return &cards[top];
}

/**
 * "Picks up" num_cards cards from a tableau and moves them to the hand.
 * The cards must be face-up.
 */
void pick_up_cards(Board *board, int tableau_index, int num_cards)
{
    // Check if the tableau index is valid
    if (tableau_index < 0 || tableau_index >= NUM_TABLEAUS)
        // If the tableau index is invalid, return
        return;

    // Get the pointer to the chosen tableau
    Tableau *tableau = &board->tableaus[tableau_index];

    // Check if there are enough cards to pick up
    if (num_cards <= 0 || num_cards > tableau->top + 1)
        // If there are not enough cards to pick up, return
        return;

    // Check if any of the cards to be picked up are face-down

    // The starting index of the cards to pick up is calculated as:
    // the top index minus the number of cards plus one
    int start = tableau->top - num_cards + 1;
    // Loop through the cards to be picked up and check if any are face-down
    for (int i = start; i <= tableau->top; i++)
    {
        // If any card in the range is face-down
        if (tableau->cards[i].is_face_down)
        {
            return; // Return without picking up cards
        }
    }

    // Move cards to hand struct

    // Set the hand's size to the number of cards being picked up
    board->hand.size = num_cards;
    // Set the hand's origin tableau index and position for potential return
    // if the move is invalid
    board->hand.origin_tableau = tableau_index;

    board->hand.origin_position = start;
    // Loop through the cards being picked up
    for (int i = 0; i < num_cards; i++)
    {
        // Copy each card from the tableau to the hand
        board->hand.cards[i] = tableau->cards[start + i];
    }
    // Remove cards from tableau by adjusting the top index
    tableau->top -= num_cards;
    // If the move leaves a face-down card on top of the tableau
    if (tableau->top >= 0 && tableau->cards[tableau->top].is_face_down)
    {
        // Turn the face-down card face-up
        tableau->cards[tableau->top].is_face_down = false;
    }
}

/**
 * Handles the logic for putting cards back to the original tableau
 * if the move is invalid.
 */
void return_cards_to_tableau(Board *board)
{
    // Check if there are cards in hand to return
    if (board->hand.size == 0)
        return; // No cards in hand, return
    // Get the original tableau index and position from the hand struct
    int tableau_index = board->hand.origin_tableau;
    int position = board->hand.origin_position;
    // Check if the tableau index is valid
    if (tableau_index < 0 || tableau_index >= NUM_TABLEAUS)
        return;
    // Get the pointer to the original tableau
    Tableau *tableau = &board->tableaus[tableau_index];
    // Loop through the cards in hand
    for (int i = 0; i < board->hand.size; i++)
    {
        // Place each card back onto the tableau at the correct position
        tableau->cards[position + i] = board->hand.cards[i];
    }
    // Adjust the tableau's top index based on the returned cards
    tableau->top += board->hand.size;
    board->hand.size = 0; // Clear hand after returning cards
}

/**
 * Handles the logic for placing cards from the hand onto a tableau.
 */
void place_cards_on_tableau(Board *board, int tableau_index)
{
    // Check if the tableau index is valid
    if (tableau_index < 0 || tableau_index >= NUM_TABLEAUS)
        return;

    // Get the pointer to the tableau
    Tableau *tableau = &board->tableaus[tableau_index];

    // Check if there are cards in hand to place
    if (board->hand.size == 0)
        return; // No cards in hand, return

    Card top_card; // Variable to hold the top card of the tableau
    // If the tableau is not empty
    if (tableau->top >= 0)
    {
        // Get the top card
        top_card = tableau->cards[tableau->top];
    }
    else
    {
        /* If the tableau is empty, use a "null" card with rank 0 and suit 0 for validation
        (This allows us to check if the first card being placed is a King,
        which is the only valid move onto an empty tableau) */
        top_card = (Card){0};
    }
    // Prevent moves going to a tableau with face-down top card
    if (tableau->top >= 0 && tableau->cards[tableau->top].is_face_down)
    {
        return_cards_to_tableau(board);
        return;
    }

    // Yukon rule: only require the first card in hand and the tableau's top card to be in sequence and alternate color

    // Validate placing the first card of hand on tableau
    if (tableau->top < 0)
    {
        // If tableau is empty, only allow King
        if (board->hand.cards[0].rank != 13)
        {
            return_cards_to_tableau(board);
            return;
        }
    }
    else // If tableau is not empty
    {
        // Check if the move is valid according to the rules
        if (!can_place_on_tableau(board->hand.cards[0], top_card))
        {
            // If the move is invalid return cards to original tableau
            return_cards_to_tableau(board);
            return;
        }
    }

    // Place cards on tableau
    for (int i = 0; i < board->hand.size; i++)
    {
        // Place each card from the hand onto the tableau
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
    // Get the pointer to the foundation
    Foundation *foundation = &board->foundations[foundation_index];
    // Only allow one card to be moved
    if (board->hand.size != 1)
        return;
    // Get the top card of the foundation for validation
    Card top_card;
    // If the foundation is not empty get the top card
    if (foundation->top >= 0)
    {
        top_card = foundation->cards[foundation->top];
    }
    else // If the foundation is empty
    {
        // Use a "null" card with rank 0 and suit 0 for validation
        top_card = (Card){0};
    }
    // Validate placing the card in hand on foundation
    if (!can_place_on_foundation(board->hand.cards[0], top_card, foundation->suit))
    {
        // If the move is invalid return card to original tableau
        return_cards_to_tableau(board);
        return;
    }
    // Place card on foundation
    foundation->cards[++foundation->top] = board->hand.cards[0];
    // Clear hand after placing card
    board->hand.size = 0;
}