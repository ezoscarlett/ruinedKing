#include <stdio.h>

struct student{
	int num;
	int age;
	char name[16];
	struct student *next;
};
int parseline(char *line,struct student *ptr);
int readline(int fd, char* line, int length);
int load_file(char *filename,struct student **out);
void free_list(struct student *stu);
