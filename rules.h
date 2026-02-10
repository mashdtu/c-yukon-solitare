#ifndef RULES_H
#define RULES_H

#include <stdbool.h>
#include "cards.h"

/**
 * @file rules.h
 * Defines the functions for validating moves according to the game rules.
 */

bool can_place_on_tableau(Card card, Card top_card);
bool can_place_on_foundation(Card card, Card top_card, Suit foundation_suit);

#endif // RULES_H