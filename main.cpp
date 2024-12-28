// File name: Four_in_a_row_BonusAI.cpp
// Purpose: AI for Game 2 (main)
// Author(s): Yasmine Sherif Mohamed
// ID(s): 20220377
// Section: S24
// TA: Mohamed Talaat
// Date: 16 Dec 2023
// Version: 1.0

#include <bits/stdc++.h>
#include "Connect4.h"

using namespace std;


int main() {

    int choice;
    Player *players[2];
    players[0] = new Player(1, 'x');
    cout << "Welcome to FCAI Connect 4 Game. :)\n";
    cout << "Do you want to play with (1) Friend Player (2) Random Player (3) AI Player: ";
    cin >> choice;
    Board *brd = new Four_in_a_row_Board;
    if (choice == 1) {
        players[1] = new Player(2, 'o');
    }
    else if (choice == 2) {
        players[1] = new RandomPlayer('o', 6);
    }
    else {
        players[1] = new AIPlayer('o', brd);
    }
    GameManager x_o_game(brd, players);
    x_o_game.run();

system("pause");

return 0;

}