#include "../headers/display.h"


int move_arrow(const int xPos, const int minYCoord, const int maxYCoord)
{
  curs_set(0); //Hidding cursor
  int pressedKey;
  int currentPos = minYCoord;

  mvprintw(minYCoord, xPos, ">");
  refresh();

  do {
    //Waiting for the user to press a key
    pressedKey = getch();

    //If pressed up arrow key and possible to move the arrow to asked position
    if (pressedKey == KEY_UP && currentPos > minYCoord)
    {
      mvprintw(currentPos--, xPos, " ");
      mvprintw(currentPos, xPos, ">");
      refresh();
    }

    //If pressed up arrow key and possible to move the arrow to asked position
    if (pressedKey == KEY_DOWN && currentPos < maxYCoord)
    {
      mvprintw(currentPos++, xPos, " ");
      mvprintw(currentPos, xPos, ">");
      refresh();
    }
  } while(pressedKey != 10); //While pressedKey != ENTER

  return currentPos - minYCoord;
}
