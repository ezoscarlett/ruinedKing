#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <load.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s $num\n",argv[0]);
        return 0;
    }
    int i = 0;
    int count = 0;
	struct student *stu = NULL;
    struct student *ptr = NULL;
    load_file("info.txt",&stu,&count);

	int queryNum = atoi(argv[1]);

	for (i = 0; i < count; i++)
	{
		if (stu[i].num == queryNum)
		{
			printf("Number: %d, Age: %d, Name: %s\n", stu[i].num, stu[i].age, stu[i].name);
			return 0;
		}
	}
	printf("ID number not found");
    free(stu);
	return -1;
}
