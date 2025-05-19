#include <stdio.h>
#include <string.h>
#include "rules.h"

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

// Verifica daca o mutare este valida
int isValidMove(int position) {
    if (position < 1 || position > SIZE * SIZE)
        return 0;

    int row, col;
    positionToRowCol(position, &row, &col);
    return (board[row][col] == ' ');
}

// Verifica daca un jucator a castigat
int checkWin(char player) {
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player &&
             board[i][3] == player && board[i][4] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player &&
             board[3][i] == player && board[4][i] == player)) {
            return 1;
        }
    }

    // Diagonala principală
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player &&
        board[3][3] == player && board[4][4] == player)
        return 1;

    // Diagonala secundară
    if (board[0][4] == player && board[1][3] == player && board[2][2] == player &&
        board[3][1] == player && board[4][0] == player)
        return 1;

    return 0;
}

// Verifica daca tabla este plina => remiza
int checkDraw() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}