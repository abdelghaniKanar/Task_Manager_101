#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Define the date structure to be used as a nested structure.
typedef struct
{

    int day, month, year;

} date;

//Define the main structure "task"
typedef struct
{
    char title[25]; //25 characters for title, it's enough!!!

    char description[350]; //Expect the description to contain 350 characters or fewer

    char priority[25]; //High or low.

    date dueDate; //The dueDate is the date on which the user expects this task to be completed

} task;

//Declaring the Global Variables
int taskListLength, cheker = 0;
task tasks[];


//Declaring the "menu" function
void menu();

//Declaring the "addTask" function
void addTask();

//Declaring the "displayTask" function
void displayTask();

//Declaring the "filter" function to be used within "displayTask" for full display features
void filter();

//Declaring the "updateTask" function
void updateTask();

//Declaring the "deleteTask" function
void deleteTask();

int main()
{
    printf("###################################################\n");
    printf("############### Task Manager 101' #################\n");
    printf("###################################################\n");

    menu();

    return 0;
}

//Define the "menu" function
void menu()
{
    char choice;

    do
    {
        printf("\n------------------ Control Menu -------------------\n");
        printf("------------ You Had One Choice to Make -----------\n");
        //Possible options
        printf("\n'A' or 'a': Add a new task.\n");
        printf("'D' or 'd': View your tasks.\n");
        printf("'U' or 'u': Update an existing task.\n");
        printf("'R' or 'r': Remove a task from your list.\n");
        printf("'O' or 'o': Exit the application.\n");
        printf("\nPlease enter your choice: ");
        scanf("%s", &choice);

        //Here is the verification section to verify the user's chosen option
        switch (toupper(choice))
        {

        case 'A':
            if(cheker == 0)
            {

                printf("\nOops! We still work on this section!\n");

            }
            break;

        case 'D':
            if(cheker == 0)
            {

                printf("\nOops! There is no task to display!\n");

            }
            break;

        case 'U':
            if(cheker == 0)
            {

                printf("\nOops! There is no task to update!\n");

            }
            break;

        case 'R':
            if(cheker == 0)
            {

                printf("\nOops! There is no task to remove!\n");

            }
            break;

        case 'O':
            break;


        }

    }
    while ( choice != 'o' );

}
