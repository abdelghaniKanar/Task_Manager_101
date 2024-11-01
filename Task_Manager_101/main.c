#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//colors
#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_WHITE "\x1b[37m"


//Declaring the Global Variables

//Using `LIST_LENGTH` with a default value of 100 to allow handling 100 tasks as maximum
//If the application needs to manage more tasks, consider using dynamic memory allocation to adjust the array size
//At the moment, it's not an important part of the code
#define LIST_LENGTH 3
#define TITLE_LENGTH 25
#define DESCRIPTION_LENGTH 350

//checker is used to verify if any tasks have been added
int checker = 0;
char singleTask[4];
int numberTasks;


//Define the date structure to be used as a nested structure.
typedef struct
{

    int day, month, year;

} date;

//Define the main structure "task"
typedef struct
{
    char title[TITLE_LENGTH]; //25 characters for title, it's enough!!!

    char description[DESCRIPTION_LENGTH]; //Expect the description to contain 350 characters or fewer

    char priority[4]; //High or low.

    date dueDate; //The dueDate is the date on which the user expects this task to be completed

} task;

//Declaring an array of task
task tasks[LIST_LENGTH];


//Declaring the "menu" function
void menu();

//Declaring the "addTask" function
void addTask();
void addMultiTasks(int numberTasks);

//Declaring the "displayTask" function
void displayTask(int checker, task tasks[]);

//Declaring the "filter" function to be used within "displayTask" for full display features
//void filter();

//Declaring the "updateTask" function
void updateTask(int checker, task tasks[]);

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

//'menu' function controls user actions
void menu()
{
    char choice;

    do
    {
        printf("\n---------------------------------------------------");
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
            //manupulating addTask function
            //If 'checker' less then LIST_LENGTH
            if(checker < LIST_LENGTH)
            {
                do
                {

                    printf("\nDo you want to add one or more tasks?\nEnter \"one\" or \"more\": ");
                    scanf("%s", &singleTask);

                    strcpy(singleTask, strupr(singleTask));

                    if(strcmp(singleTask, "ONE") != 0 && strcmp(singleTask, "MORE") != 0)
                    {

                        printf("%s\nYou enter invalid value!!!\n%s", AC_RED, AC_WHITE);

                    }
                    else if(strcmp(singleTask, "ONE") == 0)
                    {

                        addTask();

                    }
                    else if(strcmp(singleTask, "MORE") == 0)
                    {
                        do
                        {

                            printf("\nHow many tasks would you like to add?\n(Limit is %d): ", (LIST_LENGTH - checker));
                            scanf("%d", &numberTasks);

                        }
                        while((LIST_LENGTH - checker) < numberTasks);


                        addMultiTasks(numberTasks);


                    }

                }
                while(strcmp(singleTask, "ONE") != 0 && strcmp(singleTask, "MORE") != 0);

            }
            else
            {

                printf("%s\nThe maximum limit has been reached!!!\n%s", AC_RED, AC_WHITE);

            }
            break;

        case 'D':
            if(checker == 0)
            {

                printf("%s\nOops! There is no task to display!\n%s", AC_RED, AC_WHITE);


            }
            else
            {

                displayTask(checker, tasks);

            }
            break;

        case 'U':
            if(checker == 0)
            {

                printf("%s\nOops! There is no task to update!\n%s", AC_RED, AC_WHITE);

            }
            else
            {

                updateTask(checker, tasks);

            }
            break;

        case 'R':
            if(checker == 0)
            {

                printf("%s\nOops! There is no task to remove!\n%s", AC_RED, AC_WHITE);

            }
            break;

        case 'O':
            break;


        }

    }
    while (toupper(choice) != 'O');

}

//'addTask' function is responsible for receiving user inputs for task details and validating these inputs
void addTask()
{
    int inputChecker;
    printf("\n---------------------------------------------------");
    printf("\n-------- Welcome! to the add task section ---------");
    printf("\n------------------- Task Number %d -----------------\n", checker + 1);

    do
    {
        printf("\nPlease enter this task title (only 25 char): ");
        scanf(" %[^\n]", &tasks[checker].title);
        inputChecker = strlen(tasks[checker].title);

        if (inputChecker > TITLE_LENGTH)
        {
            printf("%s\nThe title must be 25 characters or fewer!%s", AC_RED, AC_WHITE);
        }

    }
    while(inputChecker > TITLE_LENGTH);


    do
    {

        printf("Please enter %s\'s task description:\n", tasks[checker].title);
        scanf(" %[^\n]", &tasks[checker].description);
        inputChecker = strlen(tasks[checker].description);

        if (inputChecker > DESCRIPTION_LENGTH)
        {
            printf("%s\nThe description must be 350 characters or fewer!%s", AC_RED, AC_WHITE);
        }

    }
    while(inputChecker > DESCRIPTION_LENGTH);

    do
    {

        printf("\nPlease enter %s\'s task priority (low or high): ", tasks[checker].title);
        scanf(" %[^\n]", &tasks[checker].priority);

        if(strcmp(strupr(tasks[checker].priority), "LOW") != 0 && strcmp(strupr(tasks[checker].priority), "HIGH") != 0)
        {
            inputChecker = 1;
            printf("%s\nThe task priority must be (low or high)!\n%s", AC_RED, AC_WHITE);

        }
        else inputChecker = 0;

    }
    while(inputChecker);


    bool leap;
    printf("\nPlease enter %s\'s task due date:\n", tasks[checker].title);

    do
    {

        printf("Enter a valid year: ");
        scanf("%d", &tasks[checker].dueDate.year);
        //A leap year contains 366 days
        if(tasks[checker].dueDate.year >= 2024)
        {

            if(tasks[checker].dueDate.year % 4 == 0)
            {

                if((tasks[checker].dueDate.year % 100 == 0) && (tasks[checker].dueDate.year % 400 == 0))
                {

                    leap = true;

                }
                else if((tasks[checker].dueDate.year % 100 == 0) && (tasks[checker].dueDate.year % 400 != 0))
                {

                    leap = false;

                }
                else
                {

                    leap = true;

                }



            }
            else
            {

                leap = false;

            }

            inputChecker = 0;

        }
        else
        {

            inputChecker = 1;
            printf("%s\nThe year must be 2024 or later!\n\n%s", AC_RED, AC_WHITE);

        }

    }
    while(inputChecker);


    do
    {

        printf("Enter a valid month: ");
        scanf("%d", &tasks[checker].dueDate.month);
        if(tasks[checker].dueDate.month >= 1 && tasks[checker].dueDate.month <= 12)
        {

            inputChecker = 0;

        }
        else
        {
            inputChecker = 1;
            printf("%s\nThe month must be between 1 and 12!\n\n%s", AC_RED, AC_WHITE);
        }

    }
    while(inputChecker);




    do
    {

        printf("Enter a valid day: ");
        scanf("%d", &tasks[checker].dueDate.day);

        switch(tasks[checker].dueDate.month)
        {

        case 1:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 31)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 31!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 2:

            if(leap == true)
            {

                if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 29)
                {

                    inputChecker = 0;

                }
                else
                {
                    inputChecker = 1;
                    printf("%s\nThe day must be between 1 and 29!\n\n%s", AC_RED, AC_WHITE);
                }

            }
            else
            {

                if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 28)
                {

                    inputChecker = 0;

                }
                else
                {
                    inputChecker = 1;
                    printf("%s\nThe day must be between 1 and 28!\n\n%s", AC_RED, AC_WHITE);
                }
            }

            break;

        case 3:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 31)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 31!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 4:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 30)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 30!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 5:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 31)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 31!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 6:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 30)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 30!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 7:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 31)
            {

                inputChecker = 0;
            }

            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 31!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 8:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 31)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 31!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 9:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 30)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 30!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 10:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 31)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 31!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 11:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 30)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 30!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        case 12:

            if(tasks[checker].dueDate.day >= 1 && tasks[checker].dueDate.day <= 31)
            {

                inputChecker = 0;

            }
            else
            {
                inputChecker = 1;
                printf("%s\nThe day must be between 1 and 31!\n\n%s", AC_RED, AC_WHITE);
            }

            break;

        default:
            break;

        }

    }
    while(inputChecker);


    checker ++;

}

//The addMultiTasks function is used to receive multiple task details at once
void addMultiTasks(int numberTasks)
{

    for(int i = 0; i < numberTasks; i++)
    {

        addTask();

    }

}


//The displayTask function is used to display tasks details at once or applying a filter
void displayTask(int checker, task tasks[])
{

    printf("\n---------------------------------------------------");
    printf("\n------ Welcome! to the display task section -------\n");

    //Filter section
    char filter[6];
    char priorityFilter[4];
    do
    {
        printf("\nDo you want to show all tasks or use a filter?");
        printf("\nType 'filter' to apply a filter,\nor 'skip' to see all tasks: ");
        scanf("%s", &filter);
        if(strcmp(strupr(filter), "FILTER") != 0 && strcmp(strupr(filter), "SKIP") != 0)
        {

            printf("%s\nOops! Enter a valid value!\n%s", AC_RED, AC_WHITE);

        }
    }
    while( strcmp(strupr(filter), "FILTER") != 0 && strcmp(strupr(filter), "SKIP") != 0 );

    if(strcmp(strupr(filter), "SKIP") == 0)
    {

        for(int i = 0; i < checker; i++)
        {

            printf("\n------------------- Task Number %d -----------------\n", i + 1);

            printf("\nThis task title: %s", tasks[i].title);
            printf("\n%s\'s description: %s", tasks[i].title, tasks[i].description);
            printf("\n%s\'s priority: %s", tasks[i].title, tasks[i].priority);
            printf("\n%s\'s due date: %d-%d-%d\n", tasks[i].title, tasks[i].dueDate.day, tasks[i].dueDate.month, tasks[i].dueDate.year);

        }

    }
    else
    {

        do
        {
            printf("\nCurrently, filtering is available by priority only!!\n");
            printf("\nType 'high' to display only high-priority tasks,\nor 'low' to show only low-priority tasks: ");
            scanf("%s", &priorityFilter);
            if(strcmp(strupr(priorityFilter), "HIGH") != 0 && strcmp(strupr(priorityFilter), "LOW") != 0)
            {

                printf("%s\nOops! Enter a valid value!\n%s", AC_RED, AC_WHITE);

            }
        }
        while( strcmp(strupr(priorityFilter), "HIGH") != 0 && strcmp(strupr(priorityFilter), "LOW") != 0 );

        if(strcmp(strupr(priorityFilter), "HIGH") == 0)
        {

            for(int i = 0; i < checker; i++)
            {
                if (strcmp(tasks[i].priority, "HIGH") == 0)
                {


                    printf("\n------------------- Task Number %d -----------------\n", i + 1);

                    printf("\nThis task title: %s", tasks[i].title);
                    printf("\n%s\'s description: %s", tasks[i].title, tasks[i].description);
                    printf("\n%s\'s priority: %s", tasks[i].title, tasks[i].priority);
                    printf("\n%s\'s due date: %d-%d-%d\n", tasks[i].title, tasks[i].dueDate.day, tasks[i].dueDate.month, tasks[i].dueDate.year);

                }

            }

        }
        else
        {


            for(int i = 0; i < checker; i++)
            {
                if (strcmp(tasks[i].priority, "LOW") == 0)
                {


                    printf("\n------------------- Task Number %d -----------------\n", i + 1);

                    printf("\nThis task title: %s", tasks[i].title);
                    printf("\n%s\'s description: %s", tasks[i].title, tasks[i].description);
                    printf("\n%s\'s priority: %s", tasks[i].title, tasks[i].priority);
                    printf("\n%s\'s due date: %d-%d-%d\n", tasks[i].title, tasks[i].dueDate.day, tasks[i].dueDate.month, tasks[i].dueDate.year);

                }

            }

        }

    }

}


void updateTask(int checker, task tasks[]){

    printf("\n---------------------------------------------------");
    printf("\n------ Welcome! to the update task section -------\n");

}

