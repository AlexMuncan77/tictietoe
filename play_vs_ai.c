#include <stdio.h>
#include "rules.h"

int main() {
    printf("Pozitii pe tabla (1-25):\n");
printf(" 1 | 2 | 3 | 4 | 5 \n");
printf("---+---+---+---+---\n");
printf(" 6 | 7 | 8 | 9 | 10\n");
printf("---+---+---+---+---\n");
printf(" 11| 12| 13| 14| 15\n");
printf("---+---+---+---+---\n");
printf(" 16| 17| 18| 19| 20\n");
printf("---+---+---+---+---\n");
printf(" 21| 22| 23| 24| 25\n\n");

    int position;
    char player = 'X'; // Tu joci cu 'X', AI cu 'O'
    
    initBoard();
    printBoard();

    while (1) {
        // Mutarea jucatorului
        printf("Introdu pozitia ta (1-25): ");
        scanf("%d", &position);

        if (!isValidMove(position)) {
            printf("Mutare invalida! Incearca din nou.\n");
            continue;
        }

        int row, col;
        positionToRowCol(position, &row, &col);
        board[row][col] = player;
        printBoard();

        if (checkWin(player)) {
            printf("Ai castigat!\n");
            break;
        }

        if (checkDraw()) {
            printf("Remiza!\n");
            break;
        }

        // Mutarea AI-ului
        aiMove();
        printBoard();

        if (checkWin('O')) {
            printf("AI-ul a castigat! Mai Incearca.\n");
            break;
        }

        if (checkDraw()) {
            printf("Remiza!\n");
            break;
        }
    }

    return 0;
}