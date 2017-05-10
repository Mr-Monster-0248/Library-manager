#include "../headers/DB.h"
#ifdef __WIN32__
#include "../headers/UI_windows.h"
#else
#include "../headers/UI_unix.h"
#endif

void store_new_user(User newUser)
{
    int i = 0;
    int *cryptedEmail = NULL, *cryptedPassword = NULL, *cryptedFName = NULL, *cryptedLName = NULL, *cryptedProfession = NULL, *cryptedMAdress = NULL;
    FILE* users_db = fopen(USERS_DB_PATH, "a");

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

    for (i = 0; i < newUser.numberBBooks; i++)
    {
        /*
        TODO: crypting of books code and return dates
        */
    }

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

    line[i + 1] = '\0'; //To end the string

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
    int *cryptedEmail = NULL, *cryptedPassword = NULL, *cryptedFName = NULL, *cryptedLName = NULL, *cryptedProfession = NULL, *cryptedMAdress = NULL;
    char *dEmail = NULL, *dPassword = NULL, *dFName = NULL, *dLName = NULL, *dProfession = NULL, *dMAdress = NULL;
    int numberBooks = 0, i = 0, numberChars = 0;

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
    dPassword = decrypt_to_string(cryptedPassword, numberChars);

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
        /*
        TODO: store books data
        */
    }

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

    return myBook;
}


void display_book_db()
{
    FILE* books_db = fopen(BOOKS_DB_PATH, "r");
    check_alloc(books_db);

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
