#include "../headers/auth.h"


int check_password(char* toCheck, char* password)
{
    //If password is good
    if (!strcmp(toCheck, password))
    return 1;

    //If password is false
    return 0;
}


int ask_new_user_data(User *newUser)
{
    return new_user_form(newUser);
}


int find_user(char* emailToFind, User* getUser)
{
    FILE* user_db = fopen(USERS_DB_PATH, "r");
    User currentUser;

    check_alloc(user_db);

    system("touch ta_chatte");

    //Exploring the database
    do {
        system("echo debut__d_exploration >> ta_chatte");
        currentUser = load_next_user(user_db);
        system("echo fin__d_exploration >> ta_chatte");
    } while(!feof(user_db) && strcmp(currentUser.email, emailToFind) != 0);

    system("echo caca >> ta_chatte");

    fclose(user_db);

    //If user not found
    if (strcmp(currentUser.email, emailToFind) != 0)
    {
        fopen("balise de bite 1", "w");
        return 0;
    }

    copy_User(getUser, currentUser);

    fopen("balise de bite 2", "w");

    return 1;
}
