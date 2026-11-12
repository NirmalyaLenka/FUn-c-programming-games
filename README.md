# C Console Games

Two small C programs for practising console input, control flow, arrays, and game logic.

## Included programs

| File | What it does | Platform notes |
|---|---|---|
| [`A tic tac toe.c`](A%20tic%20tac%20toe.c) | Human player (`X`) versus computer (`O`) on a 3×3 board. The computer selects moves using a minimax search. | Standard C headers are used; a C99-compatible compiler is suitable. |
| [`snake.c`](snake.c) | Console Snake game with WASD movement, pause (`P`), exit (`X`), score, increasing speed, and a high-score file. | Windows-specific: uses `conio.h`, `windows.h`, and Windows console APIs. |

## Prerequisites

- GCC/MinGW-w64 or another C compiler.
- A terminal/console window.
- For Snake, a Windows environment with a compiler that provides the Windows console headers and APIs (for example, MinGW-w64/MSYS2 UCRT64).

## Build and run

Run commands from the repository root.

### Tic-tac-toe

**Windows (MinGW-w64):**

```powershell
gcc -std=c99 -Wall -Wextra "A tic tac toe.c" -o tic_tac_toe.exe
.\tic_tac_toe.exe
```

**Linux/macOS (if GCC or Clang is installed):**

```bash
gcc -std=c99 -Wall -Wextra "A tic tac toe.c" -o tic_tac_toe
./tic_tac_toe
```

### Snake (Windows)

```powershell
gcc -std=c99 -Wall -Wextra snake.c -o snake.exe
.\snake.exe
```

The Snake game reads `highscore.txt` from the current working directory and attempts to write a new high score there. Run it from the directory where you want that file stored. The file is created at runtime; it is not included in the repository.

## Repository layout

```text
.
├── A tic tac toe.c   # Human-versus-computer tic-tac-toe
├── snake.c           # Windows console Snake game
└── README.md         # Setup, usage, and known limitations
```

## Known limitations

- The tic-tac-toe input handler expects an integer corresponding to a board position from 1 to 9. It does not validate non-numeric or out-of-range input; such input can cause incorrect behaviour.
- The tic-tac-toe program prints a final `Draw` message after the game loop even when a win message was already printed. This is a source-code issue and is not changed by this documentation update.
- Snake depends on Windows console APIs and is not directly portable to Linux/macOS without code changes.
- Snake does not check whether opening `highscore.txt` for writing succeeded.
- No automated tests or build results are recorded here.

## License

No license file is present in the repository. Reuse and redistribution terms are therefore not explicitly specified; add a license if you intend to publish the project for reuse.

## Maintenance & audit

- **Audit date:** 11 November 2026
- **Scope:** Documentation-only review of the two C source files and repository layout.
- **Verification:** The source was inspected for documentation accuracy, but it was not compiled or executed during this pass. No source-code changes were made.
