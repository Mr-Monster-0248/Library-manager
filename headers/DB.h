#ifndef DEF_DB
#define DEF_DB

#include <stdio.h>
#include <stdlib.h>

#include "dates.h"
#include "basic_functions.h"
#include "crypting.h"

#define USERS_DB_PATH ".databases/users.db"
#define BOOKS_DB_PATH ".databases/books.db"
#define TEMP_DB_PATH ".databases/temp.db"

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
    Date returnDates[3];
    int groupID;
    int numberBBooks;
} User;


//Function that stores a new user in the users database
void store_user(User newUser, const char* db_path);

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

//Function to copy a user to another one
void copy_User(User* to, User from);

//Function to return the next book read from book database given as parameter (must already be opened in read mode)
Book load_next_book(FILE* books_db);

//Function to display all the books of the library (display the entire database)
void display_book_db();

//Function to display all the available books
void display_available_books();

void display_books_by_author();

void display_books_by_title();

void display_book_by_code();

void search_user_by_name();

void search_user_by_email();

void display_all_users();

//Function to get a users' space (user ID) in users database, returns -1 if user not found
int get_user_ID(User myUser);

Book get_book_by_code(const char* bookCode);

//Function to update a user's data in the users database
void update_user(User myUser);

//Function to alphabetically order the users database after a new user was created
void order__users_db();

//Function to decode the users database and print the result in the file which path is given as parameter
void decode_users_db(const char* filePath);

#endif
