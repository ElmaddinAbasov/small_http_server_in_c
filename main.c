#include "init.h"
#include "parse.h"
#include "postgres_db.h"
#include "sql.h"
#include "socket.h"

static char storage[buffer_size];
const char* http_response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 20\r\nConnection: close\r\n\r\n<h1>Hello, World!</h1>";
			      
#endif
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
	create_http_server();
	for (;;)
	{
		accept_http_request(&new_socket_fd);
		read_data(storage, new_socket_fd);
		len = strlen(storage);
		*(storage + len) = 0;
		printf("Data - %s\n", storage);
		write_data(http_response, new_socket_fd);
		printf("I`m here");
		close(new_socket_fd);
		break;
	}
	printf("close\n");
	close_http_server();
#endif	
        exit(0);
}


