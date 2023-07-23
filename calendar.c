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


struct task *TaskDelete(struct task *start, int date, int month, int year, int hours, int min)
{
    if(start == NULL)
    {
        printf("No task to delete\n");
        return NULL;
    }
    else if((year < start->initial->year || (year == start->initial->year && month < start->initial->month) ||
             (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours < start->initial->hours) ||
             (year == start->initial->year && month == start->initial->month && date < start->initial->Date) ||
             (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours == start->initial->hours && min < start->initial->minutes)))
             {
                start->prev = TaskDelete(start->prev, date, month, year, hours, min);
             }
    else if((year > start->initial->year || (year == start->initial->year && month > start->initial->month) ||
              (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours > start->initial->hours) ||
              (year == start->initial->year && month == start->initial->month && date > start->initial->Date) ||
              (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours == start->initial->hours && min > start->initial->minutes)))
    {
        start->next = TaskDelete(start->next, date, month, year, hours, min);
    }
    else
    {
        struct task *temp = start;

        if((start->prev == NULL) && (start->next == NULL))
        {
            free(start->initial);
            free(start->content);
            free(start);
            return NULL; 
        }
        else if(start->prev == NULL)
        {
            start = start->next;
            
        }
    }
}


void InOrderTraversal(struct task *root) {
    if (root != NULL) {
        InOrderTraversal(root->prev);
        printf("%d/%d/%d %02d:%02d - %s\n", root->initial->Date, root->initial->month, root->initial->year, root->initial->hours, root->initial->minutes, root->content);
        InOrderTraversal(root->next);
    }
}

struct task *TaskDisplay(struct task *start) {
    InOrderTraversal(start);
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
            TaskDisplay(start);
        break;

        case 3:
            TaskDelete(start, date, month, year, hours, min);
            break;

        case 5:
        exit(0);

        default:
        printf("Enter a Valid operation\n");
        break;
        }
    }
}
