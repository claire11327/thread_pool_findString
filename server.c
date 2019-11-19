#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "thpool.h"
#include "find_str.h"
#include "unicast_server.h"


void task2(Task *task);

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

	/* get socketfd */
     sockfd = tcp_ser(port, sockfd);

	/* create pool */
     threadpool thpool = thpool_init(n);

     while(1){
	     if(numbytes = read(sockfd, buffer, sizeof(buffer)) != 0){

		     /* create job */
		     Task *task = malloc(sizeof(struct Task));
		     task->target = malloc(strlen(buffer)+1);
		     strcpy(task->target ,buffer);
		     task->dir = root;
		     task->sockfd = sockfd;
		     task->buffer = buffer;
		     printf("t->bu: %s\n",task->buffer);

		     /* get string and add to pool */
		     thpool_add_work(thpool, (void*)task2, task);
		     memset(buffer, 0, strlen(buffer)+1);
	     }
     }











     printf("%s\n",buffer);


}

void task2(Task *task){
	printf("buffer %s\n",task->buffer);
	printf("target %s\n",task->target);

	/* malloc to store result & clear */
	task->fileN = malloc(sizeof(char)*255);
	memset(task->fileN, 0, sizeof(task->fileN));

	/* find str */
	task = strDir(task);

	printf("str = %s\n", task->fileN);
	strcpy(task->buffer, task->fileN);
	
	
	write(task->sockfd, task->buffer, strlen(task->fileN));
	printf("tas->buffer : %s\n",task->buffer);

}

