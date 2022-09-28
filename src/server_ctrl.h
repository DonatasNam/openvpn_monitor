#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>

#define LOCALHOST "127.0.0.1"
int sock;
/*Returns initialized socket object or a negative integer on err*/
int socket_init(int port);
/*
Returns reply to sent messsage
Free returned string
*/
char *msg_to_server(char *msg);