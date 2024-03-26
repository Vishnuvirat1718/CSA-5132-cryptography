#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to encrypt the plaintext
void caesar_encrypt(char *plaintext, int key) {
    while (*plaintext) {
        if (isalpha(*plaintext)) {
            char base = isupper(*plaintext) ? 'A' : 'a';
            *plaintext = (char)(((int)(*plaintext - base + key) % ALPHABET_SIZE) + base);
        }
        plaintext++;
    }
}

// Function to decrypt the ciphertext
void caesar_decrypt(char *ciphertext, int key) {
    while (*ciphertext) {
        if (isalpha(*ciphertext)) {
            char base = isupper(*ciphertext) ? 'A' : 'a';
            *ciphertext = (char)(((int)(*ciphertext - base - key + ALPHABET_SIZE) % ALPHABET_SIZE) + base);
        }
        ciphertext++;
    }
}

int main() {
    char message[100];
    int key, choice;

    printf("Enter the message to encrypt/decrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the key (1-25): ");
    scanf("%d", &key);

    printf("Enter 1 to encrypt or 2 to decrypt: ");
    scanf("%d", &choice);

    if (choice == 1) {
        caesar_encrypt(message, key);
        printf("Encrypted message: %s\n", message);
    } else if (choice == 2) {
        caesar_decrypt(message, key);
        printf("Decrypted message: %s\n", message);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

