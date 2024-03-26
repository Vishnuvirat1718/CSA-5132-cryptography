#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to prepare the key by removing duplicate letters and 'J', and fill into the matrix
void prepare_key(char *key, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    char *temp = key;
    int len = 0;
    int i, j;
    int used[26] = {0};

    while (*temp) {
        if (isalpha(*temp)) {
            *temp = toupper(*temp);
            if (*temp == 'J')
                *temp = 'I';
            if (!used[*temp - 'A']) {
                matrix[len / MATRIX_SIZE][len % MATRIX_SIZE] = *temp;
                used[*temp - 'A'] = 1;
                len++;
            }
        }
        temp++;
    }

    for (i = len / MATRIX_SIZE; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            char ch;
            do {
                ch = 'A' + rand() % 26;
            } while (used[ch - 'A']);
            matrix[i][j] = ch;
            used[ch - 'A'] = 1;
        }
    }
}

// Function to find row and column of each character in the matrix
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

// Function to encrypt plaintext using Playfair algorithm
void playfair_encrypt(char *plaintext, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int len = strlen(plaintext);
    int i;

    // Convert 'J' to 'I' in plaintext
    for (i = 0; i < len; i++) {
        if (plaintext[i] == 'J')
            plaintext[i] = 'I';
    }

    // Adjust length of plaintext if it's odd
    if (len % 2 != 0) {
        plaintext[len] = 'X';
        plaintext[len + 1] = '\0';
        len++;
    }

    // Encrypt
    for (i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        find_position(matrix, plaintext[i], &row1, &col1);
        find_position(matrix, plaintext[i + 1], &row2, &col2);
        if (row1 == row2) {
            plaintext[i] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
            plaintext[i + 1] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
        } else if (col1 == col2) {
            plaintext[i] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
            plaintext[i + 1] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
        } else {
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
}

int main() {
    char key[50];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char plaintext[100];

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Prepare the key matrix
    prepare_key(key, matrix);

    // Encrypt the plaintext
    playfair_encrypt(plaintext, matrix);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}

