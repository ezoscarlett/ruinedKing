#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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
    if(ptr2 != NULL)
    {
        *ptr2 = 0;
    }

	return 0;
}
int load_file(char *filename,struct student **out,int *num)
{
   	int fd = 0;
	fd = open(filename, O_RDONLY);
    char line[1024];
    int count = 0;
    struct student *list = NULL,*ptr = NULL;
	if(fd == -1)
	{
		printf("Unable to read info");
		return -1;
	}
    while(read(fd,line,1) == 1){
        if(*line == "\n")
        {
        	count++;
        }
    }
    *num = count;
    printf("there are %d line in %s\n",count,filename);
    lseek(fd, 0, SEEK_SET);

    ptr = list = calloc(1, sizeof(struct student));
    parseline(line, ptr);

    while(read(fd,line,1) != -1){
        //TODO parse the line
    	struct student *new = calloc(1, sizeof(struct student));
        parseline(line,new);
        ptr->next = new;
        ptr = ptr->next;
    }
    fclose(fd);
    *out = list;
    return 0;
}
