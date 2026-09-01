#include <iostream>

using namespace std;

int inputBetweenValidRange(int var, string text, int upperBound, int lowerBound) {
    int repeat = 0;
    do {
        if (repeat > 0) {
            cout << "ERROR: Input outside of valid range." << endl;
        }
        repeat++;

        cout << text;
        cin >> var;
    } while (var < upperBound || var > lowerBound);

    return var;
}

class Board {
    public:
        // Declaring empty 3x3 array
        char gameArray[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };
        bool whichTurn = true;

        void drawBoard() {
            cout << endl;
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    cout << "| " << gameArray[row][col] << " ";
                    
                    // Once the last column has been printed, it goes to the next line
                    if (col == 2) {
                        cout << "|" << endl;
                    }

                }
                // Prints the row divider only after row 1 and 2
                if (row < 2) {
                    cout << "+-+-+-+-+-+-+" << endl;
                }
            }
            cout << endl;
        }

        void attack() {
            int col;
            int row;
            
            // Printing whose turn it is
            if (whichTurn == true) { 
                cout << "It is X's turn" << endl;
            } else {
                cout << "It is O's turn" << endl;
            }

            // Asks the user to input which square to attack
            row = inputBetweenValidRange(row, "Choose a row(1, 2, or 3): ", 1, 3);
            row--;

            col = inputBetweenValidRange(col, "Choose a column(1, 2, or 3): ", 1, 3);
            col--;

            // Ensures that you cannot attack a space that has already been attacked
            int repeat = 0;
            while (gameArray[row][col] != ' ') {
                repeat++;
                if (repeat > 0) {
                    cout << "Spot already taken" << endl;
                }

                row = inputBetweenValidRange(row, "Choose a row(1, 2, or 3): ", 1, 3);
                row--;

                col = inputBetweenValidRange(col, "Choose a column(1, 2, or 3): ", 1, 3);
                col--;
            }

            if (whichTurn == true) {
                gameArray[row][col] = 'X';
            } else {
                gameArray[row][col] = 'O';
            }

            // Swaps the bool value to switch turns
            whichTurn = !(whichTurn);
        }

        bool checkWinCondition() {
            for (int i = 0; i < 3; i++) {
                bool horizontalCheck = gameArray[i][0] == gameArray[i][1] && gameArray[i][0] == gameArray[i][2] && gameArray[i][0] != ' ';
                bool verticalCheck = gameArray[0][i] == gameArray[1][i] && gameArray[0][i] == gameArray[2][i] && gameArray[0][i] != ' ';
                bool diagonalCheck1 = gameArray[0][0] == gameArray[1][1] && gameArray[0][0] == gameArray[2][2] && gameArray[1][1] != ' ';
                bool diagonalCheck2 = gameArray[0][2] == gameArray[1][1] && gameArray[0][2] == gameArray[2][0] && gameArray[1][1] != ' ';

                // Check all possible win conditions
                if (horizontalCheck || verticalCheck || diagonalCheck1 || diagonalCheck2) {
                    drawBoard();
                    if (horizontalCheck) {
                        cout << gameArray[i][0] << " has won the game!";
                    } else if (verticalCheck) {
                        cout << gameArray[0][i] << " has won the game!";
                    } else if (diagonalCheck1 || diagonalCheck2) {
                        cout << gameArray[1][1] << " has won the game!";
                    }
                    return true;

                } else if (i == 2) { // Only return false when all the squares have been cycled through
                    return false;
                }
            }
        }
};

int main() {
    bool hasWon = false;
    int numTurns = 0;
    Board game;

    while (!hasWon) {
        game.drawBoard();
        game.attack();
        hasWon = game.checkWinCondition();
        numTurns++;

        if (numTurns == 9) {
            game.drawBoard();
            cout << "Game ends in a draw";
            break;
        }
    }

    return 0;
}