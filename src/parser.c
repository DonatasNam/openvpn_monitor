#include "parser.h"

static void *create_node(char * data, int depth){
    level_two *two_node = NULL;
    level_one *one_node =NULL;
    switch (depth)
    {
    case LVL_1:

        one_node = (level_one *)malloc(sizeof(level_one));
        one_node->token = (char *)malloc(strlen(data)+1);
        strncpy(one_node->token,data,strlen(data)+1);
        return one_node;
        break;
    case LVL_2:

        two_node = (level_two *)malloc(sizeof(level_two));
        two_node->token= (char *)malloc(strlen(data)+1);
        strncpy(two_node->token,data,strlen(data)+1);
        return two_node;
        break;
    default:
        return NULL;
        break;
    }
}

static void append_to_list(void **head, void *node, int depth){
    
    level_one *one_tmp = NULL;
    level_two *two_tmp = NULL;
    switch (depth)
    {
    case LVL_2:

        two_tmp = (level_two*)*head;
        if(two_tmp == NULL){
            *head = (level_two*)node;
            return;
        }
        while(two_tmp->next != NULL){

            two_tmp = two_tmp->next;
        }
        two_tmp->next = node;
        return;
        break;

    case LVL_1:
        one_tmp = (level_one*)*head;
        if(one_tmp == NULL){
            *head = (level_one*)node;
            return;
        }
        while(one_tmp->next != NULL){
            //printf("NEXT: %p NODE: %p\n",one_tmp->next,node);
            //LOOPS HERE
            one_tmp = one_tmp->next;
        }
        one_tmp->next = node;
        return;
        break;
    default:
        return;
        break;
    }
}

static void string_split(char *string, char* delim,void **head,int depth){

    char *ptr = strtok(string,delim);
    switch (depth)
    {
    case LVL_1:
        while(ptr != NULL){
            level_one *node =NULL;
		    node = create_node(ptr,LVL_1);
		    append_to_list(head,node,LVL_1);
            ptr = strtok(NULL, delim);
	    }
    return;
    break;
    case LVL_2:
        while(ptr != NULL){
            level_two *node =NULL;
		    node = create_node(ptr,LVL_2);
		    append_to_list(head,node,LVL_2);
            ptr = strtok(NULL, delim);
	    }
    return;
    break;    
    default:
        return;
        break;
    }
}
//dont send lvl 2
static void string_split_to(char *string,char* select, char* delim,void **head,int depth){

    char *ptr = strtok(string,delim);
    puts(select);
    while(ptr != NULL){
        puts(ptr);
        level_one *node =NULL;
        if (strstr(ptr,select)!= NULL){
            return;
        }
        node = create_node(ptr,LVL_1);
        append_to_list(head,node,LVL_1);
        ptr = strtok(NULL, delim);

	}
    return;
}
static void print_list(void *head,int depth){

    switch(depth)
    {
    case LVL_1:
        if (!head){
            return;
        }
        level_one *one_tmp = (level_one*)head;
        while(one_tmp != NULL){
            printf("lvl1: %s\n",one_tmp->token);
		    one_tmp=one_tmp->next;
        }
        printf("List end\n");
        return;
        break;
    case LVL_2:
        if (!head){
            return;
        }
        level_two *two_tmp = (level_two*)head;
        while(two_tmp != NULL){
            printf("lvl2 :%s\n",two_tmp->token);
		    two_tmp=two_tmp->next;
        }
        printf("List end\n");
        return;
        break;
    
    default:
        return;
        break;
    }
}

static void print_loop(void* head,int depth){

    level_one *one_tmp = (level_one *)head;
    
    while (one_tmp != NULL)
    {
        print_list((void *)one_tmp->two_head,depth+1);
        one_tmp= one_tmp->next;    
    }
    
}


static void create_child_loop(void **parent_head,char *delim,int depth){

    level_one *one_tmp =(level_one *)*parent_head;
    puts("CIA ???????????");
    if(!one_tmp){
        return;
    }
    while (one_tmp != NULL)
    {
        printf("child loop");
        char *dup =strdup(one_tmp->token);
        string_split(dup,delim,(void *)&one_tmp->two_head,LVL_2);
        one_tmp =one_tmp->next;
        free(dup);
    }
}



static void delete_list(void *head,int depth){
    
    level_one *one_delete =(level_one *)head;
    level_two *two_delete =(level_two *)head;
    switch (depth)
    {
    case LVL_1:
        while(one_delete != NULL){
            one_delete =(level_one*)delete_node(one_delete,LVL_1);
        }
        return;
        break;
    case LVL_2:
        while(two_delete != NULL){
            two_delete =(level_two*)delete_node(two_delete,LVL_2);
        }
        return;
        break;   
    default:
        return;
        break;
    }
}
static void delete_level(void *head,int depth){

    level_one* one_tmp = (level_one*)head;
    while (one_tmp != NULL)
    {
        delete_list(one_tmp->two_head,depth);
        one_tmp = one_tmp->next;
    }
}
static char *__extract_string(void *head, int string_num, int depth){
    int i=0;
    char *extracted;
    level_one *one_head =(level_one*)head;
    level_two* two_head =(level_two*)head;
    switch(depth)
    {   
    case LVL_1:
        while(i != string_num && one_head != NULL){

            one_head=one_head->next;
            i++;        
        }
        if(one_head == NULL){
            return NULL;
        }
        extracted = strdup(one_head->token);
        return extracted;
        break;

        case LVL_2:
        while(i != string_num && two_head != NULL){

            two_head=two_head->next;
            i++;        
        }
        if(two_head == NULL){
            return NULL;
        }
        extracted = strdup(two_head->token);
        return extracted;
        break;
    default:
        return NULL;
        break;
    }
}


static void * delete_node(void* head,int depth){

    level_one *one_delete =(level_one*)head;
    level_one *one_head=(level_one*)head;
    level_two *two_delete =(level_two*)head;
    level_two *two_head=(level_two*)head;
    switch (depth)
    {
    case LVL_1:
    	one_delete =one_head;
	    one_head = one_head->next;
	    free(one_delete->token);
	    free(one_delete);
	    return one_head;
    break;
    case LVL_2:
    	two_delete =two_head;
	    two_head = two_head->next;
	    free(two_delete->token);
	    free(two_delete);
	    return two_head;
    break;
    default:
        return NULL;
        break;
    }

}
char *extract_selected_string(parser *ctx,int depth,int list_num,int str_num){

    char *extracted;
    int i =0;
    level_one * one_head =ctx->one_head;

    switch (depth)
    {
    case LVL_1:
        extracted =__extract_string(one_head,str_num,LVL_1);
        return extracted;
        break;
    
    case LVL_2:

        while (i != list_num  && one_head != NULL)
        {
            one_head =one_head->next;
            i++;
        }
        if(one_head == NULL){
            return NULL;
        }
               
        extracted = __extract_string(one_head->two_head,str_num,LVL_2);
        break;
    default:
        break;
    }
}

parser* parser_init(){
    parser *ctx;
    ctx = (parser *)malloc(sizeof(parser));
    level_two * two_head =NULL;
    level_one *one_head =NULL;
    return ctx;
}

void parser_destroy(parser *ctx){
    
    delete_level(ctx->one_head,LVL_2);
    delete_list(ctx->one_head,LVL_1);
    free(ctx);
}

void print_parser(parser *ctx){

    print_list((void *)ctx->one_head,LVL_1);
    print_loop((void *)ctx->one_head,LVL_1);
}

void string_parse_from_to(parser *ctx,char *string,char *from,char* to,char *lvl1_delim,char *lvl2_delim){

    char *tmp =strstr(string,from);
    puts("here");
    string_split_to(tmp,to,lvl1_delim,(void *)&ctx->one_head,LVL_1);
    puts("here");
    create_child_loop((void *)&ctx->one_head,lvl2_delim,LVL_2);
    
}