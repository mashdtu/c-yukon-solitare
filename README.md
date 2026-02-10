## Yukon Solitaire (C Implementation)

This is Yukon Solitaire implemented in C.  
The UI is not implemented yet, but you can try out the game logic by compiling and running `test_game.c`, which lets you try it out in the terminal.

---

## Compiling Test Files

To compile the test files, use the following commands in your project root:

### Compile test_game.c

```sh
gcc test/test_game.c board.c cards.c pile.c deck.c win.c rules.c -o test_game
```

### Compile test_circumstances.c

```sh
gcc test/test_circumstances.c board.c cards.c pile.c deck.c win.c rules.c -o test_circumstances
```

### Compile test_deck.c

```sh
gcc test/test_deck.c board.c cards.c pile.c deck.c win.c rules.c -o test_deck
```

If you get missing symbol errors, add any other .c files required by your tests.

### Run the game
```sh
./test_game
```

### Run the tests

```sh
./test_circumstances
./test_deck
```

---

Make sure you have GCC installed. If you need to clean up object files, use:

```sh
rm *.o
```
