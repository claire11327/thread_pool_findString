#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>

#include "thpool.h"
#include "search.h"
#define MAXLen 1024
#define server_ip "127.0.0.1"   

typedef struct Job{
	char* root;
	int port;
}Job;


//int main(){
void server_thread(Job* job){
	//int main(int argc, char**argv){

	const char * const delim = "\"";

	int server_sport = job->port;	

	int sock,cli;
	sock = socket(AF_INET,SOCK_STREAM,0); 
	struct sockaddr_in server_addr,client_addr;         

	server_addr.sin_family = AF_INET;   
	server_addr.sin_port = htons(server_sport);
	inet_pton(AF_INET,server_ip,&server_addr.sin_addr.s_addr);


	bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));


	listen(sock,20);

	socklen_t cli_len = sizeof(client_addr);
	char buf[BUFSIZ];    
	char str[BUFSIZ];
	char result[BUFSIZ];
	memset(str,'\0',sizeof(str));
	memset(result,'\0',sizeof(result));
	int n,i;
	while(1){
		cli = accept(sock,(struct sockaddr*)&client_addr,&cli_len);    
		memset(buf,'\0',sizeof(buf));
		if(n = read(cli,buf,sizeof(buf)) >= 0){ 
			strcpy(str,buf);
			if(str[strlen(str)-1]=='\n')
				str[strlen(str)-1] = '\0';
			memset(buf,0,n);

			//cut str
			memset(buf,'\0',sizeof(buf));
			printf("%s\n", str);

			char *saveptr = NULL;
			char *substr = NULL;
			int count = 0;

			substr = strtok_r(str, delim, &saveptr);
			if(strcmp(substr,"Query ") == 0){
				substr = strtok_r(NULL, delim, &saveptr);
				do{
					readFileList(job->root, substr, result);
					strcat(buf,result);
					memset(result,'\0',strlen(result));
					substr = strtok_r(NULL, delim, &saveptr);
					substr = strtok_r(NULL, delim, &saveptr);
				}while(substr);


			}
			write(cli,buf,strlen(buf));
			memset(buf,'\0',sizeof(buf));
			memset(result,'\0',strlen(result));
			n = 0;
		}

	}
	close(sock);
	close(cli);
}



void server_thread(Job* job);

int main(int argc, char *argv[]){

	if (argc < 7) {
		printf("ERROR,please enter [./server -r root -p port -n n]\n");
		exit(1);
	}

	/* set var value */	
	char *root = argv[2];
	int port = atoi(argv[4]);
	int n = atoi(argv[6]);

	int sockfd = 0;
	char buffer[256];

	int numbytes = 0;


	/* creat Job */
	Job* job = malloc(sizeof(struct Job));
	job->port = port;
	job->root = malloc(strlen(root));
	strcpy(job->root,root);



	/* create pool */
	threadpool thpool = thpool_init(n);
	thpool_add_work(thpool, (void*)server_thread, job);

	while(1){}


}

