#ifndef DEF_DB
#define DEF_DB

  #include <stdio.h>
  #include <stdlib.h>
  #include "auth.h"
  #include "basic_functions.h"

  #define USERS_DB_PATH "../databases/users.db"
  #define BOOKS_DB_PATH "../databases/books.db"

  typedef struct Book
  {
    char title[50];
    char author[50];
    char code[8];
    int inStock;
  } Book;

  typedef struct User
  {
    char username[50];
    char password[50];
    int groupID;
    Book* borrowedBooks;
  } User;

  //Function that stores a new user in the users database
  void store_new_user(User newUser);

  //Function that writes an array of integers in a specified file (must already be opened in write or append mode)
  void write_integers_array(FILE* file, int* array, const int numberElements);

  //Function that returns a string containing a line from a given file (must already be opened in read mode)
  char* read_line(FILE* file);

  //Function that creates a copy of a file until a given line from which nothing will be copied (including this specific line)
  void copy_to_line(char* path_toCopy, char* path_newFile, const int stopLine);

#endif
