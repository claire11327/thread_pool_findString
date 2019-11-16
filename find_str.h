#ifndef _FIND_STR_
#define _FIND_STR_

typedef struct Task{
	char *target;
	char *dir;
	char *fileN;
	int  count;
}Task;



Task* strDir(Task *task);

#endif
