#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "search.h"
#include "load.h"

int main(int argc, char *argv[]){
	struct student *stu = NULL;
    char line[8];
    load_file("info.txt",&stu);

	int queryNum = 0;
	struct student *result = NULL;
    while(1){
        printf("Input the number you want to search: ");
        int n_read = read(STDIN_FILENO, line, sizeof(line));
        if(n_read < 0)
        {
        	printf("Input error");
        	return -1;
        }
        if(strlen(line)==0)
            continue;
        if(line[0] == 'q')
            break;
        queryNum = atoi(line);

        result = search(stu, queryNum);
        if(result != NULL)
        {
            printf("Number: %d, Age: %d, Name: %s\n", result->num, result->age, result->name);
        }else{
            printf("ID number not found\n");
        }
    }
//
    free_list(stu);
	return -1;
}
