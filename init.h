#ifndef INIT_H
#define INIT_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

enum {buffer_cap = 3096};
extern char buffer[buffer_cap];
init();
#endif

