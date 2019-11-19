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
	printf("%d\n",*(int*)task);
	char *cnt = malloc(sizeof(char)*20); 
	task->fileN = malloc(sizeof(char)*255);
	memset(task->fileN, 0, sizeof(task->fileN));
	
	task = strDir(task);
	
	ans[k] = (int)(pthread_self()) % 1000;
	k ++;

	printf("count :%d\n",task->count);
	
	sprintf(cnt,"Count:%d",task->count);
	strcat(task->fileN,cnt);
	printf("str = %s\n", task->fileN);
	
}


int main(int argc, char* argv[]){
	

	char *c[5] = {"csdsd","test","t","te","w"};
	char *b[5] = {"jsdsd","nluot","g","e","i"};


	
	if(argc < 4){
		printf("you should enter ./ str dir");
		return -1;
	}
	printf("%s %s %s %s %s\n",c[0],c[1],c[2],c[3],c[4]);


    	int n = atoi(argv[1]);
	puts("Making threadpool with 4 threads");
	threadpool thpool = thpool_init(n);

/*
		char str[256];
		Task *task = malloc(sizeof(struct Task));
		//task->target = argv[2];
		task->target = fgets(str,255,stdin);
		task->dir = argv[3];*/

	puts("Adding 40 tasks to threadpool");
	int i;
//	while(1){
	for(i = 0;i < n;i++){
		char str[256];
		Task *task = malloc(sizeof(struct Task));
		task->target = c[i];
		task->dir = argv[3];

		thpool_add_work(thpool, (void*)task2, task);
		printf("-----------\n");
	}
	if(k != 0){
		int j = 0;
		for(j = 0; j < k;j++){
			printf("ans[%d] = %d\n",j,ans[j]);

		}
		k = j;
		printf("k = %d\n",k);
	}

	thpool_destroy(thpool);

	//	puts("Killing threadpool");
	//	thpool_destroy(thpool);

	return 0;
}
