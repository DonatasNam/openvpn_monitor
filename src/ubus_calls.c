#include "ubus_calls.h"


int client_get(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg){

    // int rc =0;
    // struct blob_buf blob_buf = {};
    // rc =blob_buf_init(&blob_buf,0);
    // if(rc != 0){
    //     syslog(LOG_ERR,"%s, err: %d",ubus_strerror(rc),rc);
    //     return rc;
    // }
    // rc =blobmsg_add_string(&blob_buf,"server name",name);
    // if(rc != 0){
    //     syslog(LOG_ERR,"%s, err: %d",ubus_strerror(rc),rc);
    //     return rc;
    // }
    // rc =blobmsg_add_u16(&blob_buf,"server id",id);
    // if(rc != 0){
    //     syslog(LOG_ERR,"%s, err: %d",ubus_strerror(rc),rc);
    //     return rc;
    // }
    // rc =blobmsg_add_u64(&blob_buf,"data sent",sent);
    // if(rc != 0){
    //     syslog(LOG_ERR,"%s, err: %d",ubus_strerror(rc),rc);
    //     return rc;
    // }
    // rc =blobmsg_add_u64(&blob_buf,"data recieved",recieved);
    // if(rc != 0){
    //     syslog(LOG_ERR,"%s, err: %d",ubus_strerror(rc),rc);
    //     return rc;
    // }
    // rc =ubus_send_reply(ctx,req,blob_buf.head);
    // if(rc != 0){
    //     syslog(LOG_ERR,"%s, err: %d",ubus_strerror(rc),rc);
    //     return rc;
    // }
    // blob_buf_free(&blob_buf);
    parser *parse =NULL;
    parse =parser_init();
    puts("Here");
    char *ret =msg_to_server(SERVER_STATUS);
        puts("Here");
    string_parse_from_to(parse,ret,"Common Name","ROUTING","\n",",");
        puts("Here");
    free(ret);
        puts("Here");
    print_parser(parse);
        puts("Here");
    parser_destroy(parse);
        puts("Here");
    return 0;
}
struct ubus_context *start_ubus_loop(){

    struct ubus_context *ctx =NULL;
    int rc = 0;
    rc = uloop_init();
    if (rc != UBUS_STATUS_OK){
        syslog(LOG_ERR,"%s err: %d",ubus_strerror(rc),rc);
        return NULL;
    }
    ctx = ubus_connect(NULL);
	if (!ctx) {
        rc =UBUS_STATUS_CONNECTION_FAILED;
		syslog(LOG_ERR,"%s err: %d",ubus_strerror(rc),rc);
		return NULL;
	}
    ubus_add_uloop(ctx);
	ubus_add_object(ctx, &monitor_object);
    if (rc != UBUS_STATUS_OK){
        syslog(LOG_ERR,"%s err: %d",ubus_strerror(rc),rc);
        return NULL;    
    }
	uloop_run();
    if (rc != UBUS_STATUS_OK){
        syslog(LOG_ERR,"%s err: %d",ubus_strerror(rc),rc);
        return NULL;
    }
    return ctx;
}
int kill_client(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg){

    struct blob_attr *tb[__MAX];
    struct blob_buf blob_buff ={};
    blobmsg_parse(kill_policy,__MAX,tb,blob_data(msg),blob_len(msg));
    printf("got kill request\n");
    if (!tb[CLIENT_NAME]){
        printf("%s, err %d",ubus_strerror(UBUS_STATUS_INVALID_ARGUMENT),UBUS_STATUS_INVALID_ARGUMENT);
        return UBUS_STATUS_INVALID_ARGUMENT;
    }

    char *client = blobmsg_get_string(tb[CLIENT_NAME]);
    printf("kill client with name: %s\n",client);

    blob_buf_free(&blob_buff);
    
    return 0;
}