/*------------------------------\
|  Code (C) 2020 Micah Lindley  |
|   Part of the CS50x course    |
|-------------------------------|
|Do not use this code to cheat! |
\------------------------------*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool isNumeric(string input)
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (!(isdigit(input[i])))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, string argv[])
{
    if (argc == 2 && isNumeric(argv[1]))
    {
        int key = atoi(argv[1]);
        printf("key: %i\n", key);
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        char ciphertext[strlen(plaintext)];
        for (int i = 0; i < strlen(plaintext); i++)
        {
            if (isupper(plaintext[i]))
            {
                int offset = 64;
                int makingCipher = ((int) plaintext[i]) - offset; // convert the ith letter of plaintext to ASCII
                makingCipher += key;
                makingCipher = makingCipher % 26;
                ciphertext[i] = (char) (makingCipher + offset);
            printf("%c", ciphertext[i]);
            }
            else if (islower(plaintext[i]))
            {
                int offset = 96;
                int makingCipher = ((int) plaintext[i]) - offset; // convert the ith letter of plaintext to ASCII
                makingCipher += key;
                makingCipher = makingCipher % 26;
                ciphertext[i] = (char) (makingCipher + offset);
                printf("%c", ciphertext[i]);
            }
            else
            {
                int offset = 0;
                printf("%c", plaintext[i]);
            }
        }

        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
