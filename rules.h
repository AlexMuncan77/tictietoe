#ifndef RULES_H
#define RULES_H

#define SIZE 5  // Dimensiunea tablei 5x5

extern char board[SIZE][SIZE];  // Tabla globală

void initBoard();          // Initializeaza tabla
void printBoard();         // Afiseaza tabla
void positionToRowCol(int position, int* row, int* col); // Converteste pozitia in rand și coloana
int isValidMove(int position); // Verifica daca o mutare este valida
int checkWin(char player); // Verifica daca un jucator a castigat
int checkDraw();           // Verifica daca e remiza
void aiMove();             // AI face o mutare

#endif