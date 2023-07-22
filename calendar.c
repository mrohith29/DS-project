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

struct task *AddTask()
{

}


void main()
{

    int date, month, year, hours, minutes, option; 
    while(1)
    {
        printf("*****TODAY'S DATE   ");
        printf(__DATE__);
        printf("******");
        printf("\n");
        printf("*****NOW TIME IS    ");
        printf(__TIME__);
        printf("*****\n");

        scanf("%d",&option);
        switch(option)
        {
            case 1: 
            scanf("%d",&date);
            scanf("%d",&month);
            scanf("%d",&year);
            scanf("%d",&hours);
            scanf("%d",&minutes);
                start = AddTask(start, date, hours, minutes);

            break;
        }


    }

    
}
