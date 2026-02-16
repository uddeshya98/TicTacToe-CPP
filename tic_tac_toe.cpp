#include <bits/stdc++.h>

using namespace std;

/**
 * @class Player
 * Represents a game participant.
 */
class Player {
private:
    char symbol;
    string name;

public:
    Player(char sym = 'X', string n = "Player") : symbol(sym), name(n) {}
    char getSymbol() const { return symbol; }
    string getName() const { return name; }
};

/**
 * @class Board
 * Handles the 3x3 grid and win/draw conditions.
 */
class Board {
private:
    char grid[3][3];
    int filledCells;

public:
    Board() : filledCells(0) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                grid[i][j] = ' ';
    }

    void drawBoard() const {
        cout << "\n      1     2     3  " << endl;
        cout << "   +-----+-----+-----+" << endl;
        for (int i = 0; i < 3; i++) {
            cout << " " << i + 1 << " |  ";
            for (int j = 0; j < 3; j++) {
                cout << grid[i][j] << "  |  ";
            }
            cout << endl << "   +-----+-----+-----+" << endl;
        }
        cout << endl;
    }

    bool isValidMove(int row, int col) const {
        return (row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == ' ');
    }

    void makeMove(int row, int col, char symbol) {
        if (isValidMove(row, col)) {
            grid[row][col] = symbol;
            filledCells++;
        }
    }

    bool checkWin(char s) const {
        for (int i = 0; i < 3; i++) {
            if ((grid[i][0] == s && grid[i][1] == s && grid[i][2] == s) || // Rows
                (grid[0][i] == s && grid[1][i] == s && grid[2][i] == s))   // Cols
                return true;
        }
        return (grid[0][0] == s && grid[1][1] == s && grid[2][2] == s) || // Diag 1
               (grid[0][2] == s && grid[1][1] == s && grid[2][0] == s);   // Diag 2
    }

    bool isFull() const { return filledCells == 9; }
};

/**
 * @class TicTacToe
 * Main Game Controller.
 */
class TicTacToe {
private:
    Board board;
    Player players[2];
    int turn;

public:
    TicTacToe() : turn(0) {
        players[0] = Player('X', "Player 1");
        players[1] = Player('O', "Player 2");
    }

    void play() {
        int r, c;
        cout << "--- Welcome to CPP Tic-Tac-Toe ---" << endl;

        while (!board.isFull()) {
            board.drawBoard();
            cout << players[turn].getName() << " (" << players[turn].getSymbol() << "), Enter [Row Col]: ";
            
            if (!(cin >> r >> c)) { // Handle non-integer input
                cout << "Invalid input! Please enter numbers." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            if (board.isValidMove(r - 1, c - 1)) {
                board.makeMove(r - 1, c - 1, players[turn].getSymbol());
                if (board.checkWin(players[turn].getSymbol())) {
                    board.drawBoard();
                    cout << "🏆 CONGRATULATIONS! " << players[turn].getName() << " wins!" << endl;
                    return;
                }
                turn = (turn + 1) % 2;
            } else {
                cout << "⚠️ Invalid Move. The cell is either taken or out of bounds!" << endl;
            }
        }
        board.drawBoard();
        cout << "🤝 Game Over! It's a DRAW." << endl;
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}