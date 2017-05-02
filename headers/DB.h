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

#endif
