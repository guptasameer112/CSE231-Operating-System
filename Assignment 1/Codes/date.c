#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char **argv) 
{
    time_t currenttime = time(NULL);
    struct tm tm = *localtime(&currenttime);

    // A list of Months
    char *months[] = 
    {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    // A list of Weekdays
    char *weekdays[] = 
    {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    /*
        Default: prints the current date in the format: "Month Day Year"
        Two Flags:
            -t: displays the time along with the date
            -w: displays the weekday along with date and time
    */
   
    int timeFlag = 0;
    int weekdayFlag = 0;

    for (int i = 0; i < argc; i++) 
    {
        if (strcmp(argv[i], "-t") == 0) 
        {
            timeFlag = 1;
        } 
        
        else if (strcmp(argv[i], "-w") == 0) 
        {
            weekdayFlag = 1;
        }

        else if (strcmp(argv[i], "-h") == 0) 
        {
            printf("Usage: date [OPTION]...\n");
            printf("  -t: Prints the time along with the date\n");
            printf("  -w: Prints the weekday along with the date and time\n");
            printf("  -h: Prints this help message\n");
            exit(0);
        }

    }

    // Printing

    if (timeFlag == 0 && weekdayFlag == 0) 
    {
        printf("%s %d %d", months[tm.tm_mon], tm.tm_mday, tm.tm_year + 1900);
    } 
    // Print Format: October 25 2022 
    
    else if (timeFlag == 1 && weekdayFlag == 0) 
    {
        printf("%s %d %d %d:%d:%d %s", months[tm.tm_mon], tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (tm.tm_hour > 12) ? "pm" : "am");
    } 
    // Print Format: October 25 2022 12:50:41 
    
    else if ((timeFlag == 0 && weekdayFlag == 1) || timeFlag == 1 && weekdayFlag == 1) 
    {
        printf("%s %s %d %d %d:%d:%d %s", weekdays[tm.tm_wday], months[tm.tm_mon], tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec, (tm.tm_hour > 12) ? "pm" : "am");
    } 
    // Print Format: Tuesday October 25 2022 12:50:23 am

    else
    {
        printf("Invalid Input");
    }
    printf("\n");
    
    return 0;
}

