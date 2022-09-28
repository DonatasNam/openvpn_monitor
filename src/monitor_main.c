#include "monitor_main.h"
error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct opts *options = state->input;
    switch (key)
    {
    case 'p':
        options->port = atoi(arg);
        break;
    case 'n':
        options->name = arg;
    break;
    case ARGP_KEY_END:
        if (!options->port || !options->name){
            argp_usage(state);
        }
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
int main(int argc, char **argv){

    int rc = 0;
    struct ubus_context *ctx;
    struct opts options;
    char name[64];
    argp_parse(&argp, argc, argv, 0, 0, &options);
    sprintf(name,"openvpn.%s",options.name);
    sock =socket_init(options.port);
    if(sock < 0){
        goto exit_no_ubus;
    }
    ctx =start_ubus_loop(name);
    if(!ctx){
        goto exit;
    }
    exit:
	ubus_free(ctx);
	uloop_done();
    exit_no_ubus:
    return 0;
}