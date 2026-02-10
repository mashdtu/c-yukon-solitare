
#include "../board.h"
#include "../cards.h"
#include "../pile.h"
#include "../win.h"
#include "../rules.h"
#include "../constants.h"
#include <stdio.h>
#include <string.h>

void print_card(const Card *card)
{
    const char *suits_ascii[] = {"♥", "♦", "♣", "♠"};
    const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    if (card->is_face_down)
    {
        printf("[X]"); // Print face-down card as [X] with no color or info
        return;
    }
    if (get_card_color(*card))
        printf("\033[31m"); // Red
    else
        printf("\033[90m"); // Gray
    printf("[%s%s]\033[0m", suits_ascii[card->suit], ranks[card->rank - 1]);
}

void print_tableaus(const Board *board)
{
    for (int t = 0; t < NUM_TABLEAUS; t++)
    {
        printf("Tableau %d: ", t + 1);
        for (int j = 0; j <= board->tableaus[t].top; j++)
        {
            print_card(&board->tableaus[t].cards[j]);
            printf(" ");
        }
        printf("\n");
    }
}

void print_foundations(const Board *board)
{
    for (int f = 0; f < NUM_SUITS; f++)
    {
        printf("Foundation %d (%s): ", f + 1, (f == 0 ? "♥" : f == 1 ? "♦"
                                                          : f == 2   ? "♣"
                                                                     : "♠"));
        for (int j = 0; j <= board->foundations[f].top; j++)
        {
            print_card(&board->foundations[f].cards[j]);
            printf(" ");
        }
        printf("\n");
    }
}

int main()
{
    Board *board = create_board();
    initialize_board(board);
    char command[64];
    int t_from, t_to, num, f_to;
    printf("Welcome to Yukon Solitaire!\nType 'help' for command info.\n\n");
    print_tableaus(board);
    print_foundations(board);
    while (1)
    {
        printf("\n> ");
        if (!fgets(command, sizeof(command), stdin))
            break;
        if (sscanf(command, "move %d %d %d", &t_from, &num, &t_to) == 3)
        {
            pick_up_cards(board, t_from - 1, num);
            place_cards_on_tableau(board, t_to - 1);
            print_tableaus(board);
            print_foundations(board);
        }
        else if (sscanf(command, "movef %d %d %d", &t_from, &num, &f_to) == 3)
        {
            pick_up_cards(board, t_from - 1, num);
            place_card_on_foundation(board, f_to - 1);
            print_tableaus(board);
            print_foundations(board);
        }
        else if (strncmp(command, "print", 5) == 0)
        {
            print_tableaus(board);
            print_foundations(board);
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
    free_board(board);
    return 0;
}
