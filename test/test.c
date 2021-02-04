#include <stdio.h>
struct student{
    int age;
    int num;
    char name[16];
}
void show(struct student a)
{
    printf("age = %d,name = %s,num = %d\n",a.age,a.name,a.num);
}
void show1(struct student *a){
    printf("age = %d,name = %s,num = %d\n",a->age,a->name,a->num);
}
int main()
{
    struct student a ;
    a.age = 20;
    a.num = 1;
    snprintf(a.name,sizeof(a.name),"%s","bob");
    show();
    show1();
}
