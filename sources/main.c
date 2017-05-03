#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "../headers/auth.h"

void curses_init();
void curses_stop();



int main(int argc, char** argv)
{
  curses_init();

  login_menu();

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
