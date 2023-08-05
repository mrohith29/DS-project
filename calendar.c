// need to do some basic operations done using calender.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define B_RED "\033[41m"
#define B_GREEN "\033[42m"
#define B_YELLOW "\033[43m"
#define B_BLUE "\033[44m"
#define B_MAGENTA "\033[45m"
#define B_CYAN "\033[46m"
#define B_WHITE "\033[47m"

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
                \033[32m***PRESS 1*** to add task\n\033[0m\
                \033[34m***PRESS 2*** to display your tasks\n\033[0m\
                \033[31m***PRESS 3*** to delete any task\n\n\n\033[0m");
        printf(RESET);
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
            system("cls");
            printf("Please enter the MONTH(in number i.e., 1-12) on which you want to schedule\n");
            scanf("%d", &month);
            system("cls");
            printf("Please enter the YEAR(in format xxxx) on which you want to schedule\n");
            scanf("%d", &year);
            system("cls");
            printf("Please enter the HOURS at which you want to schedule\n");
            printf("***please use 24 hours clock time(i.e., 0-23)***\n");
            scanf("%d", &hours);
            system("cls");
            printf("Please enter the MINUTES(i.e., 0-59) at which you want to schedule\n");
            scanf("%d", &min);
            system("cls");
            getchar();
            printf("please enter the TASK to schedule at the provided time\n");
            fgets(theme, sizeof(theme), stdin);
            system("cls");
            start = AddTask(start, date, month, year, hours, min, theme);
            printf(B_GREEN);
            printf("\t\t******TASK SCHEDULED SUCCESSFULLY******\t\t\n\n");
            printf(RESET);
            break;

        case 2:
            if (start == NULL)
            {
                printf(B_YELLOW);
                printf("\n\n\t\t***Sorry, You Don't Have Any Tasks scheduled to Display***\n\n");
                printf(RESET);
            }
            else
            {
                printf(B_GREEN);
                printf("\t\t****YOUR LIST OF TASKS ARE****\t\t\n");
                printf(RESET);
                TaskDisplay(start);
            }
            break;

        case 3:
            printf(GREEN);
            printf("Please enter the DATE of task to delete\n");
            printf(RESET);
            scanf("%d", &date);
            system("cls");
            printf(GREEN);
            printf("Please enter the MONTH(in number i.e., 1-12) of task to delete\n");
            printf(RESET);
            scanf("%d", &month);
            system("cls");
            printf(GREEN);
            printf("Please enter the YEAR(in format xxxx) of task to delete\n");
            printf(RESET);
            scanf("%d", &year);
            system("cls");
            printf(GREEN);
            printf("Please enter the HOURS of task to delete\n");
            printf("***please use 24 hours clock time(i.e., 0-23)***\n");
            printf(RESET);
            scanf("%d", &hours);
            system("cls");
            printf(GREEN);
            printf("Please enter the MINUTES(i.e., 0-59) of task to delete\n");
            printf(RESET);
            scanf("%d", &min);
            system("cls");
            start = TaskDelete(start, date, month, year, hours, min);
            break;

        case 5:
            exit(0);

        default:
            system("cls");
            printf(RED);
            printf("Enter a Valid operation\n");
            printf(RESET);
            break;
        }
    }
}
