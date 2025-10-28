#include <iostream>
#include <string>
using namespace std;

#define GRID_SIZE 10  // 10x10 grid

char board[GRID_SIZE][GRID_SIZE];  // 10x10 board

// Function to initialize the board with water ('~')
void initBoard() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            board[i][j] = '~';  // '~' means water
        }
    }
}

// Function to display the board in the specified format
void displayBoard() {


system("clear");

    cout << "                                                                                             " << endl;
    cout << "                                                                                             " << endl;
    cout << "                                                                                             " << endl;
    cout << "        A   B   C   D   E   F   G   H   I   J                                                 " << endl;
    cout << "       ___ ___ ___ ___ ___ ___ ___ ___ ___ ___                                                " << endl;

    for (int i = 0; i < GRID_SIZE; i++) {  // Row number 
        cout << "   " << i + 1;
        if(i<9) {
            cout << " ";
        }
        cout  << " |";
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << " " << board[i][j] << " |";  // Cell content
        }
        cout << endl;
        cout << "      |___|___|___|___|___|___|___|___|___|___|                                               " << endl;
    }
    cout << "                                                                                             " << endl;
    cout << "                                                                                             " << endl;
    cout << "                                                                                             " << endl;
}

// Function to place a ship at a fixed position
bool placeShip(int row, int col) {
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && board[row][col] == '~') {
        board[row][col] = 'S';  // 'S' means ship
        return true;
    }
    return false;  // Invalid placement
}

// Function to handle an attack
bool attack(int row, int col) {
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
        if (board[row][col] == 'S') {
            board[row][col] = 'X';  // Mark hit
            return true;
        } else if (board[row][col] == '~') {
            board[row][col] = 'O';  // Mark miss
            return false;
        }
    }
    return false;  // Invalid coordinate
}

int main() {

    initBoard();
    
    // Place one ship at a fixed position (e.g., C3)
    placeShip(2, 2);  // Ship at (2, 2) (C3 on the grid)

    int row, col;
    bool gameOver = false;
    bool player1Turn = true;

    while (!gameOver) {
        displayBoard();
        cout << "Player " << (player1Turn ? "1" : "2") << "'s turn." << endl;
        cout << "Enter coordinates to attack (e.g., a1, b2, etc.): ";
        
        string input;
        cin >> input;
        
        // Convert the letter part (A-J) to column index (0-9)
        col = input[0] - 'a';
        // Convert the number part (1-10) to row index (0-9)
        row = stoi(input.substr(1)) - 1;

        if (attack(row, col)) {
            cout << "Hit!" << endl;
        } else {
            cout << "Miss." << endl;
        }

        // Check for win condition (ship is hit)
        if (board[2][2] == 'X') {  // Check if the ship at (2, 2) is hit
            gameOver = true;
            cout << "Player " << (player1Turn ? "1" : "2") << " wins!" << endl;
        }

        player1Turn = !player1Turn;  // Switch turns
    }

    return 0;
}