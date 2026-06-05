#ifndef SQL_H
#define SQL_H

enum {num_of_params = 7};

#define SELECT_ALL_DBS "SELECT datname FROM pg_database;" 

#define SELECT_ALL_TB "SELECT tablename FROM pg_tables;"

#define CREATE_DB "CREATE DATABASE etc_users;"

#define CREATE_TB "CREATE TABLE users (user_name varchar(255) NOT NULL PRIMARY KEY, password varchar(255) NOT NULL, user_id varchar(255) NOT NULL, group_id varchar(255) NOT NULL, comments varchar(255) NOT NULL, home_path varchar(255) NOT NULL, path_to_interpretator varchar(255) NOT NULL);"

#define INSERT "INSERT INTO users (user_name,password,user_id,group_id,comments,home_path,path_to_interpretator) VALUES ($1,$2,$3,$4,$5,$6,$7);"

#endif
