#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to find position of a character in the matrix
void find_position(char matrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decrypt Playfair-encoded message
void playfair_decrypt(char *ciphertext, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int len = strlen(ciphertext);
    int i;

    for (i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        find_position(matrix, ciphertext[i], &row1, &col1);
        find_position(matrix, ciphertext[i + 1], &row2, &col2);

        if (row1 == row2) {
            printf("%c%c", matrix[row1][(col1 + 4) % MATRIX_SIZE], matrix[row2][(col2 + 4) % MATRIX_SIZE]);
        } else if (col1 == col2) {
            printf("%c%c", matrix[(row1 + 4) % MATRIX_SIZE][col1], matrix[(row2 + 4) % MATRIX_SIZE][col2]);
        } else {
            printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
        }
    }
    printf("\n");
}

int main() {
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char ciphertext[100];

    // Get Playfair key from the user
    printf("Enter the 5x5 Playfair key matrix (without spaces): \n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            scanf(" %c", &matrix[i][j]);
            matrix[i][j] = toupper(matrix[i][j]);
        }
    }

    // Flush the input buffer
    while (getchar() != '\n');

    // Get encoded message from the user
    printf("Enter the encoded message: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove trailing newline

    // Decrypt the message using Playfair cipher
    printf("Deciphered message: ");
    playfair_decrypt(ciphertext, matrix);

    return 0;
}

