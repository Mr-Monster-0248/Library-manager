#ifndef DEF_UI_WINDOWS
#define DEF_UI_WINDOWS

#include "auth.h"
#include "basic_functions.h"


#define CLEAR_SCREEN() system("cls")

int login(User* currentUser);

int login_menu();

void UI_init();

void UI_stop();

void password_field(int yPos, int xPos, char* password);

int new_user_form(User *newUser);

void clear();

#endif
