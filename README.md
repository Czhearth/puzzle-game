# 15 Puzzle Game in C

A terminal-based **15 Puzzle / Sliding Puzzle Game** built in **C** for Windows.

## Features
- Multiple difficulty levels:
  - Easy (3x3)
  - Medium (5x5)
  - Hard (6x6)
- Keyboard controls:
  - `W A S D`
  - Arrow keys
- Move counter
- Auto Solver option
- Randomized solvable board generation
- Console-based interactive UI

## Tech Stack
- **Language:** C
- **Platform:** Windows Console
- **Libraries Used:**
  - `stdio.h`
  - `stdlib.h`
  - `time.h`
  - `conio.h`
  - `ctype.h`
  - `windows.h`

## How to Run

### Compile using GCC
```bash
gcc src/version_4.c -o puzzle.exe
```

### Run
```bash
./puzzle.exe
```

> Note: This project uses `conio.h` and `windows.h`, so it is intended for **Windows**.

## Controls
- `W` / `↑` → Move Up
- `S` / `↓` → Move Down
- `A` / `←` → Move Left
- `D` / `→` → Move Right
- `H` → Auto Solve
- `Q` → Quit

## Project Structure
```bash
15-puzzle-game/
│── src/
│   └── version_4.c
│── old_versions/
│   ├── Game_n_Solver.c
│   └── version_3.c
│── README.md
│── .gitignore
```

## Future Improvements
- Add proper puzzle solvability check
- Add timer system
- Add leaderboard / high score tracking
- Improve auto-solver with actual solving algorithm
- Add Linux-compatible version

## Author
**Siddharth**