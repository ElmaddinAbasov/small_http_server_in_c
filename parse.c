#include "parse.h"

struct user_info users[num_of_users];

static split(buffer)
char* buffer;
{
        int len, i;
        len = strlen(buffer);
        for (i = 0; i < len; i++)
        {
                if (*(buffer + i) == '\n')
                        *(buffer + i) = 0;
        }
}

static dummy_function(pointer, data, code)
char** pointer;
struct user_info* data;
int code;
{
        switch (code)
        {
                /*delete this line later*/
                case user :
                        *pointer = data->user_name;
                        break;
                case password :
                        *pointer = &(data->password);
                        break;
                case uid :
                        *pointer = data->user_id;
                        break;
                case gid :
                        *pointer = data->group_id;
                        break;
                case comments :
                        *pointer = data->comments;
                        break;
                case home_path :
                        *pointer = data->home_path;
                        break;
                case interpretator :
                        *pointer = data->path_to_interpretator;
                        break;
        }
}

parse(buffer)
const char* buffer;
{
        int i, pos, num_of_semicolons, j;
        struct user_info u_info;
        char* mem;

        i = 0;
        pos = 0;
        num_of_semicolons = 0;
        j = 0;
        mem = u_info.user_name;

        split(buffer);

        while (*(buffer + pos))
        {
                if (*(buffer + pos) == SEMICOLON)
                {
                        *(mem + i) = 0;
                        pos++;
                        i = 0;
                        num_of_semicolons++;
                        dummy_function(&mem, &u_info, num_of_semicolons);
                        if (num_of_semicolons == max_num_of_semicolons)
                        {
                                mem = u_info.path_to_interpretator;
                                while (*(buffer + pos))
                                {
                                        *(mem + i) = *(buffer + pos);
                                        i++;
                                        pos++;
                                }
                                *(mem + i) = 0;
                                i = 0;
                                users[j] = u_info;
                                j++;
                                printf("DEBUG_PRINT : %s\n%c\n%s\n%s\n%s\n%s\n%s\n", u_info.user_name,
                                                u_info.password, u_info.user_id,
                                                u_info.group_id, u_info.comments, u_info.home_path,
                                                u_info.path_to_interpretator);
                                mem = u_info.user_name;
                                pos++;
                                num_of_semicolons = 0;
                        }
                }
                *(mem + i) = *(buffer + pos);
                pos++;
                i++;
        }
}

                                        
