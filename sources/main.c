#include <stdio.h>
#include <stdlib.h>
#include "../headers/DB.h"
#include "../headers/auth.h"
#include "../headers/basic_functions.h"
#ifdef __WIN32__
#include "../headers/UI_windows.h"
#else
#include "../headers/UI_unix.h"
#endif

void command_line_arguments(int argc, char** argv);




int main(int argc, char** argv)
{
    int leave = 0;
    User myUser;

    command_line_arguments(argc, argv);

    UI_init();

    do
    {
        switch(login_menu())
        {
            case 0:
                if(!login(&myUser))
                    break;

                if (myUser.groupID == 1)
                {
                    admin_interface(myUser);
                    break;
                }

                do {
                    leave = 0;
                    switch (client_interface(myUser)) //pour le moment change ici pour test admin_interface PS. elle marche très bien
                    {
                        case 0:
                            system("echo Borrow book >> test.b");
                        break;

                        case 1:
                            system("echo return book >> test.b");
                        break;

                        case 2:
                            system("echo search a book >> test.b");
                        break;

                        case 3:
                            system("echo Modify password >> test.b");
                        break;

                        case 4:
                            system("echo delete account >> test.b");
                        break;

                        case 5:
                            leave = 1;
                        break;

                        default:
                            leave = 1;
                        break;
                    }
                } while(leave == 0);
            break;


            case 1:
                while(!ask_new_user_data(&myUser));
                store_user(myUser, USERS_DB_PATH);
                order__users_db();
            break;


            default:
                UI_stop();
                return EXIT_SUCCESS;
            break;
        }

        clear_screen();
    } while (1);

    return EXIT_SUCCESS;
}





void command_line_arguments(int argc, char** argv)
{
    if (argc == 1)
        return;

    if (argc >= 2)
    {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
        {
            printf("This program is a simple console software to manage a library with a user database and a book database\n");

            printf("\n\nAvailable command line arguments:\n");

            printf("\t\"-h\" or \"--help\" -> Display this help window\n");
            printf("\t\"-d filename\" or \"--decode filename\" -> Decode the database and print the result in the file filename\n\n");

            exit(EXIT_SUCCESS);
        }

        if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "--decode"))
        {
            if (argc < 3)
            {
                printf("ERROR: cannot decode: missing filename as command line argument\n");

                exit(EXIT_SUCCESS);
            }

            if (argc > 3)
            {
                printf("ERROR: too many command line arguments\n");

                exit(EXIT_SUCCESS);
            }

            decode_users_db(argv[2]);

            exit(EXIT_SUCCESS);
        }

        printf("ERROR: command line argument %s not recognized\n", argv[1]);
        exit(EXIT_SUCCESS);
    }
}
