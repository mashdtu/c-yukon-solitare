#ifndef DECK_H
#define DECK_H

#include "cards.h"

/**
 * @file deck.h
 * Declares functions for managing the deck of cards.
 */

void shuffle_deck(Card *deck);
Card *create_deck();
void free_deck(Card *deck);

#endif // DECK_H
