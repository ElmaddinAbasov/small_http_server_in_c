#ifndef POSTGRES_DB_H
#define POSTGRES_DB_H
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>
#include "sql.h"
#include "parse.h"
enum {size = 255};
enum {array_length = 7};
#define HOST "host=localhost"
#define PORT " port=5432"
#define DEFAULT_DB_NAME " dbname=postgres"
#define USER " user=JohnGacy"
#define PASSWORD " password=Gacy1996"
#define DB_NAME_TO_CREATE "etc_users"
#define TABLE_NAME "users"
#define DB_NAME " dbname=etc_users"
connect_to_db(host, port, dbname, user, password);
create_database();
create_table();
fill_database(users);
db_finish();
#endif
