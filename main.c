#include "init.h"
#include "parse.h"
#include "postgres_db.h"
#include "sql.h"
#include "socket.h"

static char storage[buffer_size];
static char method[buffer_size];
static char uri[buffer_size];
static char value[buffer_size];
static char version[buffer_size];
const char http_response[] = "HTTP/1.1 200 OK\r\n"
			     "Content-Type: text/html\r\n"
			     "Content-Length: 20\r\n"
			     "Connection: close\r\n\r\n"
			     "<h1>Hello, World!</h1>";

static free_resources(fd);
static free_resources(fd)
{
	close(fd);
        close_http_server();
        db_finish();
        exit(1);
}

main(argc, argv)
int argc;
char** argv;
{
	int new_socket_fd, ok;
	size_t len;

        init();
        printf("buffer - \n%s\n", buffer);
        parse(buffer);
	connect_to_db(HOST, PORT, DEFAULT_DB_NAME, USER, PASSWORD);
	create_database();
	connect_to_db(HOST, PORT, DB_NAME, USER, PASSWORD);
	create_table();
	fill_database(users);
#if 0	
	db_finish();
#endif
	create_http_server();
	for (;;)
	{
		accept_http_request(&new_socket_fd);

		read_data(storage, new_socket_fd);
		len = strlen(storage);
		*(storage + len) = 0;

		ok = 0;
		get_info(new_socket_fd, &ok);
		if (ok == -1)
			free_resources(new_socket_fd);

		printf("Data - %s\n", storage);
		sscanf(storage, "%s %s %s", method, uri, version);

		parse_url(uri, value);
		
		printf("HTTP_METHOD - %s\t URI - %s\t HTTP_VERSION - %s\n", method, uri, version);

		find_user(FIND_USER, value);

		write_data(http_response, new_socket_fd);

		printf("I`m here");

		close(new_socket_fd);
		break;
	}

	printf("close\n");
	close_http_server();
	db_finish();

        exit(0);
}


