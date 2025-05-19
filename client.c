#include <stdio.h>
#include <winsock2.h>
#include "rules.h"

#pragma comment(lib, "ws2_32.lib")
#define PORT 12345

int main() {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    int pos, recv_pos;

    printf("Initializare Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Eroare WSA: %d\n", WSAGetLastError());
        return 1;
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        printf("Eroare socket: %d\n", WSAGetLastError());
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    printf("Conectare la server...\n");
    if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Conectare esuata.\n");
        return 1;
    }

    printf("Conectat la server!\n");
    initBoard();
    printBoard();

    while (1) {
        int row, col;

        // Primeste mutarea de la server
        recv(s, (char*)&recv_pos, sizeof(int), 0);
        positionToRowCol(recv_pos, &row, &col);
        board[row][col] = 'X';
        printf("Oponentul (X) a mutat pe %d\n", recv_pos);
        printBoard();

        if (checkWin('X')) {
            printf("\n Oponentul a castigat!\n");
            break;
        }
        if (checkDraw()) {
            printf("\n Remiza!\n");
            break;
        }

        // Mutarea clientului
        do {
            printf("Introdu pozitia ta (1-25): ");
            scanf("%d", &pos);
            if (!isValidMove(pos))
                printf("Mutare invalida! Te rog introdu o pozitie libera intre 1 si 25.\n");
        } while (!isValidMove(pos));

        positionToRowCol(pos, &row, &col);
        board[row][col] = 'O';
        printBoard();
        send(s, (char*)&pos, sizeof(int), 0);

        if (checkWin('O')) {
            printf("\n FELICITARI! AI CASTIGAT! \n");
            break;
        }
        if (checkDraw()) {
            printf("\n Remiza!\n");
            break;
        }
    }

    closesocket(s);
    WSACleanup();
    return 0;
}