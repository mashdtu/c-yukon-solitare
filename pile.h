#ifndef PILE_H
#define PILE_H

#include "cards.h"
#include <stdbool.h>

bool can_place_on_tableau(Card hand_card, Card tableau_card);
bool can_place_on_foundation(Card hand_card, Card foundation_card, Suit foundation_suit);

#endif // PILE_H
