#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#include <load.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s $num\n",argv[0]);
        return 0;
    }
    int i = 0;
    int count = 0;
	struct student *stu = NULL;
    load_file("info.txt",&stu,&count);

	int queryNum = atoi(argv[1]);
	struct student result = search(stu, count, queryNum);
	if(result != NULL)
	{
		printf("Number: %d, Age: %d, Name: %s\n", result[i].num, result[i].age, result[i].name);
		return 0;
	}

	printf("ID number not found");
    free(stu);
	return -1;
}
