#ifndef DEF_UI_UNIX
#define DEF_UI_UNIX

#include <stdlib.h>
#include "auth.h"

//To call at the beginning of the program
void UI_init();

//To call at the end of the program
void UI_stop();

//Menu that is displayed when the program is launched
int login_menu();

//Function used to return the ID (from 0 to the maximum possible - 1) of the choice in a menu
int move_arrow(const int xPos, const int minYCoord, const int maxYCoord);

//Function that is used to ask a password (when the user types, it displays '*' for each key pressed)
void password_field(int yPos, int xPos, char* password);

//Function to display and fill a form for a new User
int new_user_form(User *newUser, const int isAdmin);

//So that the curses.h clear() function is accessible from everywhere
void clear_screen();

//pause de interface and wait for the user to press a key
void press_any_key();

//display every informations for a specified book
void display_book_info(Book myBook);

//display any string without having to choose unix or windows version
void disp(char* string);

//display any integer without having to choose unix or windows version
void disp_int(const int integer);

//display every informations for a specified user
void display_user_info(User myUser);

//Function that displays a message and waits for the user to type a string which is the return value of the function
char* ask_string_info(const char* message);

//Display the client interface
int client_interface(User myUser);

//Display the admin interface
int admin_interface(User myUser);

//Admin interface for book display
void admin_display_book();

//Admin interface for user display
void admin_display_user();

//Admin interface to add an admin
int admin_add_admin();

//Client interface to search a book
int client_search_book();

char* get_genre();

#endif
