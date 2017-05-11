#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/crypting.h"
#include "headers/DB.h"
#include "headers/basic_functions.h"

#define DECODED_USERS_PATH ".databases/decoded_users.db"


int main(int argc, char** argv)
{
    User myUser;
    FILE *users_db = fopen(USERS_DB_PATH, "r");
    FILE *decoded_db = fopen(DECODED_USERS_PATH, "w");

    check_alloc(users_db);
    check_alloc(decoded_db);

    if (argc >= 2)
    {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
        {
            printf("This program decodes the users database located in the .databases folder, and prints what it read inside the file decoded_users.db\n");
            printf("This program does not require any command line argument to work\n\n");
        }

        exit(EXIT_SUCCESS);
    }


    while (!feof(users_db))
    {
        myUser = load_next_user(users_db);

        fprintf(decoded_db, "User: %s %s ", myUser.fName, myUser.lName);
        if (myUser.groupID == 1)
            fprintf(decoded_db, "(Admin)");
        fprintf(decoded_db, "\n\tgroupID:\t\t%d\n", myUser.groupID);
        fprintf(decoded_db, "\te-mail:\t\t\t%s\n", myUser.email);
        fprintf(decoded_db, "\tpassword:\t\t%s\n", myUser.password);
        fprintf(decoded_db, "\tprofession:\t\t%s\n", myUser.profession);
        fprintf(decoded_db, "\tmailing adress:\t%s\n\n", myUser.mailingAdress);
    }

    fclose(users_db);
    fclose(decoded_db);

    printf("Dabase successfully decoded!\n\n");

    return EXIT_SUCCESS;
}
