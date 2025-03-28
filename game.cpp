#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

class Tetromino {
public:
    vector<vector<int>> shape;
    char symbol;
    int color;

    Tetromino() : shape({{0}}), symbol(' '), color(15) {}
    Tetromino(vector<vector<int>> s, char sym, int col) : shape(s), symbol(sym), color(col) {}
};

class Game {
private:
    vector<vector<int>> board;
    Tetromino currentPiece;
    int pieceX, pieceY;
    int score;
    bool gameOver;
    HANDLE hConsole;

    void spawnPiece() {
        static vector<Tetromino> pieces = {
            Tetromino({{1}, {1}, {1}, {1}}, 'I', 11),
            Tetromino({{1,1,1}, {0,1,0}}, 'T', 13),
            Tetromino({{1,0,0}, {1,0,0}, {1,1,0}}, 'L', 9),
            Tetromino({{0,0,1}, {0,0,1}, {0,1,1}}, 'J', 12),
            Tetromino({{1,1}, {1,1}}, 'O', 14),
            Tetromino({{1,1,0}, {0,1,1}}, 'S', 10),
            Tetromino({{0,1,1}, {1,1,0}}, 'Z', 13)
        };

        currentPiece = pieces[rand() % pieces.size()];
        pieceX = WIDTH / 2 - currentPiece.shape[0].size() / 2;
        pieceY = 0;

        if (!isValidMove(0, 0)) {
            gameOver = true;
        }
    }

    bool isValidMove(int offsetX, int offsetY) {
        for (int y = 0; y < currentPiece.shape.size(); y++) {
            for (int x = 0; x < currentPiece.shape[y].size(); x++) {
                if (currentPiece.shape[y][x]) {
                    int newX = pieceX + x + offsetX;
                    int newY = pieceY + y + offsetY;
                    if (newX < 0 || newX >= WIDTH || newY >= HEIGHT) return false;
                    if (newY >= 0 && board[newY][newX]) return false;
                }
            }
        }
        return true;
    }

    void mergePiece() {
        for (int y = 0; y < currentPiece.shape.size(); y++) {
            for (int x = 0; x < currentPiece.shape[y].size(); x++) {
                if (currentPiece.shape[y][x]) {
                    board[pieceY + y][pieceX + x] = currentPiece.color;
                }
            }
        }
    }

    void clearLines() {
        for (int y = 0; y < HEIGHT; y++) {
            bool full = true;
            for (int x = 0; x < WIDTH; x++) {
                if (!board[y][x]) full = false;
            }
            if (full) {
                board.erase(board.begin() + y);
                board.insert(board.begin(), vector<int>(WIDTH, 0));
                score++;
            }
        }
    }

    void rotatePiece() {
        vector<vector<int>> rotatedPiece(currentPiece.shape[0].size(), vector<int>(currentPiece.shape.size()));
        for (int y = 0; y < currentPiece.shape.size(); y++) {
            for (int x = 0; x < currentPiece.shape[y].size(); x++) {
                rotatedPiece[x][currentPiece.shape.size() - 1 - y] = currentPiece.shape[y][x];
            }
        }
        vector<vector<int>> originalShape = currentPiece.shape;
        currentPiece.shape = rotatedPiece;
        if (!isValidMove(0, 0)) {
            currentPiece.shape = originalShape;
        }
    }

public:
    Game() : board(HEIGHT, vector<int>(WIDTH, 0)), score(0), gameOver(false), hConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {
        srand(time(0));
        spawnPiece();
    }

    void draw() {
        system("cls");
        for (int y = 0; y < HEIGHT; y++) {
            cout << "|";
            for (int x = 0; x < WIDTH; x++) {
                bool isPiece = false;
                for (int py = 0; py < currentPiece.shape.size(); py++) {
                    for (int px = 0; px < currentPiece.shape[py].size(); px++) {
                        if (currentPiece.shape[py][px] && y == pieceY + py && x == pieceX + px) {
                            isPiece = true;
                        }
                    }
                }
                if (isPiece) {
                    SetConsoleTextAttribute(hConsole, currentPiece.color);
                    cout << "[]";
                } else if (board[y][x]) {
                    SetConsoleTextAttribute(hConsole, board[y][x]);
                    cout << "[]";
                } else {
                    cout << "  ";
                }
                SetConsoleTextAttribute(hConsole, 15);
            }
            cout << "|\n";
        }
        cout << "Score: " << score << endl;
        if (gameOver) cout << "Game Over! Press R to Restart or Q to Quit" << endl;
    }

    void update() {
        if (gameOver) return;
        if (!isValidMove(0, 1)) {
            mergePiece();
            clearLines();
            spawnPiece();
            return;
        }
        pieceY++;
    }

    void handleInput() {
        if (_kbhit()) {
            switch (_getch()) {
                case 75: if (isValidMove(-1, 0)) pieceX--; break;
                case 77: if (isValidMove(1, 0)) pieceX++; break;
                case 80: if (isValidMove(0, 1)) pieceY++; break;
                case 72: rotatePiece(); break;
                case 'r': gameOver = false; board.assign(HEIGHT, vector<int>(WIDTH, 0)); spawnPiece(); break;
                case 'q': exit(0);
            }
        }
    }

    bool isGameOver() { return gameOver; }
};

int main() {
    hideCursor();
    Game game;
    while (true) {
        game.draw();
        if (game.isGameOver()) {
            while (true) {
                char ch = _getch();
                if (ch == 'r') { game = Game(); break; }
                if (ch == 'q') exit(0);
            }
        }
        game.handleInput();
        game.update();
        Sleep(50);
    }
    return 0;
}