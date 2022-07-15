/*
 ============================================================================
 Name        : 426.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "inout.h"

int callback_printf(void *notused, int ncols, char **cols, char **colnames);

int main(int argc, char **argv) {

  sqlite3 *db;
  sqlite3_stmt *res;
  char cmd[80];
  char uname[IDLEN];
  int err;


  if ( (err = sqlite3_open(INOUTDB, &db)) != SQLITE_OK) {
    fprintf(stderr, "Error: failed to open database\n");
    exit(1);
  }

  if (argc < 2) {

    sprintf(cmd, "SELECT * from inout;");

    if ( (err = sqlite3_exec(db, cmd, &callback_printf, NULL, NULL)) != SQLITE_OK ) {
      fprintf(stderr, "Error: unable to query database.\n");
      sqlite3_close(db);
      exit(1);
    }

  } 
  else {

    sprintf(cmd, "SELECT * from inout WHERE id=\'%s\'", argv[1]);

    if ( (err = sqlite3_exec(db, cmd, &callback_printf, NULL, NULL)) != SQLITE_OK ) {
      fprintf(stderr, "Error: unable to query database.\n");
      sqlite3_close(db);
      exit(1);
    }
  }

  exit(0);

}

int callback_printf(void *notused, int ncols, char **cols, char **colnames) {

  if (cols[2][0] == '\0') {
    printf("%s is %s\n", cols[0], cols[1]);
  } else {
    printf("%s is %s (%s)\n", cols[0], cols[1], cols[2]);
  }

  return 0;
}

