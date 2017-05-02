#include "../headers/DB.h"

void add_new_user(char* username, char* password, int groupID)
{
  FILE* db =  fopen(USERS_DB_PATH, "a");
  check_alloc(db);

  
}
