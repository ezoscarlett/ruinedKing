#include <stdio.h>

struct student{
	int num;
	int age;
	char name[16];
	struct student *next;
};
int parseline(char *line,struct student *ptr);
int load_file(char *filename,struct student **out,int *num);
