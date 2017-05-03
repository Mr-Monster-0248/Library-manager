#include "../headers/auth.h"

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
  char* string = (char*) malloc(numberChars * sizeof(char));
  check_alloc(string);

  for (i = 0; i < numberChars; i++)
    string[i] = (char) (encrypted[i] - i - 1);

  return string;
}


int check_password(char* toCheck, char* password)
{
  //If password is good
  if (!strcmp(toCheck, password))
    return 1;

  //If password is false
  return 0;
}


int login_menu()
{
  int height, width;
  getmaxyx(stdscr, height, width); //Getting the size of the screen

  //Displaying the options
  mvprintw(height/3 - 1, width/3, "Login (existing account)");
  mvprintw(height/3, width/3, "Create new account");
  mvprintw(height/3 + 1, width/3, "Exit the program");


  curs_set(0);

  refresh();

  return move_arrow(width/3 - 2, height/3 - 1, height/3 + 1);
}
