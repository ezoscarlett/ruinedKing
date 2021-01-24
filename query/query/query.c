#include <stdio.h>
#include <stdlib.h>

struct student{
	int num;
	int age;
	char *name;
};

int main(int argc, char *argv[]){
	FILE *fp = fopen("info.txt", "r");
	if(fp == NULL)
	{
		printf("Unable to read info");
		return -1;
	}
	struct student stu[6];
	int i;
	for (i = 0; i < 6; i++)
	{
		int res = fscanf(fp, "%d %d %s", stu[i].num, stu[i].age, stu[i].name);
		if(res == -1)
		{
			fclose(fp);
			break;
		}
	}

	int queryNum = atoi(argv[1]);
	if(queryNum > 5)
	{
		printf("Query number out of range");
		return -1;
	}
	printf("Number: %d, Age: %d, Name: %s", stu[queryNum-1].num, stu[queryNum-1].age, stu[queryNum-1].name);
	return 0;
}
