// need to do some basic operations done using calender 
#include<stdio.h>
#include<stdlib.h>

struct task
{
    struct date
    {
        int date;
        int hours;
        int minutes;
    };
    char content;
    struct task *prev;
    struct task *next;
}*start = NULL;

void main()
{
    printf(__DATE__);
    printf("\n");
    printf(__TIME__);
}
