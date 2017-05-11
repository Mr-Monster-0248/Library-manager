#include "../headers/DB.h"
#include "../headers/UI_unix.h"
#include <curses.h>


void UI_init()
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


void UI_stop()
{
    endwin();
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
            mvprintw(yPos, xPos - 2, " ");
            xPos -= 2;
            i--;
            continue;
        }

        //If unvalid character
        if (pressedKey < 32 || pressedKey > 126)
        continue;

        if (pressedKey == 10) //If ENTER key pressed
        break;

        printw("*");
        password[i++] = pressedKey;
    }

    password[i] = '\0';
}


int new_user_form(User *newUser)
{
    int height, width;
    char c;


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
        remove_end_char(newUser->email, ' ');
    } while (strcmp(newUser->email, "") == 0); //While verify email function not implemented

    //Asking first name
    do
    {
        move(2 * height/5 + 1, width/4 + strlen("First name     (max. 49 characters): "));
        getnstr(newUser->fName, 49);
        remove_end_char(newUser->fName, ' ');
    } while (strcmp(newUser->fName, "") == 0);

    //Asking last name
    do
    {
        move(2 * height/5 + 2, width/4 + strlen("Last name      (max. 49 characters): "));
        getnstr(newUser->lName, 49);
        remove_end_char(newUser->lName, ' ');
    } while (strcmp(newUser->lName, "") == 0);

    //Asking mailing adress
    do
    {
        move(2 * height/5 + 3, width/4 + strlen("Mailing adress (max. 99 characters): "));
        getnstr(newUser->mailingAdress, 99);
        remove_end_char(newUser->mailingAdress, ' ');
    } while (strcmp(newUser->mailingAdress, "") == 0);

    //Asking profession
    do
    {
        move(2 * height/5 + 4, width/4 + strlen("Profession     (max. 99 characters): "));
        getnstr(newUser->profession, 99);
        remove_end_char(newUser->profession, ' ');
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
        c = getch();
    } while(c != 'y' && c != 'Y' && c != 'n' && c != 'N');

    if (c == 'n' || c == 'N')
    return 0;

    newUser->groupID = 0; //Set user mode to client
    newUser->numberBBooks = 0; //No books borrowed

    return 1;
}


int login(User* currentUser)
{
    int height, width, remainingAttempts = 3, userOK = 0;
    char* askedEmail = (char*) malloc(50 * sizeof(char));
    char* askedPassword = (char*) malloc(50 * sizeof(char));
    User myUser;

    getmaxyx(stdscr, height, width);

    //Building interface
    clear();
    mvprintw(height/5 - 7, (width - 22) / 2, "===== Login Page =====");
    mvprintw(height/5, width/5, "E-mail: ");
    mvprintw(height/5 + 5, width/5 - 2, "Password: ");
    refresh();

    echo();
    curs_set(1); //Setting cursor visible


    //Getting a valid e-mail adress
    do {
        mvprintw(height/5, width/5 + 8, "                                                  ");
        refresh();
        move(height/5, width/5 + 8);
        getnstr(askedEmail, 50);

        //Verifying if the email adress is stored in the database
        if(find_user(askedEmail, &myUser))
        {
            userOK = 1;
            break;
        }

        mvprintw(height/5 + 2, width/5 + 4, "Error: cannot find email \"%s\" in database, %d attempts remaining", askedEmail, --remainingAttempts);
    } while(remainingAttempts > 0);

    remainingAttempts = 3;

    FILE* logFile = fopen("log", "a");
    check_alloc(logFile);
    fprintf(logFile, "User loaded:\n\te-mail: \"%s\"\n\tpassword: \"%s\"\n", myUser.email, myUser.password);
    //fclose(logFile);

    clear();
    mvprintw(height/5 - 7, (width - 22) / 2, "===== Login Page =====");
    mvprintw(height/5, width/5, "E-mail: %s", askedEmail);
    mvprintw(height/5 + 5, width/5 - 2, "Password: ");
    refresh();


    //Asking password
    while(userOK == 1 && remainingAttempts > 0)
    {
        noecho();
        mvprintw(height/5 + 5, width/5 + 8, "                                                  ");
        refresh();
        password_field(height/5 + 5, width/5 + 8, askedPassword); //Asking the password

        fprintf(logFile, "\ttyped: \"%s\", must be \"%s\"\n", askedPassword, myUser.password);

        if (strcmp(askedPassword, myUser.password) == 0) //If password found
        {
            copy_User(currentUser, myUser);

            fprintf(logFile, "Password match!\n\n");
            fclose(logFile);

            return 1;
        }

        mvprintw(height/5 + 7, width/5, "Error: wrong password. %d attempts remaining", --remainingAttempts);
    }

    fprintf(logFile, "Wrong password 3 times\n\n");
    fclose(logFile);

    return 0;
}


void clear_screen()
{
    clear();
}

void display_book_info(Book myBook)
{
    curs_set(0);
    move(1,1);
    printw("\"%s\" by %s\n", myBook.title, myBook.author);
    printw("\tcode: %s, %d copie(s), with %d available(s)\n", myBook.code, myBook.copies, myBook.available);
}

void disp(char* string)
{
    printw("%s", string);
}

void display_user_info(User myUser)
{
    curs_set(0);
    move(1,1);
    printw("%s %s - %s\n", myUser.fName, myUser.lName, myUser.profession);
    printw("E-mail: %s\n", myUser.email);
    printw("Mailing adress: %s\"\n", myUser.mailingAdress);
}


char* ask_string_info(const char* message)
{
    char* info = (char*) malloc(50 * sizeof(char));

    check_alloc(info);

    while (1)
    {
        printw(message);
        refresh();
        echo();
        getnstr(info, 49);
        noecho();

        if (strcmp(info, ""))
            return info;

        clear_screen();
    }
}
