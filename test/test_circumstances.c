#include <stdbool.h>
#include "board.h"
#include "pile.h"
#include "win.h"
#include <stdio.h>
#include <stdbool.h>

#define CHECKMARK "\xE2\x9C\x94"
#define CROSS "\xE2\x9C\x98"

typedef bool (*TestFunc)();

// Test 10: Move group with only starting and target cards in sequence and alternate color
bool test_move_group_sequence_and_color_only()
{
    Board *board = create_board();
    // Tableau 0: Black 4 (Clubs, face up)
    board->tableaus[0].top = 0;
    board->tableaus[0].cards[0].rank = 4;
    board->tableaus[0].cards[0].suit = CLUBS;
    board->tableaus[0].cards[0].is_face_down = false;
    // Tableau 1: Red 3 (Hearts, face up), 7 of Spades, 2 of Diamonds (order below doesn't matter)
    board->tableaus[1].top = 2;
    board->tableaus[1].cards[0].rank = 3;
    board->tableaus[1].cards[0].suit = HEARTS;
    board->tableaus[1].cards[0].is_face_down = false;
    board->tableaus[1].cards[1].rank = 7;
    board->tableaus[1].cards[1].suit = SPADES;
    board->tableaus[1].cards[1].is_face_down = false;
    board->tableaus[1].cards[2].rank = 2;
    board->tableaus[1].cards[2].suit = DIAMONDS;
    board->tableaus[1].cards[2].is_face_down = false;
    // Pick up all 3 cards from tableau 1
    pick_up_cards(board, 1, 3);
    // Move group onto tableau 0
    place_cards_on_tableau(board, 0);
    // Should succeed: Black 4, Red 3, 7 of Spades, 2 of Diamonds
    bool result = (board->tableaus[0].top == 3 && board->tableaus[0].cards[0].rank == 4 && board->tableaus[0].cards[1].rank == 3);
    free_board(board);
    return result;
}

// Test 1: Move King to empty tableau
bool test_move_king_to_empty_tableau()
{
    Board *board = create_board();
    board->tableaus[0].top = -1;
    board->tableaus[1].top = 0;
    board->tableaus[1].cards[0].rank = 13; // King
    board->tableaus[1].cards[0].suit = HEARTS;
    board->tableaus[1].cards[0].is_face_down = false;
    pick_up_cards(board, 1, 1);
    place_cards_on_tableau(board, 0);
    bool result = (board->tableaus[0].top == 0 && board->tableaus[0].cards[0].rank == 13);
    free_board(board);
    return result;
}

// Test 2: Move non-King to empty tableau (should fail)
bool test_move_non_king_to_empty_tableau()
{
    Board *board = create_board();
    board->tableaus[0].top = -1;
    board->tableaus[1].top = 0;
    board->tableaus[1].cards[0].rank = 12; // Queen
    board->tableaus[1].cards[0].suit = HEARTS;
    board->tableaus[1].cards[0].is_face_down = false;
    pick_up_cards(board, 1, 1);
    place_cards_on_tableau(board, 0);
    bool result = (board->tableaus[0].top == -1);
    free_board(board);
    return result;
}

// Test 3: Move King to non-empty tableau (should succeed if valid)
bool test_move_king_to_non_empty_tableau()
{
    Board *board = create_board();
    board->tableaus[0].top = 0;
    board->tableaus[0].cards[0].rank = 13; // King
    board->tableaus[0].cards[0].suit = HEARTS;
    board->tableaus[0].cards[0].is_face_down = false;
    board->tableaus[1].top = 0;
    board->tableaus[1].cards[0].rank = 12; // Queen
    board->tableaus[1].cards[0].suit = CLUBS;
    board->tableaus[1].cards[0].is_face_down = false;
    pick_up_cards(board, 1, 1);
    place_cards_on_tableau(board, 0);
    bool result = (board->tableaus[0].top == 1 && board->tableaus[0].cards[1].rank == 12);
    free_board(board);
    return result;
}

// Test 4: Move card onto tableau with face-down top card (should fail)
bool test_move_onto_facedown_card()
{
    Board *board = create_board();
    board->tableaus[0].top = 0;
    board->tableaus[0].cards[0].rank = 2;
    board->tableaus[0].cards[0].suit = CLUBS;
    board->tableaus[0].cards[0].is_face_down = true;
    board->tableaus[1].top = 0;
    board->tableaus[1].cards[0].rank = 3;
    board->tableaus[1].cards[0].suit = HEARTS;
    board->tableaus[1].cards[0].is_face_down = false;
    pick_up_cards(board, 1, 1);
    place_cards_on_tableau(board, 0);
    bool result = (board->tableaus[0].top == 0 && board->tableaus[0].cards[0].rank == 2);
    free_board(board);
    return result;
}

// Test 5: Move card onto tableau with same color (should fail)
bool test_move_onto_same_color()
{
    Board *board = create_board();
    board->tableaus[0].top = 0;
    board->tableaus[0].cards[0].rank = 5;
    board->tableaus[0].cards[0].suit = HEARTS;
    board->tableaus[0].cards[0].is_face_down = false;
    board->tableaus[1].top = 0;
    board->tableaus[1].cards[0].rank = 4;
    board->tableaus[1].cards[0].suit = DIAMONDS;
    board->tableaus[1].cards[0].is_face_down = false;
    pick_up_cards(board, 1, 1);
    place_cards_on_tableau(board, 0);
    bool result = (board->tableaus[0].top == 0 && board->tableaus[0].cards[0].rank == 5);
    free_board(board);
    return result;
}

// Test 6: Move card onto tableau with opposite color and one rank higher (should succeed)
bool test_move_onto_opposite_color_one_rank_higher()
{
    Board *board = create_board();
    board->tableaus[0].top = 0;
    board->tableaus[0].cards[0].rank = 5;
    board->tableaus[0].cards[0].suit = CLUBS;
    board->tableaus[0].cards[0].is_face_down = false;
    board->tableaus[1].top = 0;
    board->tableaus[1].cards[0].rank = 4;
    board->tableaus[1].cards[0].suit = HEARTS;
    board->tableaus[1].cards[0].is_face_down = false;
    pick_up_cards(board, 1, 1);
    place_cards_on_tableau(board, 0);
    bool result = (board->tableaus[0].top == 1 && board->tableaus[0].cards[1].rank == 4);
    free_board(board);
    return result;
}

// Test 7: Move card to foundation with incorrect suit (should fail)
bool test_move_to_foundation_wrong_suit()
{
    Board *board = create_board();
    board->foundations[0].top = 0;
    board->foundations[0].cards[0].rank = 1;
    board->foundations[0].cards[0].suit = HEARTS;
    board->tableaus[0].top = 0;
    board->tableaus[0].cards[0].rank = 2;
    board->tableaus[0].cards[0].suit = CLUBS;
    board->tableaus[0].cards[0].is_face_down = false;
    pick_up_cards(board, 0, 1);
    place_card_on_foundation(board, 0);
    bool result = (board->foundations[0].top == 0 && board->foundations[0].cards[0].rank == 1);
    free_board(board);
    return result;
}

// Test 8: Move card to foundation with correct suit and rank (should succeed)
bool test_move_to_foundation_correct_suit_and_rank()
{
    Board *board = create_board();
    board->foundations[0].top = 0;
    board->foundations[0].cards[0].rank = 1;
    board->foundations[0].cards[0].suit = HEARTS;
    board->tableaus[0].top = 0;
    board->tableaus[0].cards[0].rank = 2;
    board->tableaus[0].cards[0].suit = HEARTS;
    board->tableaus[0].cards[0].is_face_down = false;
    pick_up_cards(board, 0, 1);
    place_card_on_foundation(board, 0);
    bool result = (board->foundations[0].top == 1 && board->foundations[0].cards[1].rank == 2);
    free_board(board);
    return result;
}

// Test 9: Automatically turn face-down card after moving all face-up cards (should succeed)
bool test_auto_turn_facedown_card()
{
    Board *board = create_board();
    board->tableaus[0].top = 1;
    board->tableaus[0].cards[0].rank = 7;
    board->tableaus[0].cards[0].suit = CLUBS;
    board->tableaus[0].cards[0].is_face_down = true;
    board->tableaus[0].cards[1].rank = 6;
    board->tableaus[0].cards[1].suit = HEARTS;
    board->tableaus[0].cards[1].is_face_down = false;
    pick_up_cards(board, 0, 1);
    bool result = (board->tableaus[0].top == 0 && !board->tableaus[0].cards[0].is_face_down);
    free_board(board);
    return result;
}

void run_test(const char *name, TestFunc func)
{
    bool passed = func();
    printf("%s: %s %s\n", name, passed ? CHECKMARK : CROSS, passed ? "" : "(failed)");
}

int main()
{
    run_test("Test1: Move King to empty tableau", test_move_king_to_empty_tableau);
    run_test("Test2: Move non-King to empty tableau", test_move_non_king_to_empty_tableau);
    run_test("Test3: Move King to non-empty tableau", test_move_king_to_non_empty_tableau);
    run_test("Test4: Move card onto tableau with face-down top card", test_move_onto_facedown_card);
    run_test("Test5: Move card onto tableau with same color", test_move_onto_same_color);
    run_test("Test6: Move card onto tableau with opposite color and one rank higher", test_move_onto_opposite_color_one_rank_higher);
    run_test("Test7: Move card to foundation with incorrect suit", test_move_to_foundation_wrong_suit);
    run_test("Test8: Move card to foundation with correct suit and rank", test_move_to_foundation_correct_suit_and_rank);
    run_test("Test9: Automatically turn face-down card after moving all face-up cards", test_auto_turn_facedown_card);
    run_test("Test10: Move group with only starting and target cards in sequence and alternate color", test_move_group_sequence_and_color_only);
    return 0;
}
