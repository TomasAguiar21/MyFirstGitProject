#include <iostream>
#include <string>
using namespace std;

#define GRID_SIZE 10

char board1[GRID_SIZE][GRID_SIZE];  
char board2[GRID_SIZE][GRID_SIZE];  

void clear() {
#ifdef _WIN32
#else
    system("clear");  
#endif
}


void initBoard(char board[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            board[i][j] = '~';  
        }
    }
}


void displayBoard(char board[GRID_SIZE][GRID_SIZE]) {
    cout << "        A   B   C   D   E   F   G   H   I   J" << endl;
    cout << "       ___ ___ ___ ___ ___ ___ ___ ___ ___ ___" << endl;

    for (int i = 0; i < GRID_SIZE; i++) {  
        cout << "   " << i + 1;
        if (i < 9) {
            cout << " ";
        }
        cout << " |";
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << " " << board[i][j] << " |";  
        }
        cout << endl;
        cout << "      |___|___|___|___|___|___|___|___|___|___|" << endl;
    }
}


bool placeShip(char board[GRID_SIZE][GRID_SIZE], int row, int col) {
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && board[row][col] == '~') {
        board[row][col] = 'S'; 
        return true;
    }
    return false;  
}


bool attack(char board[GRID_SIZE][GRID_SIZE], int row, int col) {
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
        if (board[row][col] == 'S') {
            board[row][col] = 'X';  
            return true;
        } else if (board[row][col] == '~') {
            board[row][col] = 'O';  
            return false;
        }
    }
    return false;  
}

bool hasWon(char board[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == 'S') {
                return false;  
            }
        }
    }
    return true;  
}


void placeShipsForPlayer(char board[GRID_SIZE][GRID_SIZE], int numShips, string playerName) {
    int row, col;
    string input;
    
    cout << playerName << ", place your " << numShips << " ships!" << endl;

    for (int i = 0; i < numShips; i++) {
        bool placed = false;
        while (!placed) {
            displayBoard(board); 
            cout << endl << "Digite as coordenadas para colocar o seu navio (ex: a1, b2, etc.): ";
            cin >> input;

       
            col = tolower(input[0]) - 'a';
         
            row = stoi(input.substr(1)) - 1;

            if (placeShip(board, row, col)) {
                cout << "Navio colocado com sucesso em " << input << "!" << endl;
                placed = true;  
            } else {
                cout << "Posição inválida ou já ocupada. Tente novamente." << endl;
            }
        }
    }
}


bool placeShipWithLength(char board[GRID_SIZE][GRID_SIZE], int row, int col, int length, char direction) {
    if (direction == 'H') {
        if (col + length > GRID_SIZE) return false;
        for (int j = 0; j < length; j++) {
            if (board[row][col + j] != '~') return false;
        }
        for (int j = 0; j < length; j++) {
            board[row][col + j] = 'S';
        }
    } else if (direction == 'V') {
        if (row + length > GRID_SIZE) return false;
        for (int i = 0; i < length; i++) {
            if (board[row + i][col] != '~') return false;
        }
        for (int i = 0; i < length; i++) {
            board[row + i][col] = 'S';
        }
    } else {
        return false;
    }
    return true;
}

void placeClassicShips(char board[GRID_SIZE][GRID_SIZE], string playerName) {
    int shipSizes[5] = {2, 3, 3, 4, 5};
    string input;
    char direction;
    int row, col;

    cout << playerName << ", place your 5 ships (sizes 2, 3, 3, 4, 5)!" << endl;

    for (int i = 0; i < 5; i++) {
        bool placed = false;
        while (!placed) {
            displayBoard(board);
            cout << "\nShip of length " << shipSizes[i] << endl;
            cout << "Enter direction (H for horizontal, V for vertical): ";
            cin >> direction;
            direction = toupper(direction);

            cout << "Enter starting coordinate (example: a1): ";
            cin >> input;

            col = tolower(input[0]) - 'a';
            row = stoi(input.substr(1)) - 1;

            if (placeShipWithLength(board, row, col, shipSizes[i], direction)) {
                cout << "Ship of size " << shipSizes[i] << " placed successfully!\n";
                placed = true;
            } else {
                cout << "Invalid position or overlap. Try again.\n";
            }
        }
    }
}


int main() {
    initBoard(board1); 
    initBoard(board2);  

    placeClassicShips(board1, "Player 1");
    placeClassicShips(board2, "Player 2");

    int row, col;
    bool gameOver = false;
    bool player1Turn = true;

    while (!gameOver) {
        clear();  // Limpar a tela antes de mostrar o tabuleiro

        if (player1Turn) {
            displayBoard(board1);  // Mostrar tabuleiro do Jogador 1
            cout << " " << endl;
            cout << "      \\-------------- PLAYER 1 --------------/" << endl;
            cout << " " << endl;
        } else {
            displayBoard(board2);  // Mostrar tabuleiro do Jogador 2
            cout << " " << endl;
            cout << "      \\-------------- PLAYER 2 --------------/" << endl;
            cout << " " << endl;
        }

        string input;
        bool validInput = false;
        
        while (!validInput) {
            cout << endl << "Digite as coordenadas para atacar (ex: a1, b2, etc.): ";
            cin >> input;

            col = tolower(input[0]) - 'a';
            row = stoi(input.substr(1)) - 1;

            if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE) {
                validInput = true;
            } else {
                cout << "Coordenadas inválidas! Tente novamente." << endl;
            }
        }

        bool hit = false;

        if (player1Turn) {
            hit = attack(board2, row, col);
        } else {
            hit = attack(board1, row, col);
        }

        cout << (hit ? " Hit!" : " No Hit.") << endl;

        if (hasWon(board1)) {
            gameOver = true;
            cout << "Player 2 Won!" << endl;
        } else if (hasWon(board2)) {
            gameOver = true;
            cout << "Player 1 Won!" << endl;
        }

        player1Turn = !player1Turn;
    }

    return 0;
}
