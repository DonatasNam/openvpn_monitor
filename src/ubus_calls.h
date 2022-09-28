#include <libubus.h>
#include <stdio.h>
#include <syslog.h>
#include "parser.h"
#include "server_ctrl.h"

#define SERVER_STATUS "status\n"
static char name[20];
static int id;
static int64_t sent;
static int64_t recieved;

enum {
    CLIENT_NAME,
    __MAX
};
struct ubus_context *start_ubus_loop(char *name);
int client_get(struct ubus_context *ctx, struct ubus_object *obj,struct ubus_request_data *req, const char *method,struct blob_attr *msg);
int kill_client(struct ubus_context *ctx, struct ubus_object *obj,struct ubus_request_data *req, const char *method,struct blob_attr *msg);

static const struct blobmsg_policy kill_policy[] = {

    [CLIENT_NAME] ={.name = "client_name", .type = BLOBMSG_TYPE_STRING},
};

static const struct ubus_method monitor_methods[] ={

    UBUS_METHOD_NOARG("get", client_get),
    UBUS_METHOD("kill", kill_client, kill_policy),
};

static struct ubus_object_type monitor_object_type= UBUS_OBJECT_TYPE("openvpn.server",monitor_methods);

static struct ubus_object monitor_object ={
    .type = &monitor_object_type,
    .methods = monitor_methods,
    .n_methods = ARRAY_SIZE(monitor_methods),
};