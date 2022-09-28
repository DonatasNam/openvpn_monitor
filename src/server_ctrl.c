#include "server_ctrl.h"
int socket_init(int port){   
    
    int rc =0;
    int soc_tmp= 0;
	struct sockaddr_in client;
	soc_tmp = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (soc_tmp == -1)
	{
		printf("Could not create socket");
    }
	client.sin_addr.s_addr = inet_addr(LOCALHOST);
	client.sin_family = AF_INET;
	client.sin_port = htons(port);

    rc =connect(soc_tmp , (struct sockaddr *)&client , sizeof(client));
	if (rc < 0){
		perror("connect failed. Error");
		return -1;
	}
	return soc_tmp;
}
char *msg_to_server(char *msg){
	int rc =0;
    char *ret = NULL;
    char reply[2048];
    memset(reply,0,sizeof(reply));
	rc =send(sock , msg , strlen(msg) ,0);
	if(rc < 0){
		syslog(LOG_ERR,"error commuincating with socket err: %d",rc);
		return NULL;
	}
	usleep(100);
    rc = recv(sock , reply , 2048 ,0);
	if(rc < 0){   
		syslog(LOG_ERR,"error commuincating with socket err: %d",rc);
		return NULL;
	}
    ret = strdup(reply);
	puts(ret);
	return ret;
}

