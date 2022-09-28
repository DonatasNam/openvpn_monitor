#include "ubus_calls.h"
#include "server_ctrl.h"
#include <syslog.h>
#include <argp.h>

static char name[20];
static int id;
static int64_t sent;
static int64_t recieved;

char arg_doc[] = "port";

struct argp_option options[]= {
    {"name",        'n', "NAME",        0, "Server Name"},   
    {"port",        'p', "PORT",        0, "Port for managment server"},
    {0}
};

struct opts{
    char *name;
    int port;
};
error_t parse_opt(int key, char *arg, struct argp_state *state);
struct argp argp = {options, parse_opt, arg_doc};