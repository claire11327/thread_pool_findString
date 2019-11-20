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



	//	Job* job = malloc(sizeof(struct Job));
	//	job->port = atoi(argv[2]);	
	//	job->root = argv[1];	
	/*delete*/

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
//	cli = accept(sock,(struct sockaddr*)&client_addr,&cli_len);    
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
			printf("str :[%s]\n",str);
			memset(buf,0,n);
			readFileList(job->root, str, result);

			strcpy(buf,result);
			printf("server 64 %s\n",buf);
			write(cli,buf,strlen(buf));
			memset(buf,'\0',sizeof(buf));
			memset(result,'\0',strlen(result));
			printf("[%s]\n",buf);
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

/*void server_thread(Job* job){
	printf("port :%d  dir = %s\n",job->port, job->root);

	int sockfd = 0;
	char *buffer;	
	buffer = malloc(sizeof(char)*MAXLen);

	tcp_ser(job->port, sockfd);
}*/
