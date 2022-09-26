#include "monitor_main.h"

int main(){

    int rc = 0;
    struct ubus_context *ctx;
    sock =socket_init();
    if(sock < 0){
        //return
    }
    ctx =start_ubus_loop();
    if(!ctx){
        //goto
    }

	ubus_free(ctx);
	uloop_done();
    return 0;
}