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
int readline(int fd, char* line, int length)
{
	char *head = line;
	while(read(fd, line, 1) == 1)
	{
		if(*line == '\n')
		{
			*line = 0;
			return 0;
		}
		line++;
	}
	if(head < line)
	{
		return 0;
	}
	return -1;
}
int load_file(char *filename,struct student **out)
{
   	int fd = 0;
	fd = open(filename, O_RDONLY);
    char line[1024];
    struct student *head = NULL,*tail = NULL;
	if(fd == -1)
	{
		printf("Unable to read info");
		return -1;
	}

    while(readline(fd,line,1024) != -1){
    	struct student *new = calloc(1, sizeof(struct student));
    	parseline(line,new);
    	if(head == NULL)
    	{
    		head = tail = new;
    	}
    	else
    	{
    		tail->next = new;
    		tail = new;
    	}
    }
    close(fd);
    *out = head;
    return 0;
}
void free_list(struct student *stu)
{
	struct student *mov;
	while(stu != NULL)
	{
		mov = stu;
		stu = mov->next;
		free(mov);
	}
}
