#ifndef _FIND_STR_
#define _FIND_STR_

typedef struct Task{
	char *target;
	char *dir;
	char *fileN;
	char *buffer;
	int  count;
	int  sockfd;
}Task;



Task* strDir(Task *task);



/*
typedef struct DoneTask{
	char *ans;
	struct DoneTask* next;
}DT;

typedef struct DoneTaskQueue{
	int DTQcnt;
	struct DoneTask* head;
	struct DoneTask* tail;
}DTQ;
	
*/	

#endif
