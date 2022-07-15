#ifndef INOUT_H
#define INOUT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <sqlite3.h>

#define INOUTDB "/var/local/inout/inout.db"
#define INOUTCOLS 3

#define IN  "IN"
#define OUT "OUT"

#define TRUE 1
#define FALSE 0

#define IDLEN 10
#define STATUSLEN 3
#define COMMENTLEN 40

#endif
