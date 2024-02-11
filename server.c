#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
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
    int clientSocket, num;
    struct sockaddr_in serverAddr;

    clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("Enter a number: ");
    scanf("%d", &num);

    sendto(clientSocket, &num, sizeof(num), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    int result;
    socklen_t addr_size = sizeof(serverAddr);
    recvfrom(clientSocket, &result, sizeof(result), 0, (struct sockaddr*)&serverAddr, &addr_size);

    if (result)
        printf("%d is an Armstrong number.\n", num);
    else
        printf("%d is not an Armstrong number.\n", num);

    close(clientSocket);
    return 0;
}
