#ifndef DEF_DB
  #define DEF_DB

  #include <stdio.h>
  #include <stdlib.h>
  #include "basic_functions.h"
  #include "crypting.h"

  #define USERS_DB_PATH "databases/users.db"
  #define BOOKS_DB_PATH "databases/books.db"

  typedef struct Book
  {
    char title[50];
    char author[50];
    char code[8];
    int copies;
    int available;
  } Book;

  typedef struct User
  {
    char fName[50];
    char lName[50];
    char mailingAdress[100];
    char email[70];
    char password[50];
    char profession[100];
    char borrowedBooks[3][8];
    int groupID;
    int numberBBooks;
  } User;

  //Function that stores a new user in the users database
  void store_new_user(User newUser);

  //Function that writes an array of integers in a specified file (must already be opened in write or append mode)
  void write_integers_array(FILE* file, int* array, const int numberElements);

  //Function that returns a string containing a line from a given file (must already be opened in read mode)
  char* read_line(FILE* file);

  //Function that creates a copy of a file until a given line from which nothing will be copied (including this specific line)
  void copy_to_line(char* path_toCopy, char* path_newFile, const int stopLine);

  //Function to return the next user read from user database given as parameter (must already be opened in read mode)
  User load_next_user(FILE* user_db);

  //Function that returns an array of integers (whole line read in database)
  int* return_int_line(FILE* user_db, int* numberChars);

#endif
