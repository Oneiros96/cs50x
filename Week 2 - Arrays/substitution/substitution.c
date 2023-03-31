#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void cipher(string cipher, string plain);
void check_cipher(string cipher);

int main(int argc, string argv[])
{
    //checks for valid number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //checks for correkt cipher length
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        check_cipher(argv[1]);
    }
    string plain_text = get_string("plaintext: ");
    cipher(argv[1], plain_text);
    printf("ciphertext: %s\n", plain_text);
    return 0;

}

void cipher(string cipher, string plain)
{
    char lower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char upper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char upperc[26];
    char lowerc[26];
    //builds 2 arrays one for cipher in upper letters one for cipher in lower letters.
    for (int i = 0; i < 26; i++)
        if (isupper(cipher[i]))
        {
            upperc[i] = cipher[i];
            lowerc[i] = cipher[i] + 32;
        }
        else
        {
            upperc[i] = cipher[i] - 32;
            lowerc[i] = cipher[i];
        }

    //"encrypts" text
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (isupper(plain[i]))
        {
            int x = 0;
            //checks positition of current letter in alphabet
            while (plain[i] != upper[x])
            {
                x++;
            }
            plain[i] = upperc[x];
        }
        else if (islower(plain[i]))
        {
            int x = 0;
            //checks positition of current letter in alphabet
            while (plain[i] != lower[x])
            {
                x++;
            }
            plain[i] = lowerc[x];
        }
        else
        {
            plain[i] = plain[i];
        }
    }

}
void check_cipher(string cipher)
{
    // checks for digits in cipher and compares every lettter with the others to check for double letters
    for (int i = 0, n = strlen(cipher); i < n; i++)
    {
        if (isdigit(cipher[i]) != 0)
        {
            exit(1);
        }
        for (int j = i + 1; j < n; j++)
        {
            if (cipher[i] == cipher[j])
            {
                exit(1);
            }
        }
    }
}