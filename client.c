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
				printf("input msg : [%s]\n",msg);

				//cut str

				//char buf[30] = "Query \"test\" \"te\" \"e\" \"w\" ";
				char *substr = NULL;
				char *saveptr = NULL;
				int count = 0;
				substr = strtok_r(msg, delim, &saveptr);
				if(strcmp(substr,"Query ") == 0){
					substr = strtok_r(NULL, delim, &saveptr);
					do {
						printf("sub string : [%s]\n",substr);
						CTask* ctask = malloc(sizeof(struct CTask));
						ctask->str = malloc(strlen(substr)+1);

						strcpy(ctask->str,substr); 
						ctask->ip = ip;
						ctask->port = port;

						/* create a thread to handle query (write to server) */	
						pthread_t t;
						pthread_create(&t, NULL, (void*)client_thread, ctask);
						memset(msg, '\0', strlen(msg)+1);

						substr = strtok_r(NULL, delim, &saveptr);
						substr = strtok_r(NULL, delim, &saveptr);


					} while (substr);
				}
				else{
					printf("unformulated input\n");
				}


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


	printf("Query \"%s\"\n",ctask->str);
	printf("%s\n",buf);


	/*	while(1){
		memset(buf, '\0', sizeof(buf));

		fgets(buf,sizeof(buf),stdin);
		write(cli,buf,strlen(buf));   
		sleep(2);
		ret = read(cli,buf,sizeof(buf));
		printf("ret %s\n",buf);		
		memset(buf, '\0', strlen(buf));
		}*/
	close(cli);
	return ;
}


/*
   void client_thread(CTask* ctask){
//lock
char buffer[MAXLen];
ctask->sockfd = tcp_cli(ctask->ip,ctask->port,ctask->sockfd);
strcpy(buffer,ctask->str);
buffer[strlen(buffer)-1] = '\0';
printf("client 71G [%s]\n",buffer);


write(ctask->sockfd,buffer, strlen(buffer));
sleep(10);
read(ctask->sockfd,buffer, strlen(buffer)+1);
printf("msg from server %s\n",buffer);
//free(ctask);
pthread_exit(NULL);

}*/
