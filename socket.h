#ifndef SOCKET_H
#define SOCKET_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
enum {http_port = 8080};
enum {buffer_size = 255};
enum {queue = 15};
create_http_server();
read_data(buffer, fd);
write_data(msg);
close_http_server();
#endif
