#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

//#define server_ip "127.0.0.1"
//#define server_port 7776

//int main(){
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
	printf("ctask copy to buf%s\n",ctask->str);

	/* write, sleep, read, exit */
	write(cli,buf,strlen(buf));
	sleep(2);
	read(cli,buf,sizeof(buf));

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
	return 0;
}


