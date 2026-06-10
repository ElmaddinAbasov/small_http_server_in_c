#include "socket.h"

static socket_fd;
static create_socket(socket_fd);
static bind_socket(socket_fd);
static reuse_port_immediately(socket_fd);
static server_listen(socket_fd);
static server_accept(socket_fd);

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

static server_accept(socket_fd)
int socket_fd;
{
	int new_socket_fd;
	errno = 0;
	new_socket_fd = accept(socket_fd, NULL, NULL);
	if (new_socket_fd == -1)
	{
		perror("ERROR: in function server_accept(socket_fd) in line 83 failed to accept connection\n");
		exit(6);
	}
	return new_socket_fd;
}

create_http_server()
{
	int new_socket_fd;
	create_socket(&socket_fd);
	bind_socket(socket_fd);
	server_listen(socket_fd);
	new_socket_fd = server_accept(socket_fd);
	return new_socket_fd;
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

write_data(msg)
const char* msg;
{

}

close_http_server()
{
	reuse_port_immediately(socket_fd);
	socket_close(socket_fd);
}
