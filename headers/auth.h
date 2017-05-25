#ifndef DEF_AUTH
#define DEF_AUTH

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "DB.h"
  #include "basic_functions.h"
  #ifdef __WIN32__
    #include "UI_windows.h"
  #else
    #include "UI_unix.h"
  #endif

  /* Function that checks if the password typed corresponds to the right password
     RETURN VALUES:
      - 0 if wrong password
      - 1 if good password
  */
  int check_password(char* toCheck, char* password);

  //Function that displays the login menu
  int login_menu();

  //Function that asks the data for a new user to store in the database
  int ask_new_user_data(User *newUser);

  //Function to get a user by his email
  /* RETURN VALUES
    - 0: no user found
    - 1: user found and stocked in getUser (parameter)
  */
  int find_user(char* email, User* getUser);

  //Function to log into an existing account
  /* RETURN VALUES
    1: user found and loaded in currentUser and password match
    0: user not found after 3 attempts, or wrong password 3 times (currentUser may contain the user)
  */
  int login(User* currentUser);

  //Function that returns 1 if a given string has the form of an email adress, 0 if not
  int check_if_email(const char* toCheck);

#endif
