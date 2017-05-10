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
        CLEAR_SCREEN();
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

void password_field(int yPos, int xPos, char* password)
{
    //This function has an interest only using curses.h with UNIX system
    fflush(stdin);
    fgets(password, 49, stdin);
}

int new_user_form(User *newUser)
{
    char c;

    fflush(stdin);

    //Asking E-mail adress
    do {
        CLEAR_SCREEN();
        printf("\n\n\t\tEnter your E-mail adress: ");
        fgets(newUser->email, 69, stdin);
        fflush(stdin);
    } while(strcmp(newUser->email, "") == 0);

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

    newUser->groupID = 0;
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
