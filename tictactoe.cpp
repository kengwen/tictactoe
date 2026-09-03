#include <iostream>
#include <vector>

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
    } while (var > upperBound || var < lowerBound);

    return var;
}

class Board {
    public:
        // Declaring empty 2D vector
        vector<vector<char>> gameArray;
        bool whichTurn = true;
        int numSides;

        Board() {
            // Allows the board to be minimum 3x3 and maximum 10x10
            numSides = inputBetweenValidRange(numSides, "What size board would you like to play? (ex. input 3 for 3x3 board): ", 10, 3);

            // Appends a ' ' to each element in the vectors
            for (int i = 0; i < numSides; i++) {
                gameArray.push_back({});
                for (int j = 0; j < numSides; j++) {
                    gameArray[i].push_back(' ');
                }
            }
        }

        void drawBoard() {
            cout << endl;
            for (int row = -1; row < numSides; row++) {
                for (int col = 0; col < numSides; col++) {
                    if (row == -1) {
                        cout << "  " << col + 1 << " "; // Displays the column numbers above the board
                    } else {
                        cout << "| " << gameArray[row][col] << " ";
                    }

                    // Once the last column has been printed, it goes to the next line
                    if (col == numSides - 1) {
                        if (row == -1) {
                            cout << "  " << endl;
                        } else {
                            cout << "| " << row + 1 << endl; // Displays the row numbers beside the board
                        }
                    }

                }
                // Prints the row divider in between each row
                if (row < numSides - 1 && row >= 0) {
                    cout << "+-+-+-+-+-+-+"; // Default row divider for a 3x3 board

                    if (numSides > 3) {
                        for (int i = 0; i < numSides - 3; i++) {
                            cout << "-+-+"; // Adds this string for every additional box above 3
                        }
                    }
                    cout << endl;
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
            col = inputBetweenValidRange(col, "Choose a column: ", numSides, 1);
            col--;
            
            row = inputBetweenValidRange(row, "Choose a row: ", numSides, 1);
            row--;

            // Ensures that you cannot attack a space that has already been attacked
            int repeat = 0;
            while (gameArray[row][col] != ' ') {
                repeat++;
                if (repeat > 0) {
                    cout << "Spot already taken" << endl;
                }

                col = inputBetweenValidRange(col, "Choose a column: ", numSides, 1);
                col--;

                row = inputBetweenValidRange(row, "Choose a row: ", numSides, 1);
                row--;
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