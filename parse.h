#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {length = 255};
enum {min_length = 6};
enum {user = 0};
enum {password = 1};
enum {uid = 2};
enum {gid = 3};
enum {comments = 4};
enum {home_path = 5};
enum {interpretator = 6};
enum {num_of_users = 1000};
enum {num_of_fields = 7};
enum {max_num_of_semicolons = 6};

#define SEMICOLON ':'

struct user_info
{
        char user_name[length];
        char password;
        char user_id[min_length];
        char group_id[min_length];
        char comments[length];
        char home_path[length];
        char path_to_interpretator[length];
};

extern struct user_info users[num_of_users];

parse(buffer);
#endif

