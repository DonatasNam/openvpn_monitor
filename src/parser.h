#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum{
    LVL_1,
    LVL_2
}node_type;

typedef struct level_two
{
    char *token;
    struct level_two *next;
}level_two;

typedef struct level_one{

    char *token;
    struct level_one *next;
    struct level_two *two_head;
}level_one;

typedef struct string_parser{
    level_one *one_head;

}parser;

parser* parser_init();
void parser_destroy(parser *ctx);
void print_parser(parser *ctx);
void string_parse_from_to(parser *ctx,char *string,char *from,char* to,char *lvl1_delim,char *lvl2_delim);
char *extract_selected_string(parser *ctx,int depth,int list_num,int str_num);

static void * delete_node(void* head,int depth);
static void delete_level(void *head,int depth);
static void delete_list(void *head,int depth);

static void *create_node(char * data, int depth);
static void append_to_list(void **head, void *node, int depth);
static void create_child_loop(void **parent_head,char *delim,int depth);
static void string_split(char *string, char* delim,void **head,int depth);
static void string_split_to(char *string,char* select, char* delim,void **head,int depth);

static void print_list(void *head,int depth);
static void print_loop(void* head,int depth);

static char *__extract_string(void *head, int string_num, int depth);