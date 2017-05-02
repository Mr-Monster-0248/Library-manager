#include "../headers/DB.h"

void store_new_user(User newUser)
{
  int* intArray;
  FILE* db =  fopen(USERS_DB_PATH, "a");
  check_alloc(db);

  //Encrypting and writing the username in the users database
  intArray = encrypt_to_int(User.username);
  write_integers_array(db, intArray, strlen(User.username));
  free(intArray);

  //Creating the encrypted array of integers for the password and groupID and writing them in the users database
  intArray = encrypt_to_int(User.password);
  intArray = realloc( (strlen(User.password) + 1) * sizeof(int) );
  intArray[strlen(User.password)] = User.groupID + strlen(User.password);
  write_integers_array(db, intArray, strlen(User.username) + 1

  fclose(db);
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
  char* line = (char*) malloc(size(char));
  check_alloc(line);

  while(!feof(file))
  {
    readChar = fgetc(file);

    if (readChar == '\n' || feof(file))
      break;

    line = (char*) realloc((i + 1) * sizeof(char));
    check_alloc(line);

    line[i] = readChar;
  }

  return line;
}




void copy_to_line(char* path_toCopy, char* path_newFile, const int stopLine)
{
  int i = 0;

  for (i = 0; i < stopLine; i++)
  {

  }
}
