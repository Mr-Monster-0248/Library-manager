#include "../headers/DB.h"

void store_new_user(User newUser)
{
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
  write_integers_array(users_db, cryptedEmail, strlen(newUser.email));
  write_integers_array(users_db, cryptedPassword, strlen(newUser.password) + 1);
  write_integers_array(users_db, cryptedFName, strlen(newUser.fName));
  write_integers_array(users_db, cryptedLName, strlen(newUser.lName));
  write_integers_array(users_db, cryptedProfession, strlen(newUser.profession));
  write_integers_array(users_db, cryptedMAdress, strlen(newUser.mailingAdress));

  //Freeing arrays
  free(cryptedEmail);
  free(cryptedPassword);
  free(cryptedFName);
  free(cryptedLName);
  free(cryptedProfession);
  free(cryptedMAdress);
}


void write_integers_array(FILE* file, int* array, const int numberElements)
{
  int i = 0;

  check_alloc(file);

  for (i = 0; i < numberElements - 1; i++)
    fprintf(file, "%d ", array[i]);
  fprintf(file, "%d\n", array[i]);
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

  FILE* file1 = fopen(path_toCopy, "r");
  FILE* file2 = fopen(path_newFile, "w");
  check_alloc(file1);
  check_alloc(file2);


  for (i = 0; i < stopLine && !feof(file1); i++)
    fprintf(file2, "%s\n", read_line(file1));

  fclose(file1);
  fclose(file2);
}


User load_next_user(FILE* user_db)
{
  check_alloc(user_db);


}
