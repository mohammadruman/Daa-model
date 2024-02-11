#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345

int isArmstrong(int num) {
    int originalNum, remainder, result = 0;

    originalNum = num;

    while (originalNum != 0) {
        remainder = originalNum % 10;
        result += remainder * remainder * remainder;
        originalNum /= 10;
    }

    if (result == num)
        return 1; // It's an Armstrong number
    else
        return 0; // It's not an Armstrong number
}

int main() {
    int serverSocket, num, result;
    struct sockaddr_in serverAddr, clientAddr;

    serverSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in binding");
        exit(1);
    }

    printf("UDP server is waiting for incoming connections...\n");

    socklen_t addr_size = sizeof(clientAddr);
    recvfrom(serverSocket, &num, sizeof(num), 0, (struct sockaddr*)&clientAddr, &addr_size);

    result = isArmstrong(num);

    sendto(serverSocket, &result, sizeof(result), 0, (struct sockaddr*)&clientAddr, addr_size);

    close(serverSocket);
    return 0;
}
