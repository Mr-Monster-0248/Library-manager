#include "../headers/auth.h"


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
  do
  {
    mvprintw(2 * height/5, width/4 + strlen("Email adress    (max.69 characters): "), "                                                                 ");
    move(2 * height/5, width/4 + strlen("Email adress    (max.69 characters): "));
    refresh();
    getnstr(newUser->email, 69);
  } while (strcmp(newUser->email, "") == 0); //While verify email function not implemented

  //Asking first name
  do
  {
    move(2 * height/5 + 1, width/4 + strlen("First name     (max. 49 characters): "));
    getnstr(newUser->fName, 49);
  } while (strcmp(newUser->fName, "") == 0);

  //Asking last name
  do
  {
    move(2 * height/5 + 2, width/4 + strlen("Last name      (max. 49 characters): "));
    getnstr(newUser->lName, 49);
  } while (strcmp(newUser->lName, "") == 0);

  //Asking mailing adress
  do
  {
    move(2 * height/5 + 3, width/4 + strlen("Mailing adress (max. 99 characters): "));
    getnstr(newUser->mailingAdress, 99);
  } while (strcmp(newUser->mailingAdress, "") == 0);

  //Asking profession
  do
  {
    move(2 * height/5 + 4, width/4 + strlen("Profession     (max. 99 characters): "));
    getnstr(newUser->profession, 99);
  } while (strcmp(newUser->profession, "") == 0);


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
  newUser->numberBBooks = 0; //No books borrowed

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

    if (pressedKey == 8 && i > 0)
    {
      //Erasing the previous star
      mvprintw(yPos, --xPos, " ");
      i--;
      continue;
    }

    //If unvalid character
    if (pressedKey < 32 && pressedKey > 126)
      continue;

    if (pressedKey == 10) //If ENTER key pressed
      break;

    printw("*");
    password[i++] = pressedKey;
  }

  password[i] = '\0';
}


int find_user(char* emailToFind, User* getUser)
{
  FILE* user_db = fopen(USERS_DB_PATH, "r");
  int i = 0;
  User currentUser;

  check_alloc(user_db);

  //Exploring the database
  do {
    currentUser = load_next_user(user_db);
  } while(!feof(user_db) && strcmp(currentUser.email, emailToFind) != 0);

  fclose(user_db);

  //If user not found
  if (strcmp(currentUser.email, emailToFind) != 0)
    return 0;

  //If user found
  strcpy(getUser->email, currentUser.email);
  strcpy(getUser->password, currentUser.password);
  strcpy(getUser->fName, currentUser.fName);
  strcpy(getUser->lName, currentUser.lName);
  strcpy(getUser->profession, currentUser.profession);
  strcpy(getUser->mailingAdress, currentUser.mailingAdress);
  getUser->groupID = currentUser.groupID;
  getUser->numberBBooks = currentUser.numberBBooks;

  for (i = 0; i < currentUser.numberBBooks; i++)
    strcpy(getUser->borrowedBooks[i], currentUser.borrowedBooks[i]);


  return 1;
}


int login()
{
  int height, width;
  char* askedEmail = (char*) malloc(80 * sizeof(int));

  clear();
  mvprintw()


  return 1;
}
