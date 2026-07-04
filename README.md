# Writing a small_http_server_in_c that handles client`s request and returns to a broweser information about Linux user, that it takes from etc_passwd file.


# Small description of our program

The program consists of two part : server and a client(in our case a web broweser). On a backend server we have a database etc_users, that is filled with information from etc_passwd. Client sends a request, a URL of a form http://lochalhost:8080/username=VALUE, server gets this request, connects to a database, search for user with a username that client provided us. And if a user with such name exsist, sends to a client a string with user id, group id, passwd, path to home directory and e.t.c

