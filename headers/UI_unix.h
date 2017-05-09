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
int new_user_form(User *newUser);

#endif
