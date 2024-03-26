#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to prepare the key by removing duplicate letters and 'J'
void prepare_key(char *key, char *clean_key) {
    int len = 0;
    int i;
    int used[26] = {0};

    while (*key) {
        if (isalpha(*key)) {
            *key = toupper(*key);
            if (*key == 'J')
                *key = 'I';
            if (!used[*key - 'A']) {
                clean_key[len++] = *key;
                used[*key - 'A'] = 1;
            }
        }
        key++;
    }

    // Fill in the rest of the key with remaining alphabets
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (!used[i]) {
            clean_key[len++] = 'A' + i;
        }
    }
}

// Function to encrypt plaintext using monoalphabetic substitution
void monoalphabetic_encrypt(char *plaintext, char *key) {
    while (*plaintext) {
        if (isalpha(*plaintext)) {
            char base = isupper(*plaintext) ? 'A' : 'a';
            *plaintext = key[*plaintext - base];
        }
        plaintext++;
    }
}

int main() {
    char message[100];
    char key[ALPHABET_SIZE];
    char clean_key[ALPHABET_SIZE];

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);

    // Prepare the key by removing duplicates and 'J'
    prepare_key(key, clean_key);

    // Encrypt the message using monoalphabetic substitution
    monoalphabetic_encrypt(message, clean_key);

    printf("Encrypted message: %s\n", message);

    return 0;
}

