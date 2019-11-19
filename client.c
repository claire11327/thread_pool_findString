#include <stdio.h>
#include <stdlib.h>
#include "unicast_client.h"


int main(int argc, char *argv[]){

     if (argc < 5) {
         printf("ERROR,please enter [./client -h host -p port]\n");
         exit(1);
     }

	/* value var */ 
     char *ip = argv[2];
     int port = atoi(argv[4]);

     char buffer[256]; 
     int sockfd = 0;
     int numbytes = 0;

	/* connect to server */
     sockfd = tcp_cli(ip,port,sockfd);


	/* main thread needs to 1.get input, 2. read buffer */	
	/* get input string */
     while(1){
	if(fgets(buffer, sizeof(buffer), stdin) != NULL){
		printf("input msg : %s\n",buffer);

		/* create a thread to handle query (write to server) */	
		//write is function of thread
		// task > sockfd, buffer, string
		write(sockfd, buffer, strlen(buffer)+1);
		//memset

		/*  */
	









}

