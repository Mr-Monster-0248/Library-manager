#include "../headers/DB.h"
#ifdef __WIN32__
#include "../headers/UI_windows.h"
#else
#include "../headers/UI_unix.h"
#endif


void store_user(User newUser, const char* db_path)
{
    int i = 0;
    int *cryptedEmail = NULL, *cryptedPassword = NULL, *cryptedFName = NULL, *cryptedLName = NULL, *cryptedProfession = NULL, *cryptedMAdress = NULL, *cryptedCode = NULL;
    FILE* users_db = fopen(db_path, "a");

    check_alloc(users_db); //Checking file opening

    //Crypting data
    cryptedEmail = encrypt_to_int(newUser.email);
    cryptedPassword = encrypt_to_int(newUser.password);
    cryptedFName = encrypt_to_int(newUser.fName);
    cryptedLName = encrypt_to_int(newUser.lName);
    cryptedProfession = encrypt_to_int(newUser.profession);
    cryptedMAdress = encrypt_to_int(newUser.mailingAdress);

    //Hidding groupID in crypted password (crypting it at the end of crypted password)
    cryptedPassword = realloc(cryptedPassword, (strlen(newUser.password) + 1) * sizeof(int));
    check_alloc(cryptedPassword);
    cryptedPassword[strlen(newUser.password)] = newUser.groupID + strlen(newUser.password) + 1;


    //Writing data in the database
    fprintf(users_db, "\n");
    write_integers_array(users_db, cryptedEmail, strlen(newUser.email));
    write_integers_array(users_db, cryptedPassword, strlen(newUser.password) + 1);
    write_integers_array(users_db, cryptedFName, strlen(newUser.fName));
    write_integers_array(users_db, cryptedLName, strlen(newUser.lName));
    write_integers_array(users_db, cryptedProfession, strlen(newUser.profession));
    write_integers_array(users_db, cryptedMAdress, strlen(newUser.mailingAdress));

    fprintf(users_db, "%d", newUser.numberBBooks);

    //Writing books codes
    for (i = 0; i < newUser.numberBBooks; i++)
    {
        cryptedCode = encrypt_to_int(newUser.borrowedBooks[i]);
        write_integers_array(users_db, cryptedCode, strlen(newUser.borrowedBooks[i]));
        free(cryptedCode);

        /*
            TODO: encrypt & write return dates of borrowed books
        */
    }

    fprintf(users_db, "\n");

    //Freeing arrays
    free(cryptedEmail);
    free(cryptedPassword);
    free(cryptedFName);
    free(cryptedLName);
    free(cryptedProfession);
    free(cryptedMAdress);
    fclose(users_db);
}


void write_integers_array(FILE* file, int* array, const int numberElements)
{
    int i = 0;

    check_alloc(file);

    for (i = 0; i < numberElements - 1; i++)
    fprintf(file, "%d ", array[i]);
    fprintf(file, "%d 1\n", array[i]); //End of line
}


char* read_line(FILE* file)
{
    int i = 0;
    char readChar;
    char* line = (char*) malloc(2 * sizeof(char));
    check_alloc(line);

    while(!feof(file))
    {
        readChar = fgetc(file);

        if (readChar == '\n' || feof(file))
            break;

        line = (char*) realloc(line, (i + 2) * sizeof(char));
        check_alloc(line);

        line[i++] = readChar;
    }

    line[i] = '\0'; //To end the string

    return line;
}


void copy_to_line(char* path_toCopy, char* path_newFile, const int stopLine)
{
    int i = 0;
    char* line = NULL;

    FILE* file1 = fopen(path_toCopy, "r");
    FILE* file2 = fopen(path_newFile, "w");
    check_alloc(file1);
    check_alloc(file2);


    for (i = 0; i < stopLine && !feof(file1); i++)
    {
        line = read_line(file1);
        fprintf(file2, "%s\n", line);
        free(line);
    }

    fclose(file1);
    fclose(file2);
}


User load_next_user(FILE* user_db)
{
    User myUser;
    int *cryptedEmail = NULL, *cryptedPassword = NULL, *cryptedFName = NULL, *cryptedLName = NULL, *cryptedProfession = NULL, *cryptedMAdress = NULL, *cryptedCode = NULL;
    char *dEmail = NULL, *dPassword = NULL, *dFName = NULL, *dLName = NULL, *dProfession = NULL, *dMAdress = NULL, *dCode = NULL;
    int numberBooks = 0, i = 0, numberChars = 0;

    //TEMPORARY (waiting for struct Date)
    int day = 0, month = 0, year = 0;

    check_alloc(user_db);

    if (feof(user_db))
        return myUser;

    /*#################################
    #                                 #
    #     Reading and decrypting      #
    #                                 #
    #################################*/

    //email
    cryptedEmail = return_int_line(user_db, &numberChars);
    dEmail = decrypt_to_string(cryptedEmail, numberChars);

    //password
    cryptedPassword = return_int_line(user_db, &numberChars);
    dPassword = decrypt_to_string(cryptedPassword, numberChars - 1);

    //first name
    cryptedFName = return_int_line(user_db, &numberChars);
    dFName = decrypt_to_string(cryptedFName, numberChars);

    //last name
    cryptedLName = return_int_line(user_db, &numberChars);
    dLName = decrypt_to_string(cryptedLName, numberChars);

    //profession
    cryptedProfession = return_int_line(user_db, &numberChars);
    dProfession = decrypt_to_string(cryptedProfession, numberChars);

    //mailing adress
    cryptedMAdress = return_int_line(user_db, &numberChars);
    dMAdress = decrypt_to_string(cryptedMAdress, numberChars);

    //number of borrowed books
    fscanf(user_db, "%d", &numberBooks);

    for (i = 0; i < numberBooks; i++)
    {
        //Obtaining the crypted book code and decrypting it
        cryptedCode = return_int_line(user_db, &numberChars);
        dCode = decrypt_to_string(cryptedCode, numberChars);
        fscanf(user_db, "%d %d %d %*d", &day, &month, &year);

        strcpy(myUser.borrowedBooks[i], dCode);

        free(cryptedCode);
        free(dCode);
    }

    fgetc(user_db);
    fgetc(user_db);

    //Storing read data in structure User
    strcpy(myUser.email, dEmail);
    strcpy(myUser.password, dPassword);
    strcpy(myUser.fName, dFName);
    strcpy(myUser.lName, dLName);
    strcpy(myUser.profession, dProfession);
    strcpy(myUser.mailingAdress, dMAdress);
    myUser.numberBBooks = numberBooks;
    myUser.groupID = cryptedPassword[strlen(dPassword)] - strlen(dPassword) - 1;


    //Freeing strings and arrays
    free(cryptedEmail);
    free(cryptedPassword);
    free(cryptedFName);
    free(cryptedLName);
    free(cryptedProfession);
    free(cryptedMAdress);
    free(dEmail);
    free(dPassword);
    free(dFName);
    free(dLName);
    free(dProfession);
    free(dMAdress);

    return myUser;
}


int* return_int_line(FILE* user_db, int* numberChars)
{
    int i = 0, read = 0;
    int* line = (int*) malloc(sizeof(int));

    while (1)
    {
        fscanf(user_db, "%d", &read);

        if (read == 1)
            break;

        line = realloc(line, (i+1) * sizeof(int));
        line[i++] = read;
    }

    *numberChars = i;

    return line;
}


void copy_User(User* to, User from)
{
    int i = 0;

    strcpy(to->email, from.email);
    strcpy(to->password, from.password);
    strcpy(to->fName, from.fName);
    strcpy(to->lName, from.lName);
    strcpy(to->profession, from.profession);
    strcpy(to->mailingAdress, from.mailingAdress);
    to->numberBBooks = from.numberBBooks;
    to->groupID = from.groupID;

    for (i = 0; i < from.numberBBooks; i++)
    strcpy(to->borrowedBooks[i], from.borrowedBooks[i]);
}


Book load_next_book(FILE* books_db)
{
    Book myBook;

    strcpy(myBook.title, read_line(books_db));
    strcpy(myBook.author, read_line(books_db));
    strcpy(myBook.code, read_line(books_db));
    fscanf(books_db, "%d", &(myBook.copies));
    fscanf(books_db, "%d", &(myBook.available));
    fgetc(books_db); //To read the empty line
    fgetc(books_db); //To read the other empty line

    return myBook;
}


void display_book_db()
{
    FILE* books_db = fopen(BOOKS_DB_PATH, "r");
    check_alloc(books_db);

    clear_screen();

    while (!feof(books_db))
        display_book_info(load_next_book(books_db));

    fclose(books_db);
}


void display_available_books()
{
    Book currentBook;
    FILE* books_db = fopen(BOOKS_DB_PATH, "r");
    check_alloc(books_db);

    while (!feof(books_db))
    {
        currentBook = load_next_book(books_db);

        if (currentBook.available > 0)
            display_book_info(currentBook);
    }

    fclose(books_db);
}


void display_books_by_author()
{
    char* authorName = ask_string_info("Please type the author's name: "); //Function to implement
    Book currentBook;
    FILE* books_db = fopen(BOOKS_DB_PATH, "r");
    check_alloc(books_db);

    while (!feof(books_db))
    {
        currentBook = load_next_book(books_db);

        if (strcmp(currentBook.author, authorName) == 0) //If book author matches with asked author
            display_book_info(currentBook);
    }

    fclose(books_db);
    free(authorName);
}


void display_books_by_title()
{
    char* bookTitle = ask_string_info("Please type the book's title: ");
    Book currentBook;
    FILE* books_db = fopen(BOOKS_DB_PATH, "r");
    check_alloc(books_db);

    while (!feof(books_db))
    {
        currentBook = load_next_book(books_db);

        if (strcmp(currentBook.title, bookTitle) == 0) //If current book's title matches with the one asked
            display_book_info(currentBook);
    }

    fclose(books_db);
    free(bookTitle);
}


void display_book_by_code()
{
    char* bookCode = ask_string_info("Please type the code of the book (XXX-YYY): ");
    Book currentBook;
    FILE* books_db = fopen(BOOKS_DB_PATH, "r");
    check_alloc(books_db);

    while (!feof(books_db))
    {
        currentBook = load_next_book(books_db);

        if (strcmp(currentBook.code, bookCode) == 0)
        {
            display_book_info(currentBook);
            free(bookCode);
            fclose(books_db);

            return;
        }
    }

    disp("No books found for code \"");
    disp(bookCode);
    disp("\"\n");

    fclose(books_db);
    free(bookCode);
}


void search_user_by_name()
{
    char *firstName = ask_string_info("Enter first name: "), *lastName = ask_string_info("Enter last name: ");
    FILE* users_db = fopen(USERS_DB_PATH, "r");
    User currentUser;

    check_alloc(users_db);

    while (!feof(users_db))
    {
        currentUser = load_next_user(users_db);

        if (!strcmp(currentUser.fName, firstName) && !strcmp(currentUser.lName, lastName))
        {
            display_user_info(currentUser);

            free(firstName);
            free(lastName);
            fclose(users_db);
            return;
        }
    }

    disp("User ");
    disp(firstName);
    disp(" ");
    disp(lastName);
    disp(" not found in database\n");

    free(firstName);
    free(lastName);
    fclose(users_db);
}


void search_user_by_email()
{
    char* eMail = ask_string_info("Enter user's e-mail: ");
    FILE* users_db = fopen(USERS_DB_PATH, "r");
    User currentUser;

    check_alloc(users_db);

    while (!feof(users_db))
    {
        currentUser = load_next_user(users_db);

        if (!strcmp(currentUser.email, eMail))
        {
            display_user_info(currentUser);

            free(eMail);
            fclose(users_db);

            return;
        }
    }

    disp("Cannot find user with e-mail ");
    disp(eMail);
    disp("\n");

    fclose(users_db);
    free(eMail);
}


void display_all_users()
{
    FILE* users_db = fopen(USERS_DB_PATH, "r");
    User myUser;
    int i = 0;

    clear_screen();

    while (!feof(users_db))
    {
        myUser = load_next_user(users_db);

        if (myUser.groupID != 2)
        {
            disp(myUser.fName);
            disp(" ");
            disp(myUser.lName);
            disp(" - ");
            disp(myUser.profession);
            if (myUser.groupID == 1) //If admin
                disp(" (Admin)");
            disp("\n\t");
            disp(myUser.email);
            disp("\n\t");
            disp(myUser.mailingAdress);

            for (i = 0; i < myUser.numberBBooks; i++)
            {
                disp("\n\tBorrowed: ");
                disp(myUser.borrowedBooks[i]);
                disp(" - Return date: ");
                disp_int(myUser.returnDates[i].month);
                disp("/");
                disp_int(myUser.returnDates[i].day);
                disp("/");
                disp_int(myUser.returnDates[i].year);
            }

            disp("\n\n");
        }
    }

    fclose(users_db);
}


int get_user_ID(User myUser)
{
    FILE* users_db = fopen(USERS_DB_PATH, "r");
    User currentUser;
    int i = 0;

    do {
        currentUser = load_next_user(users_db);

        if (!strcmp(myUser.email, currentUser.email))
        {
            fclose(users_db);
            return i;
        }

        i++;
    } while(!feof(users_db));

    fclose(users_db);
    return -1;
}


void update_user(User myUser)
{
    FILE *users_db = fopen(USERS_DB_PATH, "r");
    User loadedUser;
    int i = 0, userID = get_user_ID(myUser);

    check_alloc(users_db);

    if (userID == -1) //If user not found in database
    {
        fclose(users_db);
        return;
    }

    //Copying database until user
    for (i = 0; i < userID; i++)
    {
        loadedUser = load_next_user(users_db);

        store_user(loadedUser, TEMP_DB_PATH);
    }

    //Copying updated user
    store_user(myUser, TEMP_DB_PATH);

    //Skip user in database (previous database)
    load_next_user(users_db);

    //Copying end of database
    while (!feof(users_db))
    {
        loadedUser = load_next_user(users_db);

        store_user(loadedUser, TEMP_DB_PATH);
    }

    fclose(users_db);

    remove(USERS_DB_PATH);

    rename(TEMP_DB_PATH, USERS_DB_PATH);
}


Book get_book_by_code(const char* bookCode)
{
    FILE* books_db = fopen(BOOKS_DB_PATH, "r");
    Book currentBook;

    check_alloc(books_db);

    while (!feof(books_db))
    {
        currentBook = load_next_book(books_db);

        if (!strcmp(bookCode, currentBook.code))
        {
            fclose(books_db);
            return currentBook;
        }
    }

    fclose(books_db);
    strcpy(currentBook.code, "ERR-000"); //Setting book code to error code
    return currentBook;
}


void order__users_db()
{
    FILE* users_db = fopen(USERS_DB_PATH, "r");
    User current, myUser;
    int ok = 0;

    check_alloc(users_db);

    //Getting the user
    while (!feof(users_db))
        myUser = load_next_user(users_db);

    //Setting the cursor to the beginning of the db
    rewind(users_db);

    //Copying the DB in a new file while looking for the right position for the user
    while (!feof(users_db))
    {
        ok = 0;
        current = load_next_user(users_db);


        /*//If same last name
        if (!strcmp(current.lName, myUser.lName))
        {
            //If also same first name
            if (!strcmp(current.fName, myUser.fName))
            {
                ok = 1;
                break;
            }


            if (strlen(current.fName) < strlen(myUser.fName))
                min_length = strlen(current.fName);
            else
                min_length = strlen(myUser.fName);


            for (i = 0; i < min_length && !ok; i++)
                if (char_upper(current.fName[i]) > char_upper(myUser.fName[i]))
                    ok = 1;

            //If names are the same for the length of the shortest
            if (i == min_length && !ok)
                if (min_length == strlen(myUser.fName))
                    ok = 1;
        }

        if (strlen(current.lName) <= strlen(myUser.lName))
            min_length = strlen(current.lName);
        else
            min_length = strlen(myUser.lName);


        for (i = 0; i < min_length; i++)
            if (char_upper(current.lName[i]) > char_upper(myUser.lName[i]))
                ok = 1;

        //If names are the same for the length of the shortest
        if (i == min_length && !ok)
            if (min_length == strlen(myUser.fName))
                ok = 1;

        */

        //If both last names are the same
        if (!strcmp(string_upper(current.lName), string_upper(myUser.lName)))
        {
            if (strcmp(string_upper(myUser.fName), string_upper(current.fName)) <= 0)
                if (strcmp(myUser.email, current.email)) //Checking if compared users are not the same user
                    ok = 1;
        } else //If names are different
        {
            if (strcmp(string_upper(myUser.lName), string_upper(current.lName)) < 0)
                ok = 1;
        }



        if (ok)
        {
            store_user(myUser, TEMP_DB_PATH);
            store_user(current, TEMP_DB_PATH);
            break;
        }

        store_user(current, TEMP_DB_PATH);
    }

    //Copying end of database
    while (!feof(users_db))
    {
        current = load_next_user(users_db);

        if (strcmp(current.email, myUser.email))
            store_user(current, TEMP_DB_PATH);
    }

    fclose(users_db);
    remove(USERS_DB_PATH);
    rename(TEMP_DB_PATH, USERS_DB_PATH);
}


void decode_users_db(const char* filePath)
{
    User myUser;
    FILE *users_db = fopen(USERS_DB_PATH, "r");
    FILE *decoded_db = fopen(filePath, "w");

    check_alloc(users_db);
    check_alloc(decoded_db);

    while (!feof(users_db))
    {
        myUser = load_next_user(users_db);

        fprintf(decoded_db, "User: %s %s ", myUser.fName, myUser.lName);
        if (myUser.groupID != 0)
            fprintf(decoded_db, "(Admin)");
        fprintf(decoded_db, "\n\tgroupID:\t\t%d\n", myUser.groupID);
        fprintf(decoded_db, "\te-mail:\t\t\t%s\n", myUser.email);
        fprintf(decoded_db, "\tpassword:\t\t%s\n", myUser.password);
        fprintf(decoded_db, "\tprofession:\t\t%s\n", myUser.profession);
        fprintf(decoded_db, "\tmailing adress:\t%s\n\n", myUser.mailingAdress);
    }

    fclose(users_db);
    fclose(decoded_db);

    printf("Dabase successfully decoded!\n");
}


void display_book_by_genre()
{
    char* genre = get_genre();
    Book currentBook;
    FILE* books_db = fopen(BOOKS_DB_PATH, "r");

    check_alloc(books_db);

    while (!feof(books_db))
    {
        currentBook = load_next_book(books_db);

        if (genre[0] == currentBook.code[0] && genre[1] == currentBook.code[1] && genre[2] == currentBook.code[2])
            display_book_info(currentBook);
    }

    fclose(books_db);
}


int verif_if_existing_user(const char* emailAdress)
{
    FILE* users_db = fopen(USERS_DB_PATH, "r");
    check_alloc(users_db);

    while (!feof(users_db))
        if (!strcmp(load_next_user(users_db).email, emailAdress))
        {
            fclose(users_db);
            return 1;
        }

    fclose(users_db);
    return 0;
}


void delete_account(User myUser)
{
    User currentUser;
    FILE* users_db = fopen(USERS_DB_PATH, "r");


    check_alloc(users_db);


    while (!feof(users_db))
    {
        currentUser = load_next_user(users_db);

        //If user loaded same as the one to remove
        if (!strcmp(currentUser.email, myUser.email))
            continue;

        store_user(currentUser, TEMP_DB_PATH);
    }

    fclose(users_db);

    remove(USERS_DB_PATH);
    rename(TEMP_DB_PATH, USERS_DB_PATH);
}


void change_password(char* password)
{
    clear_screen();
    disp("\n\nEnter your new password:");
    password_field(3, 0, password);
}
