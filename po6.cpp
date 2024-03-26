#include <stdio.h>

// Greatest common divisor function
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Modular inverse function
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // Inverse doesn't exist
}

// Break affine cipher given two known letters
void break_affine_cipher(char most_frequent, char second_most_frequent) {
    // ASCII values of most frequent and second most frequent letters
    int most_frequent_ascii = most_frequent - 'A';
    int second_most_frequent_ascii = second_most_frequent - 'A';

    // ASCII values of 'B' and 'U'
    int B_ascii = 'B' - 'A';
    int U_ascii = 'U' - 'A';

    // Determine the size of the alphabet
    int alphabet_size = 26;

    // Determine the multiplicative key (a)
    int a = (most_frequent_ascii - second_most_frequent_ascii) % alphabet_size;
    if (a < 0) // Ensure 'a' is positive
        a += alphabet_size;

    // Determine the additive key (b)
    int b = (B_ascii - (a * U_ascii)) % alphabet_size;
    if (b < 0) // Ensure 'b' is positive
        b += alphabet_size;

    // Find modular inverse of 'a' modulo the alphabet size
    int a_inverse = mod_inverse(a, alphabet_size);

    if (a_inverse == -1) {
        printf("Affine cipher cannot be broken. No modular inverse of 'a'.\n");
        return;
    }

    // Print the multiplicative key (a) and additive key (b)
    printf("The multiplicative key (a) is: %d\n", a);
    printf("The additive key (b) is: %d\n", b);

    // Print the plaintext
    printf("Plaintext:\n");
    for (int i = 0; i < 26; i++) {
        int decrypted_letter = (a_inverse * (i - b)) % alphabet_size;
        if (decrypted_letter < 0) // Ensure decrypted_letter is positive
            decrypted_letter += alphabet_size;
        printf("%c ", decrypted_letter + 'A');
    }
    printf("\n");
}

int main() {
    // Given most frequent and second most frequent letters
    char most_frequent = 'B';
    char second_most_frequent = 'U';

    printf("Breaking affine cipher...\n");
    break_affine_cipher(most_frequent, second_most_frequent);

    return 0;
}

