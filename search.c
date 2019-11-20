#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "search.h"
int countStr(char *filepath, char* str);
char* readFileList(char *basePath, char* str, char* result);
char* readFileList(char *basePath, char* str, char* result)
{
	DIR *dir;
	int c = 0;
	int size_str = 0;
	struct dirent *ptr;
	char base[1000];
	char filepath[1000];
	char cnt[100];

	memset(filepath,'\0',sizeof(filepath));
	memset(cnt,'\0',sizeof(cnt));

	if(strlen(result) == 0){
		strcpy(result, "String: \"");
		strcat(result, str);
		strcat(result, "\"\n");
		size_str = strlen(result);
	}

	if ((dir=opendir(basePath)) == NULL)
	{
		perror("Open dir error...");
		exit(1);
	}

	while ((ptr=readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
			continue;
		else if(ptr->d_type == 8){    ///file
			strcpy(filepath,basePath);
			strcat(filepath,"/");
			strcat(filepath,ptr->d_name);
			if((c= countStr(filepath,str)) != 0)	{
				strcat(result, "File: ./");
				strcat(result, filepath);
				sprintf(cnt, ", Count:%d\n",c);
				strcat(result, cnt);
			}
		}
		else if(ptr->d_type == 10){    ///link file
			strcpy(filepath,basePath);
			strcat(filepath,"/");
			strcat(filepath,ptr->d_name);
			if((c = countStr(filepath,str)) != 0)	{
				strcat(result, "File: ./");
				strcat(result, filepath);
				sprintf(cnt, ", Count:%d\n",c);
				strcat(result, cnt);

			}
		}
		else if(ptr->d_type == 4)    ///dir
		{
			memset(base,'\0',sizeof(base));
			strcpy(base,basePath);
			strcat(base,"/");
			strcat(base,ptr->d_name);
			readFileList(base,str,result);
		}
	}
	if(strlen(result)==size_str){
		strcat(result, "Not found\n" );
	}
	return result;
	closedir(dir);
}


int countStr(char *filepath, char* str){

	int count = 0;
	char content[1000];
	memset(content,'\0',sizeof(content));
	FILE *fp = fopen(filepath, "r");

	if(fp == NULL){
		perror("open file fail:");
		return 0;
	}
	while(fgets(content,1000, fp) != NULL){
		int index = 0;
		char *ret;
		while((ret = strstr(content+index, str)) != NULL){
			count ++;
			index = ret-content +1;

		}
	}
	return count;
}


/*
   int main(int argc, char **argv)
   {
   DIR *dir;
   char basePath[1000];
   char result[1000];
   char str[1000];

///get the current absoulte path
memset(basePath,'\0',sizeof(basePath));
memset(result,'\0',sizeof(result));
memset(str,'\0',sizeof(str));

strcpy(basePath, argv[1]);

fgets(str, 1000, stdin);
if(str[strlen(str)-1] == '\n'){
str[strlen(str)-1] = '\0';
}

readFileList(basePath, str, result);
printf("the is : [%s]\n",result);
return 0;
}*/
