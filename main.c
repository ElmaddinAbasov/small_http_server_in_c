#include "init.h"
#include "parse.h"
#include "postgres_db.h"
#include "sql.h"
#include "socket.h"

char storage[buffer_size];
main(argc, argv)
int argc;
char** argv;
{
	int new_socket_fd;
	size_t len;
        init();
        printf("buffer - \n%s\n", buffer);
        parse(buffer);
	connect_to_db(HOST, PORT, DEFAULT_DB_NAME, USER, PASSWORD);
	create_database();
	connect_to_db(HOST, PORT, DB_NAME, USER, PASSWORD);
	create_table();
	fill_database(users);
	db_finish();
#if 1
	new_socket_fd = create_http_server();
	for (;;)
	{
		read_data(storage, new_socket_fd);
		len = strlen(storage);
		*(storage + len) = 0;
		printf("Data - %s\n", storage);
		break;
	}
	close_http_server();
#endif	
        exit(0);
}


