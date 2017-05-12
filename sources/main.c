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



int main(int argc, char** argv)
{
    int leave = 0;
    User myUser;

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
                //order database (alphabetical order)
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
