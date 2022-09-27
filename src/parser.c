#include "parser.h"


static response *create_node(char *client_string,char *delimeter){

    response *node = NULL;
    node = (response *)malloc(sizeof(response));
    if(!node){
        return NULL;
    }
    char *token = strtok(client_string,delimeter);
    if(!token){
        return NULL;
    }
    strncpy(node->common_name, token,strlen(token)+1);
    token = strtok(NULL,delimeter);
    if(!token){
        return NULL;
    }
    strncpy(node->real_address, token,strlen(token)+1);
    token = strtok(NULL,delimeter);
    if(!token){
        return NULL;
    }
    strncpy(node->bytes_rec, token,strlen(token)+1);
    token = strtok(NULL,delimeter);
    if(!token){
        return NULL;
    }
    strncpy(node->bytes_sent, token,strlen(token)+1);
    token = strtok(NULL,delimeter);
    if(!token){
        return NULL;
    }
    strncpy(node->connected_since, token,strlen(token));
    node->next = NULL;
    return node;
}

static void append_to_list(response **head, response *node){

    response *tmp = *head;
    if(!tmp){
        *head = node;
        return;
    }

    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = node;
    return;
}

static void add_to_list_until(response **head, char *resp, char *delim1,char *delim2, char *stop_here){

    char *ptr = strtok(resp,delim1);
    char *save = NULL;
    while(ptr != NULL){
        save = strtok(NULL,"");
        response *node =NULL;
        if (strstr(ptr,stop_here)!= NULL){
            return;
        }
        node = create_node(ptr,delim2);
        if(!node){
            return;
        }
        append_to_list(head,node);
        ptr = strtok(save, delim1);
	}
    return;
}
void create_list(response **head, char* resp,char *delim1,char *delim2, char *stop_here,char *start_here){

    char *tmp = strstr(resp,start_here);
    add_to_list_until(head,tmp,delim1,delim2,stop_here);
}
response *remove_top(response *head){
    response *remove =head;
    head =head->next;
    free(remove);
    return head;
}

void delete_list(response *head){

    while (head !=NULL)
    {
        head =remove_top(head);
    }
    
}
void print_list(response *head){

    response *tmp = head;
    while(tmp != NULL){
        printf("%s  %s  %s  %s %s\n",tmp->common_name,tmp->bytes_rec,tmp->bytes_sent,tmp->real_address,tmp->connected_since);

		tmp=tmp->next;
    }
}