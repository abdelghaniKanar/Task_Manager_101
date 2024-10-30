#include <stdio.h>
#include <stdlib.h>

//Define the date structure to be used as a nested structure.
typedef struct {

    int day, month, year;

}date;

//Define the main structure "task".
typedef struct {

    char title[25]; //25 characters for title, I think it's enough.

    char description[350]; //I expect that the description should contain 350 characters or less.

    char priority[25]; //high or low.

    date dueDate; //The dueDate is the date on which the user expects this task to be completed.

}task;

//Define the "menu" function
void menu();

//Define the "addTask" function
void addTask();

//Define the "displayTask" function
void displayTask();

//Define the "filter" function to be used within "displayTask" for full display features.
void filter();

//Define the "updateTask" function
void updateTask();

//Define the "deleteTask" function
void deleteTask();

int main()
{

    printf("---------------------------------------------------\n");
    printf("--------------- Task Manager 101' -----------------\n");
    printf("---------------------------------------------------\n");

    return 0;
}
