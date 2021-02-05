#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"

int parseline(char *line,struct student *ptr)
{
	char delim[] = " ";
	char* token;
	token = strtok(line, delim);
	if(atoi(token) == 0)
	{
		printf("Invalid ID number");
		return -1;
	}
	ptr->num = atoi(token);

	token = strtok(NULL, delim);
	if(atoi(token) == 0)
	{
		printf("Invalid age");
		return -1;
	}
	ptr->age = atoi(token);

	token = strtok(NULL, delim);
	strncpy(ptr->name, token, strlen(token));
    char *ptr2 = strstr(ptr->name,"\n");
    if(ptr2)
        *ptr2 = 0;
	return 0;
}
int load_file(char *filename,struct student **out,int *num)
{
   	FILE *fp = fopen(filename, "r");
    char line[1024];//
    int count = 0;
    struct student *list = NULL,*ptr = NULL;
	if(fp == NULL)
	{
		printf("Unable to read info");
		return -1;
	}
    while(fgets(line,1024,fp)!=NULL){
        count++;
    }
    *num = count;
    printf("there are %d line in %s\n",count,filename);
    fseek(fp, 0L, SEEK_SET);//rewind the fp

    ptr = list = calloc(1, sizeof(struct student));
    parseline(line, ptr);

    while(fgets(line,1024,fp)!=NULL){
        //TODO parse the line
    	struct student *new = calloc(1, sizeof(struct student));
        parseline(line,new);
        ptr->next = new;
        ptr = ptr->next;
    }
    fclose(fp); //must close fp when read finish
    *out = list;
    return 0;
}
