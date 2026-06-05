CC=cc
CCFLAGS=-Wall -ansi -Wextra -Wimplicit-int -Wreturn-type -O
init.o:init.c
	$(CC) $(CCFLAGS) -g -c $< -o $@
parse.o:parse.c
	$(CC) $(CCFLAGS) -g -c $< -o $@
postgres_db.o:postgres_db.c
	$(CC) $(CCFLAGS) -g -c $< -o $@
main:main.c init.o parse.o postgres_db.o
	$(CC) $(CCFLAGS) -g -lpq $^ -o $@

