#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLen 1024

typedef struct CTask{
	int sockfd;
	int port;
	char* ip;
	char* str;
}CTask;



void client_thread(CTask* ctask);

int main(int argc, char *argv[]){

	if (argc < 5) {
		printf("ERROR,please enter [./client -h host -p port]\n");
		exit(1);
	}

	/* value var */ 
	char *ip = argv[2];
	int port = atoi(argv[4]);

	char buffer[MAXLen]; 
	char msg[MAXLen]; 
	int sockfd = 0;
	int numbytes = 0;


	const char * const delim = "\"";

	while(1){
		if(fgets(msg, sizeof(msg), stdin) != NULL){
			if(strlen(msg) >= 256){
				printf("you can only search string under size 255\n");
				memset(msg, '\0', strlen(msg)+1);
			}
			else{
				if(msg[strlen(msg)-1] == '\n')
					msg[strlen(msg)-1] = '\0';
				//if num of["] is even, and first of str is "Query "
				int count = 0;
				int index = 0;
				char* ret;

				char* dup_msg = malloc(strlen(msg));
				char* saveptr = NULL;
				char* substr = NULL;
			
				strcpy(dup_msg, msg);	
				substr = strtok_r(dup_msg, "\"", &saveptr);
				while((ret = strstr(msg+index, "\"")) != NULL){
					index = ret-msg+1;
					count ++;
				}
				if((count != 0) && (count % 2 == 0) && (strcmp(substr,"Query ") == 0) ){


					CTask* ctask = malloc(sizeof(struct CTask));
					ctask->str = malloc(strlen(msg)+1);

					strcpy(ctask->str,msg); 
					ctask->ip = ip;
					ctask->port = port;

					/* create a thread to handle query (write to server) */	
					pthread_t t;
					pthread_create(&t, NULL, (void*)client_thread, ctask);
				}
				else{
					printf("The string formate is not correct \n");
				}
				memset(msg, '\0', strlen(msg)+1);

			}
		}

	}


}
void client_thread(CTask* ctask){

	char* server_ip  = malloc(strlen(ctask->ip));
	strcpy(server_ip, ctask->ip);

	int server_port = ctask->port;

	int cli;
	cli = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);
	inet_pton(AF_INET,server_ip,&server_addr.sin_addr.s_addr);

	connect(cli,(struct sockaddr*)&server_addr,sizeof(server_addr));

	char buf [BUFSIZ];
	int ret,i;

	strcpy(buf, ctask->str);

	/* write, sleep, read, exit */
	write(cli,buf,strlen(buf));
	sleep(2);
	read(cli,buf,sizeof(buf));

	if(ctask->str[strlen(ctask->str)-1] == '\n')
		ctask->str[strlen(ctask->str)-1] = '\0';

	printf("%s\n",buf);

	close(cli);
	return ;
}


