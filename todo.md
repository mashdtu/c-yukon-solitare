# TODO
- Implement undo functionality
- Implement Controller for handling communication between Model and UI
- Implement UI
- Complete overhaul of code and refactor to improve readability and maintainability

## Game.c
1. board.c / board.h

    Functions: create_board, initialize_board, free_board
    Data: Board struct and related initialization
    Header: Declare board management functions and Board struct

2. move.c / move.h

    Functions: pick_up_cards, place_cards_on_tableau, place_card_on_foundation
    Data: Hand struct (if not already in board.h)
    Header: Declare move-related functions

3. win.c / win.h

    Functions: check_win_condition
    Header: Declare win condition function

### Steps:

- Create board.c/board.h, move.c/move.h, win.c/win.h files.
- Move relevant functions and structs from game.c to these files.
- Update game.h to only include high-level orchestration or move struct definitions to new headers as needed.
- Update includes in all files to reference new headers.
- Refactor game.c to only call functions from these modules, keeping it minimal.