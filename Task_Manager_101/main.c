#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
//<time.h> is included for time-related functions such as localtime and time
#include <time.h>

//colors
#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_WHITE "\x1b[37m"


//Declaring the Global Constants

//Using `LIST_LENGTH` with a default value of 100 to allow handling 100 tasks as maximum
//If the application needs to manage more tasks, consider using dynamic memory allocation to adjust the array size
//At the moment, it's not an important part of the code

#define LIST_LENGTH 3
#define TITLE_LENGTH 25
#define DESCRIPTION_LENGTH 350

//Define the date structure to be used as a nested structure
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

//Declaring Global Variables

//Declaring an array of task
task tasks[LIST_LENGTH];
//To count how many task added
int checker = 0;
//Used to store an integer value before checking
char stringInt[4];

//Declaring Functions

//Declaring the "menu" function
void menu();
//Declaring 'validateInteger' function
int validateInteger(char stringInt[4]);
//Declaring the "addTask" function and its Support team
void addTask();
void addMultiTasksSupport(int numberTasks);
void addTaskSupport();
bool validateDate(int month, int day, int year);
//Declaring the "displayTask" function
void displayTask(int checker, task tasks[]);
//Declaring the "filter" function to be used within "displayTask" for full display features
//void filter();
//Declaring the "updateTask" function
void updateTask(int checker, task tasks[]);
//Declaring the "deleteTask" function
void deleteTask(int checker, task tasks[]);

int main()
{
    printf("###################################################\n");
    printf("############### Task Manager 101' #################\n");
    printf("###################################################\n");

    menu();

    return 0;
}

//Defining Functions

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

        //Verify user input option
        switch (toupper(choice))
        {

        case 'A':
            //Manipulating addTask Section
            addTask();
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
            else
            {


                deleteTask( checker, tasks);

            }
            break;

        case 'O':
            break;
        }
    }
    while (toupper(choice) != 'O');
}

//'addTask' function is used to control addTask process flow
void addTask()
{
    //`static` keeps `singleTask` and `numberTasks` values between calls,
    //avoiding repeated creation each time `addTask()` runs
    //This approach is more efficient than global scope, as it limits access to within the function

    //Used to store user choice
    static char singleTask[4];
    static int numberTasks;
    //If 'checker' less then LIST_LENGTH means that still have empty spots
    if(checker < LIST_LENGTH)
    {
        do
        {
            //To choose calling 'addTaskSupport' or 'addMultiTasksSupport'
            printf("\nDo you want to add one or more tasks?\nEnter \"one\" or \"more\": ");
            scanf("%s", &singleTask);
            //To avoid case sensitivity
            strcpy(singleTask, strupr(singleTask));
            if(strcmp(singleTask, "ONE") != 0 && strcmp(singleTask, "MORE") != 0)
            {
                printf("%s\nYou enter invalid value!!!\n%s", AC_RED, AC_WHITE);
            }
            else if(strcmp(singleTask, "ONE") == 0)
            {
                addTaskSupport();
                break;
            }
            else if(strcmp(singleTask, "MORE") == 0)
            {
                // Checking if the use enter a valid value,
                // '(LIST_LENGTH - checker)' to get how many spots still free,
                // and validate user input
                do
                {
                    printf("\nHow many tasks would you like to add?\n(Limit is %d): ", (LIST_LENGTH - checker));
                    scanf("%s", &stringInt);
                    numberTasks = validateInteger(stringInt);
                    if (numberTasks != 0)
                    {
                        if (numberTasks > (LIST_LENGTH - checker))
                        {
                            printf("%s\nOnly %d spots left!\n%s", AC_RED, (LIST_LENGTH - checker), AC_WHITE);
                        }
                        else break;
                    }
                }
                while(true);
                addMultiTasksSupport(numberTasks);
                break;
            }
        }
        while(true);
    }
    else
    {
        //If 'checker' equals LIST_LENGTH, it means there are no available space left
        printf("%s\nThe maximum limit has been reached!!!\n%s", AC_RED, AC_WHITE);
    }
}

//'addMultiTasksSupport' function is used to receive multiple task details at once
void addMultiTasksSupport(int numberTasks)
{
    for(int i = 0; i < numberTasks; i++)
    {
        addTaskSupport();
    }
}

//'addTaskSupport' function collects and validates user input for task details
void addTaskSupport()
{
    //Used to store string date value before checking
    static char stringDay[2], stringMonth[2],stringYear[4];
    static int integerChecker;
    static bool inputChecker = true;//used in conditions validation
    printf("\n---------------------------------------------------");
    printf("\n-------- Welcome! to the add task section ---------\n");
    printf("\n------------------- Task Number %d -----------------\n", checker + 1);
    //Getting task title
    do
    {
        printf("\nPlease enter this task title (only 25 char): ");
        scanf(" %[^\n]", &tasks[checker].title);
        if (strlen(tasks[checker].title) > TITLE_LENGTH)
        {
            printf("%s\nThe title must be 25 characters or fewer!%s", AC_RED, AC_WHITE);
        }
        else break;
    }
    while(true);
    //Getting task description
    do
    {
        printf("Please enter %s\'s task description:\n", tasks[checker].title);
        scanf(" %[^\n]", &tasks[checker].description);
        if (strlen(tasks[checker].description) > DESCRIPTION_LENGTH)
        {
            printf("%s\nThe description must be 350 characters or fewer!%s", AC_RED, AC_WHITE);
        }
        else break;
    }
    while(true);
    //Getting task priority
    do
    {
        printf("\nPlease enter %s\'s task priority (low or high): ", tasks[checker].title);
        scanf("%s", &tasks[checker].priority);
        //To avoid case sensitivity
        strcpy(tasks[checker].priority, strupr(tasks[checker].priority));

        if(strcmp(tasks[checker].priority, "LOW") != 0 && strcmp(tasks[checker].priority, "HIGH") != 0)
        {
            printf("%s\nThe task priority must be (low or high)!\n%s", AC_RED, AC_WHITE);

        }
        else break;

    }
    while(true);
    //Getting task due date
    do
    {
        printf("\nPlease enter %s\'s task due date.\n", tasks[checker].title);
        //checking user inputs type digit or not
        do
        {
            printf("Day: ");
            scanf("%s", &stringDay);
            integerChecker = validateInteger(stringDay);
            if(integerChecker != 0){
                tasks[checker].dueDate.day = integerChecker;
                break;
            }

        }while(true);

        do
        {
            printf("Month: ");
            scanf("%s", &stringMonth);
            integerChecker = validateInteger(stringMonth);
            if(integerChecker != 0){
                tasks[checker].dueDate.month = integerChecker;
                break;
            }

        }while(true);

        do
        {
            printf("Year: ");
            scanf("%s", &stringYear);
            integerChecker = validateInteger(stringYear);
            if(integerChecker != 0){
                tasks[checker].dueDate.year = integerChecker;
                break;
            }

        }while(true);
        //Validate due date with 'validateDate' function
        inputChecker = validateDate(tasks[checker].dueDate.month, tasks[checker].dueDate.day, tasks[checker].dueDate.year);
        if(inputChecker == true)
        {
            printf("%s\nThe due date is invalid, Please try to enter a valid date!\n%s", AC_RED, AC_WHITE);
        }
    }
    while(inputChecker);
    checker ++;
}

//'validateDate'function use to validate due date
bool validateDate(month, day, year)
{
    static bool inputChecker = true;
    static bool leap;
    //Get current time in seconds
    //This line declares a variable t of type time_t
    //and assigns it the current time in seconds since the Unix epoch (00:00:00 UTC on 1 January 1900)
    //The time() function from the <time.h> header is used for this purpose
    time_t t = time(NULL);
    //This line converts the current time (t) to the local time representation
    //and stores it in a struct tm object named currentTime
    //The localtime() function from the <time.h> header is used for this conversion
    struct tm *currentTime = localtime(&t);
    //This line prints the current date and time in a human-readable format
    //The format specifier %02d ensures that each component (day, month, year, hour, minute, second) is printed with leading zeros if necessary
    //The values are extracted from the currentTime structure using its members (tm_mday, tm_mon, tm_year, tm_hour, tm_min, tm_sec)
    //Note that tm_mon represents the month (0-11), so we add 1 to it to get the actual month
    //printf("\nCurrent Date and Time: %02d/%02d/%04d\n", currentTime->tm_mday, currentTime->tm_mon + 1, currentTime->tm_year + 1900);

    //Checking if the user due date is valid
    if(month >= currentTime->tm_mon + 1 && day >= currentTime->tm_mday && year >= currentTime->tm_year + 1900)
    {
        //check if a year is a leap year or not
        if(year % 4 == 0)
        {
            if((year % 100 == 0) && (year % 400 == 0))
            {
                leap = true;
            }
            else if((year % 100 == 0) && (year % 400 != 0))
            {
                leap = false;
            }
            else leap = true;
        }
        else leap = false;

        //month validation
        if(month >= 1 && month <= 12)
        {
            inputChecker = false;
        }
        else inputChecker = true;

        //day validation
        if(day >= 1 && day <= 31)
        {
            if(leap == true)
            {
                if(month == 2)
                {
                    if(day <= 29)
                    {
                        inputChecker = false;
                    }
                    else inputChecker = true;

                }
                else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10  || month == 12)
                {
                    if(day <= 31)
                    {
                        inputChecker = false;
                    }
                    else inputChecker = true;

                }
                else if (month == 4 || month == 6 || month == 9 || month == 11)
                {
                    if(day <= 30)
                    {
                        inputChecker = false;
                    }
                    else inputChecker = true;
                }
            }
            else
            {
                if(month == 2)
                {
                    if(day <= 28)
                    {
                        inputChecker = false;
                    }
                    else inputChecker = true;

                }
                else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10  || month == 12)
                {
                    if(day <= 31)
                    {
                        inputChecker = false;
                    }
                    else inputChecker = true;

                }
                else if (month == 4 || month == 6 || month == 9 || month == 11)
                {
                    if(day <= 30)
                    {
                        inputChecker = false;
                    }
                    else inputChecker = true;
                }
            }

        }
        else inputChecker = true;

    }
    else inputChecker = true;

    return inputChecker;

}

//The 'displayTask' function is used to display tasks details at once or applying a filter
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


//The 'updateTask' function is used to update tasks details
void updateTask(int checker, task tasks[])
{
    int taskNumber, update;

    printf("\n---------------------------------------------------");
    printf("\n------ Welcome! to the update task section -------\n");

    do
    {

        printf("\nPlease enter the list number of the task you want to update");
        printf("\nIf you don't remember,\nenter '0' to display your list and choose a task: ");
        scanf("%d", &taskNumber);

        if(taskNumber == 0)
        {

            displayTask(checker, tasks);

        }

    }
    while( taskNumber < 1 || taskNumber > LIST_LENGTH );

    for(int i = 0; i < checker; i++)
    {

        if (i == (taskNumber - 1))
        {


            printf("\n------------------Task number %d-------------------\n", i + 1);

            printf("\n1. This task title: %s", tasks[i].title);
            printf("\n2. %s\'s description: %s", tasks[i].title, tasks[i].description);
            printf("\n3. %s\'s priority: %s", tasks[i].title, tasks[i].priority);
            printf("\n4. %s\'s due year: %d\n", tasks[i].title, tasks[i].dueDate.year);
            printf("\n5. %s\'s due month: %d\n", tasks[i].title, tasks[i].dueDate.month);
            printf("\n6. %s\'s due day: %d\n", tasks[i].title, tasks[i].dueDate.day);

            do
            {

                printf("\n\nPlease chose one number to specify what you want to update: ");
                scanf("%d", &update);

            }
            while( update < 1 || update > 6);

            switch (update)
            {

            case 1:

                printf("\nPlease enter the new task title: ");
                scanf("%s", &tasks[i].title);
                break;

            case 2:

                printf("\nPlease enter the new task description: ");
                scanf("%s", &tasks[i].description);
                break;

            case 3:

                printf("\nPlease enter the new task priority: ");
                scanf("%s", &tasks[i].priority);
                break;

            case 4:

                printf("\nPlease enter the new task due year: ");
                scanf("%s", &tasks[i].dueDate.year);
                break;

            case 5:

                printf("\nPlease enter the new task due month: ");
                scanf("%s", &tasks[i].dueDate.month);
                break;

            case 6:

                printf("\nPlease enter the new task due day: ");
                scanf("%s", &tasks[i].dueDate.day);
                break;

            };

            break;

        }

    }

}


//The 'deleteTAsk' function is used to delete tasks details
void deleteTask(int checker, task tasks[])
{
    int remember;
    int lengthListDeletedTasks;
    printf("\n---------------------------------------------------");
    printf("\n------ Welcome! to the delet task section -------\n");

    do
    {

        printf("\nIf you don't remember,\nenter '0' to display your list of tasks.\nIf you do remember,\nenter '1' to continue the deletion process: ");
        scanf("%d", &remember);

    }
    while(remember != 0 && remember != 1);

    if (remember == 0)
    {

        displayTask(checker, tasks);

    }
    else
    {

        do
        {

            printf("Please enter how many tasks you want to remove?: ");
            scanf("%d", &lengthListDeletedTasks);

        }
        while(lengthListDeletedTasks == 0 || lengthListDeletedTasks > checker);


        //will store the list number of deleted tasks
        int listDeletedTasks[lengthListDeletedTasks];

        for(int i = 0; i < lengthListDeletedTasks; i++)
        {

            do
            {

                printf("Please enter task list number: ");
                scanf("%d", &listDeletedTasks[i]);

            }
            while(listDeletedTasks[i] == 0 || listDeletedTasks[i] > checker);

        }


        printf("\n----------------------------------------------------------------");
        printf("\n--------Are you sure you want to delete these tasks?-----------\n");

        for(int i = 0; i < lengthListDeletedTasks; i++)
        {

            printf("\n------------------ Task number %d -------------------\n", listDeletedTasks[i]);

            printf("\n1. This task title: %s", tasks[listDeletedTasks[i]-1].title);
            printf("\n2. %s\'s description: %s", tasks[listDeletedTasks[i]-1].title, tasks[listDeletedTasks[i]-1].description);
            printf("\n3. %s\'s priority: %s", tasks[listDeletedTasks[i]-1].title, tasks[listDeletedTasks[i]-1].priority);
            printf("\n%s\'s due date: %d-%d-%d\n", tasks[listDeletedTasks[i]-1].title, tasks[listDeletedTasks[i]-1].dueDate.day, tasks[listDeletedTasks[i]-1].dueDate.month, tasks[listDeletedTasks[i]-1].dueDate.year);

        }

        int com;
        printf("\n----------------------------------------------------------------");
        printf("\n----------------Please enter \'1\' to confirm or \'0\' to cancel: ");
        scanf("%d", &com);

        if(com == 1)
        {

            for(int i = 0; i < lengthListDeletedTasks; i++)
            {
                strcpy(tasks[listDeletedTasks[i]-1].title, " ");
                strcpy(tasks[listDeletedTasks[i]-1].description, " ");
                strcpy(tasks[listDeletedTasks[i]-1].priority, " ");
                tasks[listDeletedTasks[i]-1].dueDate.year = 0;
                tasks[listDeletedTasks[i]-1].dueDate.month = 0;
                tasks[listDeletedTasks[i]-1].dueDate.day = 0;

                printf("\n------------------ Task number %d -------------------\n", listDeletedTasks[i]);

                printf("\n1. This task title: %s", tasks[listDeletedTasks[i]-1].title);
                printf("\n2. %s\'s description: %s", tasks[listDeletedTasks[i]-1].title, tasks[listDeletedTasks[i]-1].description);
                printf("\n3. %s\'s priority: %s", tasks[listDeletedTasks[i]-1].title, tasks[listDeletedTasks[i]-1].priority);
                printf("\n%s\'s due date: %d-%d-%d\n", tasks[listDeletedTasks[i]-1].title, tasks[listDeletedTasks[i]-1].dueDate.day, tasks[listDeletedTasks[i]-1].dueDate.month, tasks[listDeletedTasks[i]-1].dueDate.year);


            }
        }


    }

}


//'validateInteger' function, check if a string contain only digits or not
int validateInteger(char stringInt[])
{
    //get string length, to loop over its chars and check them if they are digits or not
    for(int i = 0; i < strlen(stringInt); i++)
    {
        if(!isdigit(stringInt[i]))
        {
            printf("%s\nPlease enter digits only!\n%s", AC_RED, AC_WHITE);
            return 0;
        }
    }
    //converting string to int
    return atoi(stringInt);
}
