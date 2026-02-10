#include "../cards.h"
#include "test_deck.h"
#include "../deck.h"
#include <stdio.h>

// Helper function to print a single card (for testing)
void print_card(const Card *card)
{
    const char *suits_ascii[] = {"♥", "♦", "♣", "♠"};
    const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    printf("%s%s", suits_ascii[card->suit], ranks[card->rank - 1]);
}

// Helper function to print the entire deck (for testing)
void print_deck(const Card *deck)
{
    int cards_per_line = 13;
    for (int i = 0; i < DECK_SIZE; i++)
    {
        print_card(&deck[i]);
        if ((i + 1) % cards_per_line == 0 || i == DECK_SIZE - 1)
            printf("\n");
        else
            printf(" ");
    }
}

// Test function for deck creation and shuffling
void test_deck()
{
    Card *deck = create_deck();
    printf("Sorted Deck:\n");
    print_deck(deck);
    shuffle_deck(deck);
    printf("\nShuffled Deck:\n");
    print_deck(deck);
    free_deck(deck);
}

int main()
{
    test_deck();
    return 0;
}