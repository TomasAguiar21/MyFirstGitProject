#include <iostream>
#include <string>
using namespace std;

#define GRID_SIZE 10  // Tamanho do tabuleiro 10x10
#define NUM_SHIPS 3  // Número de navios por jogador

char board1[GRID_SIZE][GRID_SIZE];  // Tabuleiro do Jogador 1
char board2[GRID_SIZE][GRID_SIZE];  // Tabuleiro do Jogador 2

// Função para limpar a tela
void clear() {
#ifdef _WIN32
    // system("CLS");  // Limpa a tela no Windows 
#else
    system("clear");  // Limpa a tela no Linux/Mac
#endif
}

// Função para inicializar o tabuleiro com água ('~')
void initBoard(char board[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            board[i][j] = '~';  // '~' significa água
        }
    }
}

// Função para exibir o tabuleiro de um jogador
void displayBoard(char board[GRID_SIZE][GRID_SIZE]) {
    cout << "        A   B   C   D   E   F   G   H   I   J" << endl;
    cout << "       ___ ___ ___ ___ ___ ___ ___ ___ ___ ___" << endl;

    for (int i = 0; i < GRID_SIZE; i++) {  // Número da linha
        cout << "   " << i + 1;
        if (i < 9) {
            cout << " ";
        }
        cout << " |";
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << " " << board[i][j] << " |";  // Conteúdo da célula
        }
        cout << endl;
        cout << "      |___|___|___|___|___|___|___|___|___|___|" << endl;
    }
}

// Função para colocar um navio em uma posição
bool placeShip(char board[GRID_SIZE][GRID_SIZE], int row, int col) {
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && board[row][col] == '~') {
        board[row][col] = 'S';  // 'S' significa navio
        return true;
    }
    return false;  // Posição inválida ou ocupada
}

// Função para realizar um ataque
bool attack(char board[GRID_SIZE][GRID_SIZE], int row, int col) {
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
        if (board[row][col] == 'S') {
            board[row][col] = 'X';  // Acertou
            return true;
        } else if (board[row][col] == '~') {
            board[row][col] = 'O';  // Errou
            return false;
        }
    }
    return false;  // Coordenada inválida
}

// Função para verificar se algum jogador venceu
bool hasWon(char board[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == 'S') {
                return false;  // Se ainda houver um navio, ninguém venceu
            }
        }
    }
    return true;  // Todos os navios foram atingidos
}

// Função para permitir que o jogador coloque seus navios
void placeShipsForPlayer(char board[GRID_SIZE][GRID_SIZE], int numShips, string playerName) {
    int row, col;
    string input;
    
    cout << playerName << ", place your " << numShips << " ships!" << endl;

    for (int i = 0; i < numShips; i++) {
        bool placed = false;
        while (!placed) {
            displayBoard(board);  // Exibir o tabuleiro atual
            cout << endl << "Digite as coordenadas para colocar o seu navio (ex: a1, b2, etc.): ";
            cin >> input;

            // Converter a parte da letra (A-J) para índice da coluna (0-9)
            col = tolower(input[0]) - 'a';
            // Converter a parte do número (1-10) para índice da linha (0-9)
            row = stoi(input.substr(1)) - 1;

            if (placeShip(board, row, col)) {
                cout << "Navio colocado com sucesso em " << input << "!" << endl;
                placed = true;  // O navio foi colocado, podemos passar para o próximo
            } else {
                cout << "Posição inválida ou já ocupada. Tente novamente." << endl;
            }
        }
    }
}

int main() {
    initBoard(board1);  // Inicializar tabuleiro do jogador 1
    initBoard(board2);  // Inicializar tabuleiro do jogador 2

    // Colocar navios para o Jogador 1 e Jogador 2
    placeShipsForPlayer(board1, NUM_SHIPS, "Jogador 1");
    placeShipsForPlayer(board2, NUM_SHIPS, "Jogador 2");

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
        
        // Loop até o jogador fornecer uma entrada válida
        while (!validInput) {
            cout << endl << "Digite as coordenadas para atacar (ex: a1, b2, etc.): ";
            cin >> input;

            // Converter a parte da letra (A-J) para índice da coluna (0-9)
            col = tolower(input[0]) - 'a';
            // Converter a parte do número (1-10) para índice da linha (0-9)
            row = stoi(input.substr(1)) - 1;

            // Verificar se a coordenada está dentro do tabuleiro
            if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE) {
                validInput = true;  // Entrada válida, sair do loop
            } else {
                cout << "Coordenadas inválidas! Tente novamente." << endl;
            }
        }

        bool hit = false;

        if (player1Turn) {
            hit = attack(board2, row, col);  // Jogador 1 ataca no tabuleiro do jogador 2
        } else {
            hit = attack(board1, row, col);  // Jogador 2 ataca no tabuleiro do jogador 1
        }

        cout << (hit ? " Hit!" : " No Hit.") << endl;

        // Verificar se alguém venceu
        if (hasWon(board1)) {
            gameOver = true;
            cout << "Player 2 Won!" << endl;
        } else if (hasWon(board2)) {
            gameOver = true;
            cout << "Player 1 Won!" << endl;
        }

        player1Turn = !player1Turn;  // Trocar de turno
    }

    return 0;
}
