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
    User myUser;

    UI_init();

    do
    {
        switch(login_menu())
        {
            case 0:
            login(&myUser);
            break;

            case 1:
            while(!ask_new_user_data(&myUser));
            store_user(myUser);
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
