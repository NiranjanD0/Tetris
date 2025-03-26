# Tetris Game in C++ (Windows API) 🕹️💥

This is a simple **Tetris game** implemented using **C++ and Windows API**. It features block movement, rotation, line clearing, and game-over detection.

---

## 📌 Features
- 🎮 **Keyboard Controls** for moving and rotating blocks
- 🧱 **Different Tetromino Shapes**
- 🔄 **Block Rotation**
- 📏 **Boundary and Collision Handling**
- 🚀 **Line Clearing Mechanics (satisfaction guaranteed)**
- 🎨 **Graphical Rendering with Bitmaps**

---

## 🛠️ How to Build & Run

### **🔹 Using MinGW (g++)**
1. Open a terminal and navigate to the project folder.
2. Run the following commands:
   ```sh
    windres -i block.rc -o block.o
    g++ -mwindows game.cpp block.o -o game.exe
   ```
3. Run the game:
   ```sh
    ./tetris.exe
    ```
---

## 🎮 Controls
| Key | Action |
|-|-|
| ⬅️ Left Arrow  | Move block left |
| ➡️ Right Arrow | Move block right |
| ⬆️ Up Arrow   | Rotate block |
| ⬇️ Down Arrow | Drop block faster (because patience is overrated) |
---

## 📜 License
This project is open-source. Feel free to modify and improve it!

---