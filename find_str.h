#ifndef _FIND_STR_
#define _FIND_STR_

typedef struct Task{
	char *target;
	char *dir;
	char *fileN;
	int  count;
}Task;

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


Task* strDir(Task *task);

#endif
