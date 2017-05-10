#include "../headers/DB.h"

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

    FILE* test_file = fopen("log", "w");

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
    fprintf(test_file, "mail: \"%s\"\n", dEmail);

    //password
    cryptedPassword = return_int_line(user_db, &numberChars);
    dPassword = decrypt_to_string(cryptedPassword, numberChars);
    fprintf(test_file, "password: \"%s\"\n", dPassword);

    //first name
    cryptedFName = return_int_line(user_db, &numberChars);
    dFName = decrypt_to_string(cryptedFName, numberChars);
    fprintf(test_file, "first name: \"%s\"\n", dFName);

    //last name
    cryptedLName = return_int_line(user_db, &numberChars);
    dLName = decrypt_to_string(cryptedLName, numberChars);
    fprintf(test_file, "last name: \"%s\"\n", dLName);

    //profession
    cryptedProfession = return_int_line(user_db, &numberChars);
    dProfession = decrypt_to_string(cryptedProfession, numberChars);
    fprintf(test_file, "profession: \"%s\"\n", dProfession);

    //mailing adress
    cryptedMAdress = return_int_line(user_db, &numberChars);
    dMAdress = decrypt_to_string(cryptedMAdress, numberChars);
    fprintf(test_file, "mailing adress: \"%s\"\n", dMAdress);

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
