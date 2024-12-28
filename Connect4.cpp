// File name: Four_in_a_row_BonusAI.cpp
// Purpose: AI for Game 2 (implementation)
// Author(s): Yasmine Sherif Mohamed
// ID(s): 20220377
// Section: S24
// TA: Mohamed Talaat
// Date: 16 Dec 2023
// Version: 1.0

#include "Connect4.h"
#include<bits/stdc++.h>

using namespace std;

// Give player a symbol to use in playing
// It can be X or O or others
// This is needed for computer players
// as it does not ask for a name
Player::Player(char symbol) {
    this->symbol = symbol;
}

// Optionally, you can give him ID or order
// Like Player 1 and Player 2
Player::Player(int order, char symbol) {
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
}

// Get desired move: x y (each between 0 and 2)
// Virtual (can change for other player types)
void Player::get_move(int &x, int &y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Give player info as a string
string Player::to_string() {
    return "Player: " + name;
}

// Get symbol used by player
char Player::get_symbol() {
    return symbol;
}

// Set player symbol and name as Random Computer Player
RandomPlayer::RandomPlayer(char symbol, int dimension) : Player(symbol) {
    this->dimension = dimension;
    this->name = "Random Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void RandomPlayer::get_move(int &x, int &y) {
    x = (int) (rand() / (RAND_MAX + 1.0) * dimension);
    y = (int) (rand() / (RAND_MAX + 1.0) * dimension);
}


AIPlayer::AIPlayer(char symbol, Board *brd) : Player(symbol) {
    this->name = "AI Player";
    cout << "My names is " << name << endl;
    this->boardPtr = brd;
}

void AIPlayer::get_move(int &x, int &y) {
    boardPtr->MinMax(x, y, false, true, 7);
}


//............................................

GameManager::GameManager(Board *bPtr, Player *playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::run() {
    int x, y;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i: {0, 1}) {
            players[i]->get_move(x, y);
            while (!boardPtr->update_board(x, y, players[i]->get_symbol())) {
                players[i]->get_move(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_winner()) {
                cout << players[i]->to_string() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////


Four_in_a_row_Board::Four_in_a_row_Board() {
    n_rows = 6;
    n_cols = 7;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool Four_in_a_row_Board::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if (y >= 0 && y < n_cols && board[0][y] == 0) {
        int i = n_rows - 1;
        while (i >= 0 && board[i][y] != 0) {
            i--;
        }
        board[i][y] = toupper(mark);
        n_moves++;
        return true;
    } else
        return false;
}

// Display the board and the pieces on it
void Four_in_a_row_Board::display_board() {
    for (int i = 0; i < n_rows; ++i) {
        cout << "\n|";
        for (int j = 0; j < n_cols; ++j) {
            if (board[i][j] == 0) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << board[i][j] << " |";
            } else {
                cout << setw(5) << board[i][j] << setw(4) << " |";
            }
        }
        cout << "\n----------------------------------------------------------------";
    }
    cout << '\n';
}


bool Four_in_a_row_Board::is_winner() {
    if (check_state() == 2 || check_state() == -2)
        return true;
    else
        return false;
}

bool Four_in_a_row_Board::is_draw() {
    return (n_moves == n_cols * n_rows && !is_winner());
}

bool Four_in_a_row_Board::game_is_over() {
    return n_moves >= n_cols * n_rows;
}

int Four_in_a_row_Board::check_state() { //winning conditions for X or O
    // Check horizontally
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j <= n_cols - 4; ++j) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] &&
                board[i][j] == board[i][j + 3]) {
                return (board[i][j] == 'X' ? 2 : -2);
            }
        }
    }

    // Check vertically
    for (int i = 0; i <= n_rows - 4; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] &&
                board[i][j] == board[i + 3][j]) {
                return (board[i][j] == 'X' ? 2 : -2);
            }
        }
    }

    // Check diagonally (top-left to bottom-right)
    for (int i = 0; i <= n_rows - 4; ++i) {
        for (int j = 0; j <= n_cols - 4; ++j) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] &&
                board[i][j] == board[i + 3][j + 3]) {
                return (board[i][j] == 'X' ? 2 : -2);
            }
        }
    }

    // Check diagonally (top-right to bottom-left)
    for (int i = 0; i <= n_rows - 4; ++i) {
        for (int j = n_cols - 1; j >= 3; --j) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] &&
                board[i][j] == board[i + 3][j - 3]) {
                return (board[i][j] == 'X' ? 2 : -2);
            }
        }
    }

    // Check for a draw or an ongoing game
    bool flag = true;
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            if (board[i][j] == 0) {
                flag = false;
            }
        }
    }

    if (flag) {
        return 0;//draw
    }
    return 1; //game still in progress
}

int Four_in_a_row_Board::MinMax(int &x, int &y, bool isMax, bool FirstTurn, int depth) { //depth calls fn depth times
    int result = check_state();
    if (result != 1 || depth == 0) //bos odam b rakam el depth 3shan el ehtmalat keteer han run lbokra
        return result;

//    int emptyCells = 0;
//    for (int i = 0; i < n_rows; ++i) {
//        for (int j = 0; j < n_cols; ++j) {
//            if (board[i][j] == 0) {
//                emptyCells++;
//            }
//        }
//    }

    int maxScore = INT_MIN, minScore = INT_MAX, lastI, lastJ;
    for (int j = 0; j < n_cols; ++j) {
        if (board[0][j] == 0) {
            int i = n_rows - 1;
            while (i >= 0 && board[i][j] != 0) {
                i--; // make sure ur dropping ur token
            }
            if (isMax) { // isMax = true -> X turn // false -> O turn
                board[i][j] = 'X';
                int newScore = MinMax(x, y, false, false, depth - 1); //false switch turn
                board[i][j] = 0;
                if (newScore >= maxScore) { //2
                    maxScore = newScore;
                    lastI = i;
                    lastJ = j; //best moves
                }
                if (FirstTurn) {
                    cout << "in " << i << ", " << j << " "
                         << (newScore == 2 ? "X wins!" : (newScore == -2) ? "O wins!" : "It's a draw!") << "\n";
                }
            } else {
                board[i][j] = 'O';
                int newScore = MinMax(x, y, true, false, depth - 1); //true switch turn
                board[i][j] = 0;
                if (newScore <= minScore) { //-2
                    minScore = newScore;
                    lastI = i;
                    lastJ = j; //best moves
                }
                if (FirstTurn) {
                    cout << "in " << i << ", " << j << " "
                         << (newScore == 2 ? "X wins!" : (newScore == -2) ? "O wins!" : "It's a draw!") << "\n";
                }
            }
        }
    }
    if (FirstTurn) { //first turn betkhaleene akhod awel le3ba twasalne lel ba3d kaza move
        // ba call el function b true awel mara bas w akhod el x wel y beto3 el mkan
        x = lastI;
        y = lastJ;
    }

    return (isMax ? maxScore : minScore); // if X turn, max score 2// if O turn, min score -2
}