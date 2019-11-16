#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "thpool.h"
#include "find_str.h"

//queue for ans
int ans[100];
int k = 0;

void task1(){
	printf("Thread #%u working on task1\n", (int)pthread_self());
}


void task2(Task *task){
	char *cnt = malloc(sizeof(char)*20); 
	task->fileN = malloc(sizeof(char)*255);
	memset(task->fileN, 0, sizeof(task->fileN));
	
	task = strDir(task);
	
	ans[k] = (int)(pthread_self()) % 1000;
	k ++;
	
	sprintf(cnt,"Count:%d",task->count);
	strcat(task->fileN,cnt);
	printf("str = %s\n", task->fileN);
	
}


int main(int argc, char* argv[]){
		
	if(argc < 4){
		printf("you should enter ./ str dir");
		return -1;
	}
//	char *result = strDir(argv[2],argv[3]);
//	printf("main result :%s\n",result);


    	int n = atoi(argv[1]);
	puts("Making threadpool with 4 threads");
	threadpool thpool = thpool_init(n);


	Task *task = malloc(sizeof(struct Task));
	task->target = argv[2];
	task->dir = argv[3];
	
	printf("target = %s\n",task->target);
	printf("dir = %s\n",task->dir);

	puts("Adding 40 tasks to threadpool");
	int i;
	for(i = 0;i < n;i++){
		thpool_add_work(thpool, (void*)task2, task);
	}
	if(k != 0){
		int j = 0;
		for(j = 0; j < k;j++){
			printf("ans[%d] = %d\n",j,ans[j]);

		}
		k = j;
		printf("k = %d\n",k);
	}



	//	puts("Killing threadpool");
	//	thpool_destroy(thpool);

	return 0;
}
