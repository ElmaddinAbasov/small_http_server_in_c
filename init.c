#include "init.h"
static const char* path = "/etc/passwd";
static fd;
char buffer[buffer_cap];

static open_file(path)
const char* path;
{
        errno = 0;
        fd = open(path, O_RDONLY);
        if (fd == -1)
        {
                perror("ERROR Report : on a line fd = open(path, O_RDONLY) failed to aopen a file\n");
                exit(1);
        }
}

static read_file(fd, buffer)
int fd;
char* buffer;
{
        ssize_t cnt;
        errno = 0;
        cnt = read(fd, buffer, buffer_cap);
        if (cnt == -1)
        {
                perror("ERROR Report : in function read_file(fd, buffer) on a line cnt = read(fd, buffer, buffer_cap)\n");
                exit(2);
        }
        *(buffer + cnt) = 0;
}

static close_file(fd)
int fd;
{
        int res;
        errno = 0;
        res = close(fd);
        if (res == -1)
        {
                perror("ERROR Report : on a line res = close(fd) failed to close a file using file descriptor fd\n");
                exit(3);
        }
}

init()
{
        open_file(path);
        read_file(fd, buffer);
        close_file(fd);
}

