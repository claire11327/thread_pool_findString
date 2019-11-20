#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "search.h"

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
	cli = accept(sock,(struct sockaddr*)&client_addr,&cli_len);    
	char buf[BUFSIZ];    
	char str[BUFSIZ];
	char result[BUFSIZ];
	memset(str,'\0',sizeof(str));
	memset(result,'\0',sizeof(result));
	int n,i;
	while(1){
		memset(buf,'\0',sizeof(buf));
		if(n = read(cli,buf,sizeof(buf)) >= 0){ 
			strcpy(str,buf);
			printf("str :%s\n",str);
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
	return 0;
}

