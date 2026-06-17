#include "postgres_db.h"

static PGconn* conn;
static char db_info[size];

static do_exit(conn, exit_code);
static evaluate_args(pg_res, count, arg, message, res);
static run_query(query, pg_res);
static run_param_query(query, n_params, param_values, pg_res);

static do_exit(conn, exit_code)
PGconn* conn;
{
    PQfinish(conn);
    exit(exit_code);
}

static evaluate_args(pg_res, count, arg, message, res)
const PGresult* pg_res;
int count; 
const char* arg;
const char* message;
int* res;
{
	int i;
	char* string;
        for (i = 0; i < count; i++)
        {
		string = PQgetvalue(pg_res, i, 0);
                if (0 == strcmp(string, arg))
                {
			fprintf(stdout, message, string);
                        *res = 1;
                }
         }
}

connect_to_db(host, port, dbname, user, password)
const char* host;
const char* port;
const char* dbname;
const char* user;
const char* password;
{
        int len;
        strcat(db_info, host);
        strcat(db_info, port);
        strcat(db_info, dbname);
        strcat(db_info, user);
        strcat(db_info, password);
        len = strlen(db_info);
        *(db_info + len) = 0;
        conn = PQconnectdb(db_info);
        if (PQstatus(conn) == CONNECTION_BAD)
        {
                fprintf(stderr, "Connection failed: %s\n", PQerrorMessage(conn));
                do_exit(conn, 1);
        }

        printf("User: %s\n", PQuser(conn));
        printf("Database: %s\n", PQdb(conn));
	*db_info = 0;
}                                                                                       

static run_query(query, pg_res)
const char* query;
PGresult** pg_res;
{
	*pg_res = PQexec(conn, query);
	if (!*pg_res)
	{
		fprintf(stderr, "ERROR: on line 44 failed to run a %s query\n", query, PQerrorMessage(conn));
		do_exit(conn, 2);
	}
}

static run_param_query(query, n_params, param_values, pg_res)
const char* query;
int n_params;
const char* const* param_values;
PGresult** pg_res;
{
	*pg_res = PQexecParams(conn, query, n_params, NULL, param_values, NULL, NULL, 0);
	if (PQresultStatus(*pg_res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "ERROR: in function run_param_query(query, n_params, param_values, pg_res) failed to run a query\n %s", PQresultErrorMessage(*pg_res));
		do_exit(conn, 3);
	}
}

create_database()
{
	PGresult* pg_res;
	int i, rows, res;
	char* string;

	run_query(SELECT_ALL_DBS, &pg_res);

	if (PQresultStatus(pg_res) == PGRES_TUPLES_OK)
	{
		rows = PQntuples(pg_res);
		for (i = 0; i < rows; i++)
		{
			string = PQgetvalue(pg_res, i, 0);
			if (0 == strcmp(string, DB_NAME_TO_CREATE))
			{
				fprintf(stdout, "PROGRAM WARNING : Database %s already exsists\n", string);
				return 0;
			}
		}
	}
	run_query(CREATE_DB, &pg_res);
}

create_table()
{
	PGresult* pg_res;
	int i, rows, res;
	char* string;

	run_query(SELECT_ALL_TB, &pg_res);

	if (PQresultStatus(pg_res) == PGRES_TUPLES_OK)
	{
		rows = PQntuples(pg_res);
		for (i = 0; i < rows; i++)
		{
			string = PQgetvalue(pg_res, i, 0);
			if (0 == strcmp(string, TABLE_NAME))
			{
				fprintf(stdout, "PROGRAM WARNING : Table %s already exsists\n", string);
				return 0;
			}
			printf("TABLE NAME %s\n", string);
		}
	}	
	PQfinish(conn);
	connect_to_db(HOST, PORT, DB_NAME, USER, PASSWORD);
	run_query("BEGIN", &pg_res);
	run_query(CREATE_TB, &pg_res);
	run_query("COMMIT", &pg_res);
}

fill_database(users)
struct user_info* users;
{
	PGresult* pg_res;
	int i, j;
	char* param_values[array_length] = {" ", "x", " ", " ", "x", " ", " "};
	
	j = 0;
	for (i = 0; i < num_of_users; i++)
	{
		printf("DEBUG_PRINT___%i_____DEBUG_PRINT\n", i);
		param_values[j] = users[i].user_name;
		param_values[j + 2] = users[i].user_id;
		param_values[j + 3] = users[i].group_id;
#if 0		
		param_values[j + 4] = users[i].comments;
#endif		
		param_values[j + 5] = users[i].home_path;
		param_values[j + 6] = users[i].path_to_interpretator;
		run_query("BEGIN", &pg_res);
		run_param_query(INSERT, array_length, param_values, &pg_res);
		run_query("COMMIT", &pg_res);
	}
}

find_user(query, value)
const char* query;
const char* value;
{
	PGresult* pg_res;
	int i, j, rows, cols;
	const char* param_values[1] = {value};	/*concat query string with value and run sql query*/
#if 1
	strcpy(db_info, "SELECT * FROM users WHERE user_name = '");
	strcat(db_info, value);
	strcat(db_info, "'");
	printf("DB_INFO - %s\n", db_info);
	pg_res = PQexec(conn, db_info);
	if (PQresultStatus(pg_res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "%s\n", PQresultErrorMessage(pg_res));
	}
#else
	run_param_query("SELECT * FROM users WHERE user_name = $1;", 1, param_values, &pg_res);
#endif	
	rows = PQntuples(pg_res);
	cols = PQnfields(pg_res);
	printf("ROWS - %d\tCOLS-%d\n", rows, cols);
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
			printf("%s\n", PQgetvalue(pg_res, i, j));
	}
}

db_finish()
{
	PQfinish(conn);
}
