#include "../headers/DB.h"
#include "../headers/UI_unix.h"
#include "../headers/dates.h"
#include <curses.h>
#include <time.h>


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


int new_user_form(User *newUser, const int isAdmin)
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
    mvprintw(2 * height/5, width/4, "Email adress   (max. 69 characters): ");
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



        mvprintw(2 * height/5 + 2, width/4, "                                                  ");

        if (check_if_email(newUser->email))
        {
            mvprintw(2 * height/5 + 2, width/4, "ERROR: \"%s\" cannot be considered an email adress", newUser->email);
            continue;
        }


        if (verif_if_existing_user(newUser->email))
        {
            mvprintw(2 * height/5 + 2, width/4, "This email is already used by someone!");
        }
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

    newUser->groupID = isAdmin; //Set user mode to client
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


        if (strcmp(askedPassword, myUser.password) == 0) //If password found
        {
            copy_User(currentUser, myUser);

            return 1;
        }

        mvprintw(height/5 + 7, width/5, "Error: wrong password. %d attempts remaining", --remainingAttempts);
    }

    return 0;
}


void clear_screen()
{
    clear();
    refresh();
}


void press_any_key()
{
    int height, width;
    getmaxyx(stdscr, height, width);

    move(height / 2, width*3/4);
    disp("Press any key to continue...");
    getch();
}


void display_book_info(Book myBook)
{
    curs_set(0);
    printw("\"%s\" by %s\n", myBook.title, myBook.author);
    printw("\tcode: %s, %d copie(s), with %d available(s)\n\n", myBook.code, myBook.copies, myBook.available);
}


void disp(char* string)
{
    printw("%s", string);
}


void disp_int(const int integer)
{
    printw("%d", integer);
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


int client_interface(User myUser)
{
    curs_set(0);
    int height, width, i = 0;
    Book borrowedBooks;
    Date currentDate = current_date();
    getmaxyx(stdscr, height, width);

    clear();
    mvprintw(height / 5, (width - (strlen(myUser.fName) + strlen(myUser.lName)) - 13) / 2, "===== %s %s =====", myUser.fName, myUser.lName);
    mvprintw(height / 5 + 1, (width - 10) / 2, "%2d/%2d/%4d", currentDate.month, currentDate.day, currentDate.year);
    if(myUser.numberBBooks == 0)
    {
        mvprintw(height / 5 + 4, (width - 40) / 2, "You have no borroed books");
    }
    else
    {
        for(i = 0; i < myUser.numberBBooks; i++)
        {
            borrowedBooks = get_book_by_code(myUser.borrowedBooks[i]);

            if(compare_dates(myUser.returnDates[i], currentDate) == 2)
            {
                //add red color
                mvprintw(height / 5 + 4 + i, width / 5, "%s by %s (%s)", borrowedBooks.title, borrowedBooks.author, borrowedBooks.code);
            }
            else
            {
                mvprintw(height / 5 + 4 + i, width / 5, "%s by %s (%s)", borrowedBooks.title, borrowedBooks.author, borrowedBooks.code);
            }
        }
    }
    mvprintw(height / 5 + 6 + i, width / 5, "Borrow a book");
    mvprintw(height / 5 + 7 + i, width / 5, "Return a book");
    mvprintw(height / 5 + 8 + i, width / 5, "Search a book");
    mvprintw(height / 5 + 9 + i, width / 5, "Modify password");
    mvprintw(height / 5 + 10 + i, width / 5, "Delete my account");
    mvprintw(height / 5 + 11 + i, width / 5, "Logout");

    refresh();

    return move_arrow(width / 5 - 2, height/5 + 6 + i, height/5 + 11 + i);
}


int admin_interface(User myUser)
{
    curs_set(0);
    int height, width;
    Date currentDate = current_date();
    getmaxyx(stdscr, height, width);

    clear();
    mvprintw(height / 5, (width - (strlen(myUser.fName) + strlen(myUser.lName)) - 13) / 2, "===== %s %s =====", myUser.fName, myUser.lName);
    mvprintw(height / 5 + 1, (width - 10) / 2, "%2d/%2d/%4d", currentDate.month, currentDate.day, currentDate.year);
    mvprintw(height / 5 + 6, width / 5, "Display books");
    mvprintw(height / 5 + 7, width / 5, "Display Users");
    mvprintw(height / 5 + 8, width / 5, "Add Admin");
    mvprintw(height / 5 + 9, width / 5, "Modify password");
    mvprintw(height / 5 + 10, width / 5, "Delete my account");
    mvprintw(height / 5 + 11, width / 5, "Logout");

    refresh();

    return move_arrow(width / 5 - 2, height/5 + 6, height/5 + 11);
}


void admin_display_book()
{
    curs_set(0);
    int height, width;
    getmaxyx(stdscr, height, width);

    clear();
    mvprintw(height / 5, width / 5, "Display all DB");
    mvprintw(height / 5 + 1, width / 5, "Display by genre (genre code)");
    mvprintw(height / 5 + 2, width / 5, "Display by autor");
    mvprintw(height / 5 + 3, width / 5, "Display by genre");

    refresh();

    switch (move_arrow(width / 5 - 2, height/5, height/5 + 3))
    {
        case 0:
            display_book_db();
            press_any_key();
        break;
        case 1:
            clear_screen();
            display_book_by_code();
            press_any_key();
        break;
        case 2:
            clear_screen();
            display_books_by_author();
            press_any_key();
        break;
        case 3:
            clear_screen();
            display_books_by_title();
            press_any_key();
        break;
        default:
        break;
    }
}


void admin_display_user()
{
    curs_set(0);
    int height, width;
    getmaxyx(stdscr, height, width);

    clear();
    mvprintw(height / 5, width / 5, "Display all DB (alphabetical order)");
    mvprintw(height / 5 + 1, width / 5, "Search user by name");
    mvprintw(height / 5 + 2, width / 5, "Search user by email");
    mvprintw(height / 5 + 3, width / 5, "Search user by profession");

    refresh();

    switch (move_arrow(width / 5 - 2, height/5, height/5 + 3))
    {
        case 0:
            display_all_users();
            press_any_key();
        break;
        case 1:
            clear_screen();
            search_user_by_name();
            press_any_key();
        break;
        case 2:
            clear_screen();
            search_user_by_email();
            press_any_key();
        break;
        case 3:
        break;
        default:
        break;
    }
}


int admin_add_admin()
{
    curs_set(0);
    int height, width;
    getmaxyx(stdscr, height, width);

    clear();
    mvprintw(height / 5, width / 5, "Existing account");
    mvprintw(height / 5 + 1, width / 5, "New account");

    refresh();

    return move_arrow(width / 5 - 2, height/5, height/5 + 1);
}


int client_search_book()
{
    curs_set(0);
    int height, width;
    getmaxyx(stdscr, height, width);

    clear();
    mvprintw(height / 5, width / 5, "Display all books");
    mvprintw(height / 5 + 1, width / 5, "Search book by title");
    mvprintw(height / 5 + 2, width / 5, "Search book by author");
    mvprintw(height / 5 + 3, width / 5, "Search book by code");

    refresh();
    return move_arrow(width / 5 - 2, height/5, height/5 + 3);
}


char* get_genre()
{
    char* genre = (char*) malloc(4 * sizeof(char));
    int height, width;

    getmaxyx(stdscr, height, width);

    clear_screen();


    check_alloc(genre);


    mvprintw(height/4, width/4, "Biography - BIO");
    mvprintw(height/4 + 1, width/4, "Novel - NVL");
    mvprintw(height/4 + 2, width/4, "Comic - CMC");
    mvprintw(height/4 + 3, width/4, "Documentation - DOC");
    mvprintw(height/4 + 4, width/4, "Manga - MAN");
    mvprintw(height/4 + 5, width/4, "Kids - KID");
    mvprintw(height/4 + 6, width/4, "Theatre - THR");
    mvprintw(height/4 + 7, width/4, "Horror - HOR");
    mvprintw(height/4 + 8, width/4, "Adult - ADT");

    refresh();

    switch(move_arrow(width/4 - 2, height/4, height/4 + 8))
    {
        case 0:
            strcpy(genre, "BIO");
        break;

        case 1:
            strcpy(genre, "NVL");
        break;

        case 2:
            strcpy(genre, "CMC");
        break;

        case 3:
            strcpy(genre, "DOC");
        break;

        case 4:
            strcpy(genre, "MAN");
        break;

        case 5:
            strcpy(genre, "KID");
        break;

        case 6:
            strcpy(genre, "THR");
        break;

        case 7:
            strcpy(genre, "HOR");
        break;

        case 8:
            strcpy(genre, "ADT");
        break;

        default:
        break;
    }

    return genre;
}


void interface_delete_account(User myUser)
{
    char c = 'a';
    int height, width;

    getmaxyx(stdscr, height, width);

    clear_screen();

    mvprintw(height/2, (width - strlen("Are you sure you want to delete your account ? (y/n)"))/2, "Are you sure you want to delete your account ? (y/n)");

    noecho();
    while (c != 'y' && c != 'Y' && c != 'n' && c != 'N')
        c = getch();

    if (c == 'n' || c == 'N')
        return;

    if (myUser.numberBBooks == 0) //Deleting the account only if the user has no currently borrowed books
        delete_account(myUser);
    else
        mvprintw(height/2, (width/2 - strlen("ERROR: cannot delete this account, it has unreturned books"))/2, "ERROR: cannot delete this account, it has unreturned books");
}
