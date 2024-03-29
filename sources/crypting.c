#include "../headers/crypting.h"


int* encrypt_to_int(char* string)
{
    int i = 0;
    int* crypted = (int*) malloc(strlen(string) * sizeof(int));
    check_alloc(crypted);

    for (i = 0; i < strlen(string); i++)
        crypted[i] = string[i] + i + 1;

    return crypted;
}


char* decrypt_to_string(int* encrypted, const int numberChars)
{
    int i = 0;
    char* string = (char*) malloc((numberChars + 1) * sizeof(char));
    check_alloc(string);

    for (i = 0; i < numberChars; i++)
        string[i] = (char) (encrypted[i] - i - 1);

    string[numberChars] = '\0';

    return string;
}
