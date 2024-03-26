#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to find the position of a character in the Playfair matrix
void find_position(char matrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == ch || (matrix[i][j] == 'I' && ch == 'J')) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt plaintext using the Playfair cipher
void playfair_encrypt(char *plaintext, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int len = strlen(plaintext);
    int i;
    
    for (i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        find_position(matrix, plaintext[i], &row1, &col1);
        find_position(matrix, plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
            printf("%c%c", matrix[row1][(col1 + 1) % MATRIX_SIZE], matrix[row2][(col2 + 1) % MATRIX_SIZE]);
        } else if (col1 == col2) {
            printf("%c%c", matrix[(row1 + 1) % MATRIX_SIZE][col1], matrix[(row2 + 1) % MATRIX_SIZE][col2]);
        } else {
            printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
        }
    }
    printf("\n");
}

int main() {
    char matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    char plaintext[] = "Must see you over Cadogan West. Coming at once.";

    printf("Encrypted message: ");
    playfair_encrypt(plaintext, matrix);

    return 0;
}

