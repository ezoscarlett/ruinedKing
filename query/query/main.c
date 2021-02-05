#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "load.h"

int main(int argc, char *argv[]){
    int count = 0;
	struct student *stu = NULL;
    char line[8];
    load_file("info.txt",&stu,&count);

	int queryNum = 0;
	struct student *result = NULL;//calloc(1, sizeof(struct student));
    while(1){
        printf("input the num you want search : ");
        fgets(line,sizeof(line),stdin);
        if(strlen(line)==0)
            continue;
        if(line[0] == 'q')
            break;
        queryNum = atoi(line);
    //    printf("num is %d\n",queryNum);
        result = search(stu, count, queryNum);
        if(result != NULL)
        {
            printf("Number: %d, Age: %d, Name: %s\n", result->num, result->age, result->name);
        }else{
            printf("ID number not found\n");
        }
    }
//    unload_file();
    free(stu);
	return -1;
}
