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
    return new_user_form(newUser, 0);
}


int find_user(char* emailToFind, User* getUser)
{
    FILE* user_db = fopen(USERS_DB_PATH, "r");
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

    copy_User(getUser, currentUser);

    return 1;
}
