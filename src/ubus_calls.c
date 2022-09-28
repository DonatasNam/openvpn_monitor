#include "ubus_calls.h"

int unload_list(response *head,struct ubus_context *ctx,struct ubus_request *req){

    int rc = 0;
    response *tmp = head;
    struct blob_buf b ={0};
    rc = blob_buf_init(&b,0);
    if(rc != 0){
        
        return rc;
    }
    void *main_tb =blobmsg_open_table(&b,"clients");
    while(tmp != NULL){
        void *client_tb =blobmsg_open_table(&b,NULL);
        blobmsg_add_string(&b,"client_name",tmp->common_name);
        if(rc != 0){
            return rc;
        }
        blobmsg_add_string(&b,"real_address",tmp->real_address);
        if(rc != 0){
            return rc;
        }
        blobmsg_add_string(&b,"bytes_recieved",tmp->bytes_rec);     
        if(rc != 0){
            return rc;
        }
        blobmsg_add_string(&b,"bytes_sent",tmp->bytes_sent); 
        if(rc != 0){
        return rc;
        }
        blobmsg_add_string(&b,"connected_since",tmp->connected_since);
        if(rc != 0){
            return rc;
        }
        blobmsg_close_table(&b,client_tb);
        tmp = tmp->next;
    }
    blobmsg_close_table(&b,main_tb); 
    ubus_send_reply(ctx,req,b.head);
    blob_buf_free(&b);
}

int client_get(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg){

    int rc =0;
    response *head = NULL;
    char *resp = msg_to_server(SERVER_STATUS);
    if(strstr(resp,"CLIENT LIST")==NULL){
        return -1;
    }
    create_list(&head,resp,"\n",",","ROUTING","Common Name");
    head =remove_top(head);
    print_list(head);
    unload_list(head,ctx,req);
    free(resp);
    delete_list(head);
    return 0;
}

struct ubus_context *start_ubus_loop(char *name){

    struct ubus_context *ctx =NULL;
    int rc = 0;
    monitor_object.name = name;
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
    char message[32];
    blobmsg_parse(kill_policy,__MAX,tb,blob_data(msg),blob_len(msg));
    if (!tb[CLIENT_NAME]){
        printf("%s, err %d",ubus_strerror(UBUS_STATUS_INVALID_ARGUMENT),UBUS_STATUS_INVALID_ARGUMENT);
        return UBUS_STATUS_INVALID_ARGUMENT;
    }
    char *client = blobmsg_get_string(tb[CLIENT_NAME]);
    sprintf(message,"kill %s\n",client);
    char *ret = msg_to_server(message);
    if(strstr(ret,"SUCCESS") == NULL){
        syslog(LOG_ERR,"%s",msg);
    }   
    free(ret);
    blob_buf_free(&blob_buff);
    return 0;
}