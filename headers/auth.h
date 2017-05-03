#ifndef DEF_CRYPT
#define DEF_CRYPT

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <curses.h>
  #include "basic_functions.h"

  //Function that returns an array of integers corresponding to the encrypted string
  int* encrypt_to_int(char* string);

  //Function that returns a string decrypted from an array of integers
  char* decrypt_to_string(int* encrypted, const int numberChars);

  /* Function that checks if the password typed corresponds to the right password
     RETURN VALUES:
      - 0 if wrong password
      - 1 if good password
  */
  int check_password(char* toCheck, char* password);

  //Function that displays the login menu
  int login_menu();

#endif
