#include "ubus_calls.h"
#include "server_ctrl.h"
#include <syslog.h>

static char name[20];
static int id;
static int64_t sent;
static int64_t recieved;