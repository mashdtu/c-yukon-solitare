#ifndef DECK_H
#define DECK_H

#include "cards.h"

/**
 * @file deck.h
 * Declares functions for managing the deck of cards.
 */

Card *create_deck();
void shuffle_deck(Card *deck);
void free_deck(Card *deck);

#endif // DECK_H
