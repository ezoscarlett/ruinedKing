#include <stdio.h>
#include <stdlib.h>

struct student{
	int num;
	int age;
	char *name;
};

struct student query(int num){
	struct student out;

	return out;
}

int main(){
	int queryNum;
	struct student result;
	printf("Please enter ID number:");
	fgets(queryNum, stdin);
	result = query(queryNum);
	
}
