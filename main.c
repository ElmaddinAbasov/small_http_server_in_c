#include "init.h"
#include "parse.h"
#include "postgres_db.h"
#include "sql.h"

main(argc, argv)
int argc;
char** argv;
{
        init();
        printf("buffer - \n%s\n", buffer);
        parse(buffer);
	connect_to_db(HOST, PORT, DEFAULT_DB_NAME, USER, PASSWORD);
	create_database();
	connect_to_db(HOST, PORT, DB_NAME, USER, PASSWORD);
	create_table();
	fill_database(users);
	db_finish();
        exit(0);
}


