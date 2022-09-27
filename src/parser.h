#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct server_response{

    char common_name[32];
    char real_address[32];
    char bytes_rec[32];
    char bytes_sent[32];
    char connected_since[32];
    struct server_response* next;
}response;

void create_list(response **head, char* resp,char *delim1,char *delim2, char *stop_here,char *start_here);
response *remove_top(response *head);
void delete_list(response *head);
void print_list(response *head);