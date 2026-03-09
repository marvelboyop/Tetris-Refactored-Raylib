# Refactored my Tetris game into multiple files (check out another previous version of this on another repo named "Tetris_CPP_Raylib")
## because can't help with a single main.cpp so divided into the 4 components/parts
- core
- shapes
- systems
- UI

---
### Also edited the makefile to adapt to multiple files compilation instead of a single main.cpp
---
# Modern Tetris Engine (C++ / Raylib)

A modern Tetris implementation written in C++ using Raylib.

This project focuses on clean architecture, safe collision handling,
and scalable game-state design rather than just visual replication.

The engine implements modern guideline-style spawning
and a structured line-clearing animation pipeline.

---

## Architecture Overview

The game is structured around three independent systems:

1. Board State System
   - Stores only locked blocks
   - Responsible for row detection and removal
   - Never stores negative indices

2. Active Piece System
   - Separate Shape class
   - Handles movement, rotation, gravity
   - Supports negative Y spawning

3. Game State Controller
   - Manages clearing animation
   - Controls spawn transitions
   - Freezes gameplay during line clear

---

## Modern Spawn Implementation

Unlike classic implementations that spawn inside the grid,
this engine supports negative Y spawning.

Key rules:
- boardY < 0 is allowed during movement and rotation
- Collision checks are ignored for negative rows
- Top-out occurs only if a piece locks while partially above grid
- LockToBoard prevents out-of-bounds memory writes

This required consistent updates to:
- CanMoveLeft
- CanMoveRight
- CanMoveDown
- CanRotate
- CanSpawn

---

## 7-Bag Randomizer

Piece generation follows the modern 7-bag system:

- All 7 tetrominoes are shuffled
- Pieces are drawn without repetition
- Ensures balanced randomness

---

## Line Clear Animation System

Instead of immediately removing full rows,
the engine separates detection from mutation.

Pipeline:

1. Detect full rows
2. Enter clearing state
3. Blink animation (hide/show toggle)
4. Remove rows after timer expires
5. Resume gameplay

This prevents state corruption and allows
future extension (sound, combo tracking, effects).

---

## High Score System

The game includes a simple persistent high score system using file storage.

### How it works

- When the game starts, the high score is loaded from `highscore.txt`.
- During gameplay, if the player's score exceeds the current high score, the value is updated in memory immediately.
- The UI reflects the new high score as soon as it is beaten.
- When the game closes, the high score is saved back to the file.

This approach ensures that:
- The high score updates live during gameplay.
- The score is preserved even if the game is closed using the **ESC key** or the **window close button**.
- File I/O is minimized by only writing the high score once when the application exits.

### File Format

The high score is stored in a simple text file:

```
highscore.txt
1500
```

Only the highest score is stored, keeping the system lightweight and easy to maintain.

---

## Safety Considerations

- All board writes guarded against negative indices
- No undefined behavior from uninitialized members
- Clear separation of rendering and data state
- No mutation during animation phase

---

## Controls

Left / Right  - Move  
Up            - Rotate  
Down          - Soft Drop  

---

## Build

Requires:
- MinGW
- Raylib

Compile using:

- make

 ### or

- mingw32-make game

---

