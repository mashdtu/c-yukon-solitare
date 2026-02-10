#include "../board.h"
#include "../cards.h"
#include "../pile.h"
#include "../win.h"
#include "../rules.h"
#include "../constants.h"

#include <stdio.h>
#include <string.h>
#include "ascii_card.h"

// Print a card as a single Unicode character (with color)
extern const char *UNICODE_CARDS[4][13];
void print_card_symbol(const Card *card)
{
    const char *reset = "\033[0m";
    const char *bg_beige = "\033[48;5;230m";
    const char *color = "";
    if (card->is_face_down)
    {
        // Beige background, blue foreground for face-down cards
        printf("\033[48;5;230;34m🂠%s", reset);
        return;
    }
    if (card->suit == HEARTS || card->suit == DIAMONDS)
        color = "\033[48;5;230;31m"; // beige bg, red fg
    else
        color = "\033[48;5;230;30m"; // beige bg, black fg
    int suit = card->suit;
    int rank = card->rank;
    if (suit >= 0 && suit < 4 && rank >= 1 && rank <= 13)
        printf("%s%s%s", color, UNICODE_CARDS[suit][rank - 1], reset);
    else
        printf("%s %s", bg_beige, reset);
}

// Print tableau with foundations to the right
void print_tableaus_and_foundations(const Board *board)
{
    int max_height = 0;
    for (int t = 0; t < NUM_TABLEAUS; t++)
    {
        int h = board->tableaus[t].top + 1;
        if (h > max_height)
            max_height = h;
    }
    // Print tableau rows
    int total_cells = NUM_TABLEAUS * 2 + 8 + 6; // 2 spaces per tableau, 8 for foundation/suits, 6 for extra padding
    for (int row = 0; row < max_height; ++row)
    {
        int cell_count = 0;
        for (int t = 0; t < NUM_TABLEAUS; ++t)
        {
            int pile_height = board->tableaus[t].top + 1;
            if (row < pile_height)
            {
                print_card_symbol(&board->tableaus[t].cards[row]);
            }
            else
            {
                printf("\033[48;5;230m \033[0m");
            }
            printf("\033[48;5;230m \033[0m");
            cell_count += 2;
        }
        // Print foundations one row lower (start at row==1)
        if (row >= 1 && row < 1 + NUM_SUITS)
        {
            int fidx = row - 1;
            printf("\033[48;5;230m   \033[0m");
            cell_count += 3;
            if (board->foundations[fidx].top >= 0)
            {
                const Card *fcard = &board->foundations[fidx].cards[board->foundations[fidx].top];
                if (fcard->suit == HEARTS || fcard->suit == DIAMONDS)
                    printf("\033[48;5;230;31m%s\033[0m", UNICODE_CARDS[fcard->suit][fcard->rank - 1]);
                else
                    printf("\033[48;5;230;30m%s\033[0m", UNICODE_CARDS[fcard->suit][fcard->rank - 1]);
            }
            else
            {
                printf("\033[48;5;230m \033[0m");
            }
            cell_count++;
            // Print suit symbol with beige background and colored foreground
            const char *suits[] = {"♥", "♦", "♣", "♠"};
            const char *suit_colors[] = {"\033[48;5;230;31m", "\033[48;5;230;31m", "\033[48;5;230;30m", "\033[48;5;230;30m"};
            printf("%s%s\033[0m", suit_colors[fidx], suits[fidx]);
            cell_count++;
        }
        // Pad the rest of the line with beige background spaces
        for (; cell_count < total_cells; ++cell_count)
            printf("\033[48;5;230m \033[0m");
        printf("\n");
    }
    // Print tableau numbers below
    int cell_count = 0;
    for (int t = 0; t < NUM_TABLEAUS; ++t)
    {
        printf("\033[48;5;230;30m%d \033[0m", t + 1);
        cell_count++;
        printf("\033[48;5;230m \033[0m");
        cell_count++;
    }
    // Only pad to the same width as the card rows, but without the foundation/suit cells (NUM_SUITS + 1 for suit, +1 for space before foundation)
    int pad_cells = (NUM_TABLEAUS * 2 + 8 + 6 - NUM_TABLEAUS) - cell_count;
    for (int pad = 0; pad < pad_cells; ++pad)
        printf("\033[48;5;230m \033[0m");
    printf("\n");
}

void print_board(const Board *board)
{
    print_tableaus_and_foundations(board);
}

int main()
{
    Board *board = create_board();
    initialize_board(board);
    char command[64];
    int t_from, t_to, num, f_to;
    printf("Welcome to Yukon Solitaire!\nType 'help' for command info.\n\n");
    // Set terminal background to beige and text to black
    printf("\033[48;5;230;30m");
    print_board(board);
    while (1)
    {
        printf("> ");
        if (!fgets(command, sizeof(command), stdin))
            break;
        if (sscanf(command, "move %d %d %d", &t_from, &num, &t_to) == 3)
        {
            pick_up_cards(board, t_from - 1, num);
            place_cards_on_tableau(board, t_to - 1);
            print_board(board);
        }
        else if (sscanf(command, "movef %d %d %d", &t_from, &num, &f_to) == 3)
        {
            pick_up_cards(board, t_from - 1, num);
            place_card_on_foundation(board, f_to - 1);
            print_board(board);
        }
        else if (strncmp(command, "print", 5) == 0)
        {
            print_board(board);
        }
        else if (strncmp(command, "help", 4) == 0)
        {
            printf("Commands:\n");
            printf("  move <from> <num> <to>        - Move <num> cards from tableau <from> to tableau <to>\n");
            printf("  movef <from> <num> <foundation> - Move <num> cards from tableau <from> to foundation <foundation>\n");
            printf("  print                         - Print the board\n");
            printf("  quit                          - Exit the game\n");
            printf("  help                          - Show this help message\n");
        }
        else if (strncmp(command, "quit", 4) == 0)
        {
            break;
        }
        else
        {
            printf("Unknown command. Try: move <from> <num> <to>, movef <from> <num> <foundation>, print, quit\n");
        }
        if (check_win_condition(board))
        {
            printf("Congratulations, you won!\n");
            break;
        }
    }
    // Reset terminal colors (including background)
    printf("\033[0m");
    free_board(board);
    return 0;
}
