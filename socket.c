#include "socket.h"

static socket_fd;
static char key_word[] = "username";
static char http_response[buffer_size << 1];
static char string[buffer_size << 1];
static create_socket(socket_fd);
static bind_socket(socket_fd);
static reuse_port_immediately(socket_fd);
static server_listen(socket_fd);
static server_accept(new_socket_fd);
static build_http_response(user);
static build_string(user);

static create_socket(socket_fd)
int* socket_fd;
{
	*socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*socket_fd == -1)
	{
		perror("ERROR: in function create_socket() in line 11 *socket_fd = socket(AF_INET, SOCK_STREAM, 0) failed to create a socket\n");
		exit(1);
	}
}

static bind_socket(socket_fd)
int socket_fd;
{
	int res;
	socklen_t slen;
	struct sockaddr_in s_addr;
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(http_port);
	s_addr.sin_addr.s_addr = htons(INADDR_ANY);
	slen = sizeof(s_addr);
	errno = 0;
	res = bind(socket_fd, (const struct sockaddr*)&s_addr, slen);
	if (res == -1)
	{
		perror("ERROR : in function bind_socket(socket_fd) in line 23 failed to bind a socket\n");
		exit(2);
	}
}

static socket_close(socket_fd)
int socket_fd;
{
	int res;
	errno = 0;
	res = close(socket_fd);
	if (res == -1)
	{
		perror("ERROR: in function socket_close(socket_fd) in line 21 res = close(socket_fd) failed to close a socket\n");
		exit(3);
	}
}

static reuse_port_immediately(socket_fd)
int socket_fd;
{
	int res, n;
	n = 0;
	errno = 0;
	res = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n));
	if (res == -1)
	{
		perror("ERROR: in function reuse_port_immediately(socket_fd) in line 56 failed to resue port 8080\n");
		exit(4);
	}
}

static server_listen(socket_fd)
{
	int res;
	errno = 0;
	res = listen(socket_fd, queue);
	if (res == -1)
	{
		perror("ERROR: in function server_listen(socket_fd) in line 69 res = listen(socket_fd, queue) failed to make socket file descriptor listening\n");
		exit(5);
	}
}

static server_accept(new_socket_fd)
int* new_socket_fd;
{
	errno = 0;
	*new_socket_fd = accept(socket_fd, NULL, NULL);
	if (*new_socket_fd == -1)
	{
		perror("ERROR: in function server_accept(socket_fd) in line 83 failed to accept connection\n");
		exit(6);
	}
}

static build_string(user)
const struct user_info* user;
{
	size_t len;
	strcpy(string, user->user_name);
	len = strlen(string);
	*(string + len) = ':';
	strcat(string, "x");
	len = strlen(string);
	*(string + len) = ':';
	strcat(string, user->user_id);
	len = strlen(string);
	*(string + len) = ':';
	strcat(string, user->group_id);
	len = strlen(string);
	*(string + len) = ':';
	strcat(string, "x");
	len = strlen(string);
	*(string + len) = ':';
	strcat(string, user->home_path);
	len = strlen(string);
	*(string + len) = ':';
	strcat(string, user->path_to_interpretator);
	len = strlen(string);
	*(string + len) = 0;
}

static build_http_response(user)
const struct user_info* user; 
{
	size_t content_length;
	build_string(user);
	content_length = strlen(string);
	snprintf(http_response, sizeof(http_response),
		"HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: %lu\r\n"
                "Connection: close\r\n"
                "\r\n"
                "%s\r\n"
                , content_length, string);

}

create_http_server()
{
	create_socket(&socket_fd);
	bind_socket(socket_fd);
	server_listen(socket_fd);
}

read_data(buffer, fd)
char* buffer;
int fd;
{
	ssize_t cnt;
	errno = 0;
	cnt = read(fd, buffer, buffer_size);
	if (cnt == -1)
	{
		perror("ERROR: in function read_data(buffer) in line 89 cnt = read(socket_fd, buffer, length) failed to read data\n");
		exit(6);
	}
	*(buffer + cnt) = 0;
}

write_data(msg, socket_fd)
const struct user_info* msg;
int socket_fd;
{
	ssize_t cnt;
	size_t len;
	build_http_response(msg);
	len = strlen(http_response);
	errno = 0;
	cnt = write(socket_fd, http_response, len);
	if (cnt == -1)
	{
		perror("ERROR: in function write_data(msg, socket_fd) in line 131 failed to write data\n");
		exit(7);
	}
}

accept_http_request(new_socket_fd)
int* new_socket_fd;
{
	server_accept(new_socket_fd);
}

get_info(socket_fd, ok)
int socket_fd;
int* ok;
{
	struct sockaddr_in client_address;
	socklen_t slen;
	slen = sizeof(client_address);
	errno = 0;
       	*ok = getsockname(socket_fd, (struct sockaddr*)&client_address, &slen);
        if (*ok == -1)
		return -1;

        printf("\nCLINET PORT - %d\t CLIENT IP_ADDRESS - %s\n\n", ntohs(client_address.sin_port), inet_ntoa(client_address.sin_addr));       	
}

parse_url(url, value)						
const char* url;
char* value;
{
	int i, len, j, k;
	len = strlen(url);
	j = 0;
	k = 0;
	for (i = 0; i < len; i++)
	{
		if (*(url + i) == '/' || *(url + i) == '=')
			continue;
		if (*(url + i) == *(key_word + k))
		{
			k++;
			continue;
		}
		*(value + j) = *(url + i);
		j++;
	}
	*(value + j) = 0;
	printf("__DEBUG__ PARSED KEY_VALUE pair = %s\n", value);
}

close_http_server()
{
	reuse_port_immediately(socket_fd);
	socket_close(socket_fd);
}

