#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to perform monoalphabetic substitution encryption
void monoalphabetic_encrypt(char *plaintext, char *key) {
    while (*plaintext) {
        if (isalpha(*plaintext)) {
            char base = isupper(*plaintext) ? 'A' : 'a';
            *plaintext = key[*plaintext - base];
        }
        plaintext++;
    }
}

// Function to perform polyalphabetic substitution encryption
void polyalphabetic_encrypt(char *plaintext, char *key) {
    int key_length = strlen(key);
    int key_index = 0;

    while (*plaintext) {
        if (isalpha(*plaintext)) {
            char base = isupper(*plaintext) ? 'A' : 'a';
            char shift = key[key_index % key_length] - 'A';
            *plaintext = (char)(((int)(*plaintext - base + shift) % ALPHABET_SIZE) + base);
            key_index++;
        }
        plaintext++;
    }
}

int main() {
    char message[100];
    char key[100];

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    // Remove trailing newline characters
    message[strcspn(message, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    // Encrypt the message using polyalphabetic substitution
    polyalphabetic_encrypt(message, key);

    printf("Encrypted message: %s\n", message);

    return 0;
}

