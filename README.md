# Tetris Console Game 🎮

A simple Tetris game built using C++ that runs in the console. Blocks fall, and you must rotate and position them to clear lines and score points! 🏆

## Features ✨
- Classic Tetris gameplay 🎲
- Smooth movement with arrow keys ⬅️⬇️➡️
- Rotations with the Up Arrow 🔄
- Score tracking 📊
- Restart (`R`) or Quit (`Q`) options after Game Over 🎮
- Hidden cursor for a cleaner UI ✨

## Controls 🎮
- ⬅️ Left Arrow: Move piece left
- ➡️ Right Arrow: Move piece right
- ⬇️ Down Arrow: Move piece down faster
- 🔼 Up Arrow: Rotate the piece
- `R`: Restart the game after Game Over 🔁
- `Q`: Quit the game ❌

## How to Compile & Run 🚀
### Windows 🖥️
1. Install `g++` (MinGW) if not installed.
2. Open a terminal in the project folder.
3. Compile using:
   ```sh
   g++ -o tetris main.cpp -std=c++11
   ```
4. Run the game:
   ```sh
   tetris.exe
   ```
## Notes 📄
- This game only works on **Windows** because it uses `windows.h` and `_getch()`.
- The game might flicker a bit due to the console update method.

Hope you like this game! Happy coding! 🚀
