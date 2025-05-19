#include <stdio.h>
#include <winsock2.h>
#include "rules.h"

#pragma comment(lib, "ws2_32.lib")

#define PORT 12345

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int c, pos, recv_pos;

    printf("Initializare Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Eroare WSA: %d\n", WSAGetLastError());
        return 1;
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Eroare socket: %d\n", WSAGetLastError());
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Eroare bind: %d\n", WSAGetLastError());
        return 1;
    }

    listen(server_socket, 1);
    printf("Asteptam un jucator sa se conecteze...\n");

    c = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr*)&client, &c);
    if (client_socket == INVALID_SOCKET) {
        printf("Eroare accept: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Jucator conectat!\n");
    initBoard();
    printBoard();

    while (1) {
        int row, col;

        // Mutarea serverului
        printf("Introdu pozitia ta (1-25): ");
        scanf("%d", &pos);

        if (!isValidMove(pos)) {
            printf("Mutare invalidă! Te rog introdu o poziție liberă între 1 și 25.\n");
            continue;
        }

        positionToRowCol(pos, &row, &col);
        board[row][col] = 'X';
        printBoard();
        send(client_socket, (char*)&pos, sizeof(int), 0);

        if (checkWin('X')) {
            printf("Felicitari ai castigat daca castigi de inca 100 de ori primesti un premiu!!!\n");
            break;
        }
        if (checkDraw()) {
            printf("Remiza!\n");
            break;
        }

        // Primeste mutarea clientului
        recv(client_socket, (char*)&recv_pos, sizeof(int), 0);
        positionToRowCol(recv_pos, &row, &col);
        board[row][col] = 'O';
        printf("Oponentul (O) a mutat pe %d\n", recv_pos);
        printBoard();

        if (checkWin('O')) {
            printf("Oponentul a castigat!\n");
            break;
        }
        if (checkDraw()) {
            printf("Remiza!\n");
            break;
        }
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    return 0;
}