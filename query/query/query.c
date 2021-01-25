#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
	int num;
	int age;
	char name[16];
};
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
	int *lineNum = atoi(token);
	ptr->num = lineNum;

	token = strtok(line, delim);
	if(atoi(token) == 0)
	{
		printf("Invalid age");
		return -1;
	}
	int *lineAge = atoi(token);
	ptr->age = lineAge;

	token = strtok(line, delim);
	strcpy(ptr->name, token);
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
    
    ptr = list = calloc(count,sizeof(struct student));//calloc equal to malloc and memset

    while(fgets(line,1024,fp)!=NULL){
        //TODO parse the line
        parseline(line,ptr);
        ptr++;
    }
    fclose(fp); //must close fp when read finish
    *out = list;
    return 0;
}
int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage: %s $num\n",argv[0]);
        return 0;
    }
    int i = 0;
    int count = 0;
	struct student *stu = NULL;
    load_file("info.txt",&stu,&count);
	for (i = 0; i < count; i++){
        printf("stu = %d %d %s\n",stu->num,stu->age,stu->name);
        stu++;
    }
/*#if 0
	int i;
	for (i = 0; i < 6; i++)
	{
		int res = fscanf(fp, "%d %d %s\n", &stu[i].num, &stu[i].age, stu[i].name);
		if(res == -1)
		{
			fclose(fp);
			break;
		}
	}
#endif*/
	int queryNum = atoi(argv[1]);
	if(queryNum > 5)
	{
		printf("Query number out of range");
		return -1;
	}
	printf("Number: %d, Age: %d, Name: %s", stu[queryNum-1].num, stu[queryNum-1].age, stu[queryNum-1].name);
	return 0;
}
