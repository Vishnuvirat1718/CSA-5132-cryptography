#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 2

void hillCipherEncrypt(char message[], int key[N][N]) {
    int len = strlen(message);
    int i, j, k, l;
    int cipher[N][1];

    char normalized_message[len];
    int index = 0;
    for (i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            normalized_message[index++] = toupper(message[i]);
        }
    }
    normalized_message[index] = '\0';

    int padding = len % N == 0 ? 0 : N - (len % N);
    len += padding;
    for (i = 0; i < padding; i++) {
        normalized_message[index++] = 'X';
    }
    normalized_message[index] = '\0';

    for (i = 0; i < len; i += N) {
        for (j = 0; j < N; j++) {
            cipher[j][0] = 0;
            for (k = 0; k < N; k++) {
                cipher[j][0] += key[j][k] * (normalized_message[i + k] - 'A');
            }
            cipher[j][0] %= 26;
        }

        for (l = 0; l < N; l++) {
            printf("%c", (char)(cipher[l][0] + 'A'));
        }
    }
}

int main() {
    int key[N][N];
    char message[100];

    // Get the Hill cipher key from the user
    printf("Enter the Hill cipher key (4 integers separated by spaces):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    // Flush the input buffer
    while (getchar() != '\n');

    // Get the message from the user
    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove trailing newline

    printf("Original Message: %s\n", message);
    printf("Encrypted Message: ");
    hillCipherEncrypt(message, key);
    printf("\n");

    return 0;
}

