#ifndef PILE_H
#define PILE_H

#include "cards.h"
#include <stdbool.h>

void pick_up_cards(Board *board, int tableau_index, int num_cards);
void place_cards_on_tableau(Board *board, int tableau_index);
void place_card_on_foundation(Board *board, int foundation_index);
void pick_up_cards(Board *board, int tableau_index, int num_cards);

#endif // PILE_H
