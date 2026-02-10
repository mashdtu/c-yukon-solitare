#include "cards.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include <time.h>

/**
 * @file deck.c
 * Implements functions for managing the deck.
 */

/**
 * Seeds the random number generator for shuffling the deck.
 */
void seed_deck_random()
{
    // Seed the random number generator with the current time to ensure different shuffle each run
    srand(time(NULL));
}

/**
 * Shuffles a deck of cards.
 */
void shuffle_deck(Card *deck)
{
    // Implements the Fisher-Yates shuffle algorithm to randomize the order of the deck
    // Loop through the deck from the last card to the first
    for (int i = DECK_SIZE - 1; i > 0; i--)
    {
        // Generate a random index from 0 to i
        int j = rand() % (i + 1);
        // Swap the cards at indices i and j
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

/**
 * Creates and returns a pointer to a new sorted deck.
 */
Card *create_deck()
{
    // Seed the random number generator
    seed_deck_random();
    // Allocate memory for the deck of cards
    Card *deck = malloc(DECK_SIZE * sizeof(Card));
    if (deck == NULL)
    {
        // If memory allocation fails throw an error and exit
        fprintf(stderr, "Error: Unable to allocate memory for deck.\n");
        exit(EXIT_FAILURE);
    }
    // Initialize the deck with cards in sorted order
    int index = 0;
    // Loop through each suit and rank to populate the deck
    for (int suit = 0; suit < NUM_SUITS; suit++)
    {
        for (int rank = 1; rank <= FOUNDATION_SIZE; rank++)
        {
            deck[index].rank = rank;
            deck[index].suit = (Suit)suit;
            // Move to the next index in the deck
            index++;
        }
    }
    // Return the pointer to the deck
    return deck;
}

/**
 * Frees the memory allocated for the deck.
 */
void free_deck(Card *deck)
{
    free(deck);
}

/**
 * Draws a card from the deck and returns it,
 * removing it from the deck.
 * (Pops the top card from the deck array and returns it)
 */
Card draw_card(Card *deck, int *size)
{
    // Check if the deck is empty before drawing a card
    if (*size <= 0)
    {
        // If the deck is empty throw an error and exit
        fprintf(stderr, "Error: Cannot draw from an empty deck.\n");
        exit(EXIT_FAILURE);
    }
    // Get the top card from the deck
    Card drawn_card = deck[*size - 1];
    // Decrease the size of the deck to remove the drawn card
    (*size)--;
    // Return the drawn card
    return drawn_card;
}