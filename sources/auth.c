#include "../headers/auth.h"


int* encrypt_to_int(char* string)
{
  int i = 0;
  int* crypted = (int*) malloc(strlen(string) * sizeof(int));
  check_alloc(crypted);

  for (i = 0; i < strlen(string); i++)
    crypted[i] = string[i] + i + 1;

  return crypted;
}


char* decrypt_to_string(int* encrypted, const int numberChars)
{
  int i = 0;
  char* string = (char*) malloc(numberChars * sizeof(char));
  check_alloc(string);

  for (i = 0; i < numberChars; i++)
    string[i] = (char) (encrypted[i] - i - 1);

  return string;
}


int check_password(char* toCheck, char* password)
{
  //If password is good
  if (!strcmp(toCheck, password))
    return 1;

  //If password is false
  return 0;
}


int login_menu()
{
  int height, width;
  getmaxyx(stdscr, height, width); //Getting the size of the screen

  //Displaying the options
  mvprintw(height/3 - 1, width/3, "Login (existing account)");
  mvprintw(height/3, width/3, "Create new account");
  mvprintw(height/3 + 1, width/3, "Exit the program");


  curs_set(0);

  refresh();

  return move_arrow(width/3 - 2, height/3 - 1, height/3 + 1);
}


int ask_new_user_data(User *newUser)
{
  int height, width;
  char cPassword[50];


  getmaxyx(stdscr, height, width);

  //Setting cursor visible and keeping trace of what is typed
  //Clearing the screen
  clear();
  echo();
  curs_set(1);

  /*#################################
  #                                 #
  #     Asking for informations     #
  #                                 #
  #################################*/

  //Displaying the form
  mvprintw(height/5, width/2 - (strlen("====== New User =====")/2), "====== New User =====");
  mvprintw(2 * height/5, width/4, "Email adress    (max.69 characters): ");
  mvprintw(2 * height/5 + 1, width/4, "First name     (max. 49 characters): ");
  mvprintw(2 * height/5 + 2, width/4, "Last name      (max. 49 characters): ");
  mvprintw(2 * height/5 + 3, width/4, "Mailing adress (max. 99 characters): ");
  mvprintw(2 * height/5 + 4, width/4, "Profession     (max. 99 characters): ");
  mvprintw(2 * height/5 + 5, width/4, "Password       (max. 49 characters): ");
  refresh();

  //Asking email adress
  move(2 * height/5, width/4 + strlen("Email adress    (max.69 characters): "));
  getnstr(newUser->email, 69);

  //Asking first name
  move(2 * height/5 + 1, width/4 + strlen("First name     (max. 49 characters): "));
  getnstr(newUser->fName, 49);

  //Asking last name
  move(2 * height/5 + 2, width/4 + strlen("Last name      (max. 49 characters): "));
  getnstr(newUser->lName, 49);

  //Asking mailing adress
  move(2 * height/5 + 3, width/4 + strlen("Mailing adress (max. 99 characters): "));
  getnstr(newUser->mailingAdress, 99);

  //Asking profession
  move(2 * height/5 + 4, width/4 + strlen("Profession     (max. 99 characters): "));
  getnstr(newUser->profession, 99);


  //Asking password
  password_field(2 * height/5 + 5, width/4 + strlen("Password       (max. 49 characters): "), newUser->password);


  /*#################################
  #                                 #
  #     Verifying informations      #
  #                                 #
  #################################*/

  //Clearing the screen
  clear();

  mvprintw(height/5, width/2 - (strlen("====== User Data =====")/2), "====== User Data =====");
  mvprintw(2 * height/5, width/4, "Email adress: ");
  printw(newUser->email);
  mvprintw(2 * height/5 + 1, width/4, "First name: ");
  printw(newUser->fName);
  mvprintw(2 * height/5 + 2, width/4, "Last name: ");
  printw(newUser->lName);
  mvprintw(2 * height/5 + 3, width/4, "Mailing adress: ");
  printw(newUser->mailingAdress);
  mvprintw(2 * height/5 + 4, width/4, "Profession: ");
  printw(newUser->profession);
  refresh();

  noecho();

  mvprintw(2 * height/5 + 6, width/3, "Is this correct ? (y/n) ");
  do {
    cPassword[0] = getch();
  } while(cPassword[0] != 'y' && cPassword[0] != 'Y' && cPassword[0] != 'n' && cPassword[0] != 'N');

  if (cPassword[0] == 'n' || cPassword[0] == 'N')
    return 0;

  newUser->groupID = 0; //Set user mode to client

  return 1;
}


void password_field(int yPos, int xPos, char* password)
{
  int i = 0, pressedKey;

  move(yPos, xPos);
  noecho();
  curs_set(1);

  while (i < 49 && pressedKey != 10) //While still typing the password
  {
    move(yPos, xPos++);
    pressedKey = getch();

    if (pressedKey == KEY_BACKSPACE && i > 0)
    {
      //Erasing the previous star
      mvprintw(yPos, --xPos, " ");
      i--;
      continue;
    }

    //If unvalid character
    if (pressedKey < 32 && pressedKey > 126)
      continue;

    printw("*");
    password[i++] = pressedKey;
  }

  password[i] = '\0';
}
