#include "../headers/UI_windows.h"


int login(User* currentUser)
{
    int remainingAttempts = 3, userOK = 0;
    char *askedEmail = (char*) malloc(50 * sizeof(char)), *askedPassword = (char*) malloc(50 * sizeof(char));
    User myUser;

    check_alloc(askedEmail);
    check_alloc(askedPassword);

    printf("\n\n\n\t\t===== Login Page =====\n");

    do {
        fflush(stdin);
        printf("E-mail: ");
        fgets(askedEmail, 49, stdin);

        if (find_user(askedEmail, &myUser))
        {
            userOK = 1;
            break;
        }

        printf("Error: cannot find user \"%s\" in database\n", askedEmail);
    } while(!userOK && remainingAttempts > 0);

    free(askedEmail);

    if (remainingAttempts == 0)
    return 0;

    remainingAttempts = 3;

    do {
        fflush(stdin);
        printf("Password: ");
        fgets(askedPassword, 49, stdin);

        if (check_password(askedPassword, myUser.password))
        {
            copy_User(currentUser, myUser);
            free(askedPassword);
            return 1;
        }

        if (!userOK)
        printf("Error: wrong password, %d attempts remaining\n", --remainingAttempts);
    } while (remainingAttempts > 0);

    return 0;
}


int login_menu()
{
    int choice = 0;

    do {
        clear_screen();
        printf("\n\n\n\t1. Create new account\n\t2. Login (existing account)\n\t3. Exit the program\n\n\n");
        printf("Your choice (numeric value): ");
        if (scanf("%d", &choice) == 1)
        {
            fflush(stdin);
            if (choice >= 1 && choice <= 3)
            return choice;
        }
        fflush(stdin);
    } while(1);
}


void UI_init()
{
    //This function has actually no interest for windows, but is needed for the program to compile
}


void UI_stop()
{
    //This function has actually no interest for windows, but is needed for the program to compile
}


int take_choice(int a)
{
    int res;
    printf("Your choice: ");
    do {
        scanf("%d", &res);
    } while(res < 1 || res > a);

    return res - 1;
}


void password_field(int yPos, int xPos, char* password)
{
    //This function has an interest only using curses.h with UNIX system
    fflush(stdin);
    fgets(password, 49, stdin);
}


int new_user_form(User *newUser, const int* isAdmin)
{
    char c;

    fflush(stdin);

    strcpy(newUser->email, "defaultemail");

    //Asking E-mail adress
    do {
        CLEAR_SCREEN();
        if (verif_if_existing_user(newUser->email))
            printf("\nThis email is already used by someone!\n");

        if (check_if_email(newUser->email))
            printf("ERROR: \"%s\" cannot be considered an email adress\n", newUser->email);

        printf("\n\n\t\tEnter your E-mail adress: ");
        fgets(newUser->email, 69, stdin);
        fflush(stdin);
    } while(!strcmp(newUser->email, "") || !check_if_email(newUser->email) || verif_if_existing_user(newUser->email));

    //Asking first name
    do {
        CLEAR_SCREEN();
        printf("\n\n\t\tEnter your first name: ");
        fgets(newUser->fName, 49, stdin);
        fflush(stdin);
    } while(strcmp(newUser->fName, "") == 0);

    //Asking last name
    do {
        CLEAR_SCREEN();
        printf("\n\n\t\tEnter your last name: ");
        fgets(newUser->lName, 49, stdin);
        fflush(stdin);
    } while(strcmp(newUser->lName, "") == 0);

    //Asking mailing adress
    do {
        CLEAR_SCREEN();
        printf("\n\n\t\tEnter your mailing adress: ");
        fgets(newUser->mailingAdress, 99, stdin);
        fflush(stdin);
    } while(strcmp(newUser->mailingAdress, "") == 0);

    //Asking profession
    do {
        CLEAR_SCREEN();
        printf("\n\n\t\tYour profession: ");
        fgets(newUser->profession, 99, stdin);
        fflush(stdin);
    } while(strcmp(newUser->profession, "") == 0);

    CLEAR_SCREEN();
    printf("\n\n\t\tPlease set a password: ");
    password_field(1, 1, newUser->password);

    CLEAR_SCREEN();
    printf("\n\n\t\t===== User Data =====\n\n");
    printf("\tE-mail:\t\t%s\n", newUser->email);
    printf("\tFirst name:\t\t\"%s\"\n", newUser->fName);
    printf("\tLast Name:\t\t\"%s\"\n", newUser->lName);
    printf("\tMailing adress:\t\t\"%s\"\n", newUser->mailingAdress);
    printf("\tProfession:\t\t\"%s\"\n", newUser->profession);

    printf("\nIs this correct ? (y/n) ");
    fflush(stdin);
    do
    {
        c = getchar();
        fflush(stdin);
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');

    if (c == 'n' || c == 'N')
    return 0;

    newUser->groupID = isAdmin;
    newUser->numberBBooks = 0;

    return 1;
}


void clear_screen()
{
    CLEAR_SCREEN();
}


void display_book_info(Book myBook)
{
    printf("\"%s\" by %s\n", myBook.title, myBook.author);
    printf("\tcode: %s, %d copie(s), with %d available(s)\n", myBook.code, myBook.copies, myBook.available);
}


void disp(char* string)
{
    printf("%s", string);
}


void disp_int(const int integer)
{
    printf("%d", integer);
}


void display_user_info(User myUser)
{
    printf("%s %s - %s\n", myUser.fName, myUser.lName, myUser.profession);
    printf("E-mail: %s\n", myUser.email);
    printf("Mailing adress: %s\"\n", myUser.mailingAdress);
}


char* ask_string_info(const char* message)
{
    char* info = (char*) malloc(50 * sizeof(char));

    check_alloc(info);

    while (1)
    {
        fflush(stdin);
        printf(message);
        fgets(info, 50, stdin);

        if (strcmp(info, ""))
            return info;

        clear_screen();
    }
}


int client_interface(User myUser)
{
    int i = 0;
    Book borrowedBooks;
    Date currentDate = current_date();

    clear_screen();
    printf("\t\t===== %s %s =====\n", myUser.fName, myUser.lName);
    printf("\t\t%2d/%2d/%4d\n\n", currentDate.month, currentDate.day, currentDate.year);
    if(myUser.numberBBooks == 0)
    {
        printf("You have no borroed books\n\n");
    }
    else
    {
        for(i = 0; i < myUser.numberBBooks; i++)
        {
            borrowedBooks = get_book_by_code(myUser.borrowedBooks[i]);

            if(compare_dates(myUser.returnDates[i], currentDate) == 2)
            {
                printf("%s by %s (%s)\n", borrowedBooks.title, borrowedBooks.author, borrowedBooks.code);
            }
            else
            {
                printf("%s by %s (%s)\n", borrowedBooks.title, borrowedBooks.author, borrowedBooks.code);
            }
        }
    }
    printf("1. Borrow a book\n");
    printf("2. Return a book\n");
    printf("3. Search a book\n");
    printf("4. Modify password\n");
    printf("5. Delete my account\n");
    printf("6. Logout\n");

    return take_choice(6);
}


int admin_interface(User myUser)
{
    Date currentDate = current_date();

    clear_screen();
    printf("\t\t===== %s %s =====\n", myUser.fName, myUser.lName);
    printf("\t\t%2d/%2d/%4d\n\n", currentDate.month, currentDate.day, currentDate.year);

    printf("1. Display books\n");
    printf("2. Display User\n");
    printf("3. Add Admin\n");
    printf("4. Modify password\n");
    printf("5. Delete my account\n");
    printf("6. Logout\n");

    return take_choice(6);
}


void admin_display_book()
{
    clear_screen();
    printf("1. Display all DB");
    printf("2. Display by genre (genre code)");
    printf("3. Display by autor");
    printf("4. Display by genre");

    switch (take_choice(4))
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
    clear_screen();
    printf("1. Display all DB (alphabetical order)");
    printf("2. Search user by name");
    printf("3. Search user by email");
    printf("4. Search user by profession");

    switch (take_choice(4))
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
    clear_screen();
    printf("1. Existing account");
    printf("2. New account");

    return take_choice(2);
}


int client_search_book()
{
    clear_screen();
    printf("1. Display all books");
    printf("2. Search book by title");
    printf("3. Search book by author");
    printf("4. Search book by code");

    return take_choice(4);
}


char* get_genre()
{
    char* genre = (char*) malloc(4 * sizeof(char));
    int height, width;

    getmaxyx(stdscr, height, width);

    clear_screen();

    check_alloc(genre);


    printf("1. Biography - BIO");
    printf("2. Novel - NVL");
    printf("3. Comic - CMC");
    printf("4. Documentation - DOC");
    printf("5. Manga - MAN");
    printf("6. Kids - KID");
    printf("7. Theatre - THR");
    printf("8. Horror - HOR");
    printf("9. Adult - ADT");

    switch(take_choice(9))
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

    clear_screen();

    printf("\n\n\n\t\tAre you sure you want to delete your account ? (y/n)\n");

    fflush(stdin);
    while (c != 'y' && c != 'Y' && c != 'n' && c != 'N')
    {
        c = getchar();
        fflush(stdin);
    }

    if (c == 'n' || c == 'N')
        return;

    if (myUser.numberBBooks == 0) //Deleting the account only if the user has no currently borrowed books
        delete_account(myUser);
    else
        printf("ERROR: cannot delete this account, it has unreturned books\n");
}
