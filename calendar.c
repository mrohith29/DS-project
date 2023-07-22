// need to do some basic operations done using calender 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct time
    {
        int month;
        int year;
        int Date;
        int hours;
        int minutes;
    };

struct task
{
    struct time *initial;
    char *content;
    struct task *prev;
    struct task *next;
}*start = NULL;

struct task *AddTask(struct task *start, int date, int month, int year, int hours, int min, char *theme)
{
    if(start == NULL)
    {
        struct task *newtask = (struct task *)malloc(sizeof(struct task));
        newtask->initial = (struct time *)malloc(sizeof(struct time));
        
    }
}


void main()
{

    int date, month, year, hours, min, option;
    char theme[100];  
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
            scanf("%d",&min);
            getchar();
            fgets(theme, sizeof(theme), stdin);
            printf("%d  %d  %d  %d  %d \n",date,month,year,hours,min);
            printf("%s\n",theme);
                start = AddTask(start, date, month, year, hours, min, theme);

            break;
        }
    }  
}
