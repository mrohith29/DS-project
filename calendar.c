// need to do some basic operations done using calender 
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int option;
    while(1)
    {
        scanf("%d",&option);
        switch(option)
        {
            case 1:
            add();
            break;

            case 2:
            search();
            break;

            case 3:
            exit(0);

            default:
            printf("Please Select Appropriate Service\n");
        }
    }
}