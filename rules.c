#include <stdio.h>
#include <string.h>
#include "rules.h"
#include <stdlib.h>
#include <time.h>

char board[SIZE][SIZE];  // Definirea tablei de joc

// Initializeaza tabla cu spatii goale
void initBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

// Afiseaza tabla de joc
void printBoard() {
    printf("\n");
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1)
            printf("---+---+---+---+---\n");
    }
    printf("\n");
}

// Converteste pozitia (1-25) în coordonate rand și coloana
void positionToRowCol(int position, int* row, int* col) {
    position--; // Convertim de la 1-25 la 0-24 pentru calcule
    *row = position / SIZE;
    *col = position % SIZE;
}

int isValidMove(int position) {
    if (position < 1 || position > SIZE * SIZE)
        return 0;
        
    int row, col;
    positionToRowCol(position, &row, &col);
    return (board[row][col] == ' ');
}

// Verifica dacă un jucator a castigat
int checkWin(char player) {
    // Verifica randuri și coloane
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player &&
             board[i][3] == player && board[i][4] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player &&
             board[3][i] == player && board[4][i] == player)) {
            return 1;
        }
    }

    // Verifica diagonala principala
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player &&
        board[3][3] == player && board[4][4] == player) {
        return 1;
    }

    // Verifica diagonala secundara
    if (board[0][4] == player && board[1][3] == player && board[2][2] == player &&
        board[3][1] == player && board[4][0] == player) {
        return 1;
    }

    return 0;  // Niciun castigator
}

// Verifica daca este remiza (tabla este plina)
int checkDraw() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ') return 0; // Daca exista cel putin un loc liber, nu e remiza
    return 1; // Tabla este plina => remiza
}

// AI face o mutare (alege o celulă goală aleatoriu)
void aiMove() {
    int position;
    
    // Initializam generatorul de numere aleatoare (doar o data)
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    
    // Încercam pozitii aleatorii pana gasim una valida
    do {
        position = rand() % (SIZE * SIZE) + 1;  // 1-25
    } while (!isValidMove(position));
    
    // Facem mutarea
    int row, col;
    positionToRowCol(position, &row, &col);
    board[row][col] = 'O';
    printf("AI a mutat pe pozitia: %d\n", position);
}