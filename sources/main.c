#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "../headers/DB.h"
#include "../headers/auth.h"
#include "../headers/display.h"
#include "../headers/basic_functions.h"

void curses_init();
void curses_stop();


int main(int argc, char** argv)
{
  User myUser;

  curses_init();

  switch(login_menu())
  {
      case 0:
      break;

      case 1:
        while(!ask_new_user_data(&myUser));
        clear();
      break;

      case 2:
      break;

      default:
      break;
  }

  curses_stop();

  return EXIT_SUCCESS;
}


void curses_init()
{
  //Init curses
  initscr();

  //Deactivation of buffer at TTY pilot
  cbreak();

  //Deactivation of automatic display of entries
  noecho();

  //Allow keyboard capture (including arrow keys)
  keypad(stdscr, TRUE);
}

void curses_stop()
{
  endwin();
}
