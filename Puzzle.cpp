#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// === Puzzle Board ===
class Puzzle {
private:
    int board[3][3];
    int emptyRow, emptyCol;
    int moves;

    void findEmpty() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == 0) {
                    emptyRow = i;
                    emptyCol = j;
                }
    }

public:
    Puzzle() {
        moves = 0;
        // Set solved state first
        int num = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                board[i][j] = (num == 9) ? 0 : num;
                num++;
            }
        emptyRow = 2;
        emptyCol = 2;
    }

    // Shuffle by making random valid moves
    void shuffle(int times = 300) {
        srand(time(0));
        for (int k = 0; k < times; k++) {
            int dir = rand() % 4;
            int newRow = emptyRow, newCol = emptyCol;
            if      (dir == 0) newRow--;  // up
            else if (dir == 1) newRow++;  // down
            else if (dir == 2) newCol--;  // left
            else               newCol++;  // right

            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                board[emptyRow][emptyCol] = board[newRow][newCol];
                board[newRow][newCol] = 0;
                emptyRow = newRow;
                emptyCol = newCol;
            }
        }
        moves = 0;
    }

    // Display the board
    void display() {
        cout << "\n  +----+----+----+" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "  |";
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0)
                    cout << "    |";
                else
                    cout << " " << setw(2) << board[i][j] << " |";
            }
            cout << endl;
            cout << "  +----+----+----+" << endl;
        }
        cout << "  Moves: " << moves << endl;
    }

    // Move tile into empty space
    // W = move tile below empty UP
    // S = move tile above empty DOWN
    // A = move tile right of empty LEFT
    // D = move tile left of empty RIGHT
    bool move(char dir) {
        int newRow = emptyRow, newCol = emptyCol;

        if      (dir == 'w' || dir == 'W') newRow++;
        else if (dir == 's' || dir == 'S') newRow--;
        else if (dir == 'a' || dir == 'A') newCol++;
        else if (dir == 'd' || dir == 'D') newCol--;
        else return false;

        if (newRow < 0 || newRow >= 3 || newCol < 0 || newCol >= 3) {
            cout << "  Invalid move!" << endl;
            return false;
        }

        board[emptyRow][emptyCol] = board[newRow][newCol];
        board[newRow][newCol] = 0;
        emptyRow = newRow;
        emptyCol = newCol;
        moves++;
        return true;
    }

    // Check if puzzle is solved
    bool isSolved() {
        int expected = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                if (i == 2 && j == 2) {
                    if (board[i][j] != 0) return false;
                } else {
                    if (board[i][j] != expected) return false;
                    expected++;
                }
            }
        return true;
    }

    int getMoves() { return moves; }
};

// === Main ===
int main() {
    char playAgain = 'y';

    cout << "=============================" << endl;
    cout << "   8-Tile Sliding Puzzle     " << endl;
    cout << "=============================" << endl;
    cout << "  Controls:" << endl;
    cout << "  W = slide tile UP" << endl;
    cout << "  S = slide tile DOWN" << endl;
    cout << "  A = slide tile LEFT" << endl;
    cout << "  D = slide tile RIGHT" << endl;
    cout << "  Goal: arrange 1-8 in order" << endl;
    cout << "  with empty space at bottom right" << endl;

    while (playAgain == 'y' || playAgain == 'Y') {
        Puzzle puzzle;
        puzzle.shuffle();

        cout << "\n  Board shuffled! Good luck!" << endl;
        puzzle.display();

        while (!puzzle.isSolved()) {
            cout << "  Enter move (W/A/S/D) or Q to quit: ";
            char input;
            cin >> input;

            if (input == 'q' || input == 'Q') {
                cout << "  Quitting game..." << endl;
                break;
            }

            puzzle.move(input);
            puzzle.display();

            if (puzzle.isSolved()) {
                cout << "\n  *** Congratulations! You solved it! ***" << endl;
                cout << "  Total moves: " << puzzle.getMoves() << endl;

                if (puzzle.getMoves() <= 20)
                    cout << "  Rating: EXCELLENT! (under 20 moves)" << endl;
                else if (puzzle.getMoves() <= 50)
                    cout << "  Rating: GOOD! (under 50 moves)" << endl;
                else
                    cout << "  Rating: KEEP PRACTICING!" << endl;
            }
        }

        cout << "\n  Play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "\n  Thanks for playing!" << endl;
    system("pause");
    return 0;
}
