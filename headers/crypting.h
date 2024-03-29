#ifndef DEF_CRYPT
#define DEF_CRYPT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic_functions.h"

//Function that returns an array of integers corresponding to the encrypted string
int* encrypt_to_int(char* string);

//Function that returns a string decrypted from an array of integers
char* decrypt_to_string(int* encrypted, const int numberChars);

#endif
