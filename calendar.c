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
    else if (year < start->initial->year ||
             (year == start->initial->year && month < start->initial->month) ||
             (year == start->initial->year && month == start->initial->month && date < start->initial->Date) ||
             (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours < start->initial->hours) ||
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

struct task *rightmin(struct task *start)
{
    struct task *current = start;
    while (current->prev != NULL)
    {
        current = current->prev;
    }
    return current;
}

struct task *TaskDelete(struct task *start, int date, int month, int year, int hours, int min)
{
    if (start == NULL)
    {
        printf("\n\n\t\t*******Sorry You Don't Have Any TASK to Delete on %d/%d/%d %02d:%02d******\t\t\n\n", date, month, year, hours, min);
        return NULL;
    }
    else if ((year < start->initial->year ||
              (year == start->initial->year && month < start->initial->month) ||
              (year == start->initial->year && month == start->initial->month && date < start->initial->Date) ||
              (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours < start->initial->hours) ||
              (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours == start->initial->hours && min < start->initial->minutes)))
    {
        start->prev = TaskDelete(start->prev, date, month, year, hours, min);
    }
    else if ((year > start->initial->year ||
              (year == start->initial->year && month > start->initial->month) ||
              (year == start->initial->year && month == start->initial->month && date > start->initial->Date) ||
              (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours > start->initial->hours) ||
              (year == start->initial->year && month == start->initial->month && date == start->initial->Date && hours == start->initial->hours && min > start->initial->minutes)))
    {
        start->next = TaskDelete(start->next, date, month, year, hours, min);
    }
    else
    {
        struct task *temp = start;

        if ((start->prev == NULL) && (start->next == NULL))
        {
            free(start->initial);
            free(start->content);
            free(start);
            return NULL;
        }
        else if (start->prev == NULL)
        {
            start = start->next;
            free(temp->content);
            free(temp->initial);
            free(temp);
            return start;
        }
        else if (start->next == NULL)
        {
            start = start->prev;
            free(temp->content);
            free(temp->initial);
            free(temp);
            return start;
        }
        else
        {
            struct task *Rightmin = rightmin(start->next);
            start->initial->Date = Rightmin->initial->Date;
            start->initial->month = Rightmin->initial->month;
            start->initial->year = Rightmin->initial->year;
            start->initial->hours = Rightmin->initial->hours;
            start->initial->minutes = Rightmin->initial->minutes;
            start->content = realloc(start->content, strlen(Rightmin->content) + 1);
            strcpy(start->content, Rightmin->content);
            start->next = TaskDelete(start->next, Rightmin->initial->Date, Rightmin->initial->month, Rightmin->initial->year, Rightmin->initial->hours, Rightmin->initial->minutes);
            return start;
        }
    }
}

void InOrderTraversal(struct task *start)
{
    if (start != NULL)
    {
        InOrderTraversal(start->prev);
        printf("%d/%d/%d %02d:%02d - %s\n", start->initial->Date, start->initial->month, start->initial->year, start->initial->hours, start->initial->minutes, start->content);
        InOrderTraversal(start->next);
    }
}

struct task *TaskDisplay(struct task *start)
{
    InOrderTraversal(start);
    return start;
}

void main()
{

    int date, month, year, hours, min, option;
    char theme[10000];
    while (1)
    {
        printf("WELCOME TO OUR CALENDAR APPLICATION\n\n");
        printf("please select the service you want\n\
                ***PRESS 1*** to add task\n\
                ***PRESS 2*** to display your tasks\n\
                ***PRESS 3*** to delete any task\n\n\n");
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
            printf("Please enter the DATE on which you want to schedule\n");
            scanf("%d", &date);
            printf("Please enter the MONTH(in number i.e., 1-12) on which you want to schedule\n");
            scanf("%d", &month);
            printf("Please enter the YEAR(in format xxxx) on which you want to schedule\n");
            scanf("%d", &year);
            printf("Please enter the HOURS at which you want to schedule\n");
            printf("***please use 24 hours clock time(i.e., 0-23)***\n");
            scanf("%d", &hours);
            printf("Please enter the MINUTES(i.e., 0-59) at which you want to schedule\n");
            scanf("%d", &min);
            getchar();
            printf("please enter the TASK to schedule at the provided time\n");
            fgets(theme, sizeof(theme), stdin);
            start = AddTask(start, date, month, year, hours, min, theme);
            printf("\t\t******TASK SCHEDULED SUCCESSFULLY******\t\t\n\n");
            break;

        case 2:
            TaskDisplay(start);
            if (start == NULL)
            {
                printf("\n\n\t\t***Sorry, You Don't Have Any Tasks scheduled to Display***\n\n");
            }
            else
            {
                printf("\t\t****YOUR LIST OF TASKS ARE****\t\t\n");
            }
            break;

        case 3:
            printf("Please enter the DATE of task to delete\n");
            scanf("%d", &date);
            printf("Please enter the MONTH(in number i.e., 1-12) of task to delete\n");
            scanf("%d", &month);
            printf("Please enter the YEAR(in format xxxx) of task to delete\n");
            scanf("%d", &year);
            printf("Please enter the HOURS of task to delete\n");
            printf("***please use 24 hours clock time(i.e., 0-23)***\n");
            scanf("%d", &hours);
            printf("Please enter the MINUTES(i.e., 0-59) of task to delete\n");
            scanf("%d", &min);
            start = TaskDelete(start, date, month, year, hours, min);
            break;

        case 5:
            exit(0);

        default:
            printf("Enter a Valid operation\n");
            break;
        }
    }
}
