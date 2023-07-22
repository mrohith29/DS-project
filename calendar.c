// need to do some basic operations done using calender
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} *start = NULL;

struct task *AddTask(struct task *start, int date, int month, int year, int hours, int min, char *theme)
{
    if (start == NULL)
    {
        struct task *newtask = (struct task *)malloc(sizeof(struct task));
        newtask->initial = (struct time *)malloc(sizeof(struct time));
        newtask->initial->Date = date;
        newtask->initial->hours = hours;
        newtask->initial->minutes = min;
        newtask->initial->month = month;
        newtask->initial->year = year;
        newtask->content = (char *)malloc(strlen((theme) + 1) * sizeof(char));
        strcpy(newtask->content, theme);
        newtask->next = newtask->prev = NULL;
        return newtask;
    }
    else if (year < start->initial->year || (year == start->initial->year && month < start->initial->month) ||
             (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours < start->initial->hours) ||
             (year == start->initial->year && month == start->initial->month && date < start->initial->Date) ||
             (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours == start->initial->hours && min < start->initial->minutes))
    {
        start->prev = AddTask(start->prev, date, month, year, hours, min, theme);
    }
    else
    {
        start->next = AddTask(start->next, date, month, year, hours, min, theme);
    }

    return start;
}

void main()
{

    int date, month, year, hours, min, option;
    char theme[10000];
    while (1)
    {
        printf("*****TODAY'S DATE   ");
        printf(__DATE__);
        printf("******");
        printf("\n");
        printf("*****NOW TIME IS    ");
        printf(__TIME__);
        printf("*****\n");

        scanf("%d", &option);
        switch (option)
        {
        case 1:
            scanf("%d", &date);
            scanf("%d", &month);
            scanf("%d", &year);
            scanf("%d", &hours);
            scanf("%d", &min);
            getchar();
            fgets(theme, sizeof(theme), stdin);
            // printf("%d  %d  %d  %d  %d \n", date, month, year, hours, min);
            // printf("%s\n", theme);
            // theme[strcspn(theme, "\n")] = '\0'; 
            start = AddTask(start, date, month, year, hours, min, theme);
            break;

        case 2:
        exit(0);

        default:
        printf("Enter a Valid operation\n");
        break;
        }
    }
}
