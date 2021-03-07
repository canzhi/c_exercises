#include <stdio.h>
#include <stdbool.h>

#include <string.h>


#include <stdlib.h>

#define __USE_XOPEN
#include <time.h>

#include "Scheduler.h"


int InputOption(char *prompt)
{

    int option;
    char buffer[100];

    do
    {
        printf("%s", prompt);
        fgets(buffer, sizeof(buffer), stdin);
        if (strlen(buffer) > 0)
            buffer[strlen(buffer) - 1] = '\0';
    
        sscanf(buffer, "%d", &option);
    } while (option != 0 && option != 1 && option != 2 && option != 3 && option != 4);

    return option;
}


void InputString(char *str, int max)
{
    printf("What is the event: ");
    char buffer[100];
    
    /* Get a line of up to 100 characters */
    fgets(buffer, sizeof(buffer), stdin);

    /* Remove any stray newlines from the buffer */
    while (buffer[0] == '\n')
        fgets(buffer, sizeof(buffer), stdin);
    
    /* Remove any \n we may have input */
    if(strlen(buffer) > 0)
        buffer[strlen(buffer)-1] = '\0';
        
    /* Copy up to max characters to our string */
    strncpy(str, buffer, max);
    str[max-1] = '\0';
}


time_t InputDate(char *prompt)
{
    char buffer[100];
    char *result;
    struct tm date;

    do
    {
        printf("%s", prompt);

        /* Get a line of up to 100 characters */
        fgets(buffer, sizeof(buffer), stdin);

        /* Remove any \n we may have input */
        if(strlen(buffer) > 0)
            buffer[strlen(buffer) - 1] = '\0';

        result = strptime(buffer, "%m/%d/%Y", &date);

    } while (result == NULL);

    /* Convert to time_t format */
    date.tm_min = 0;
    date.tm_hour = 0;
    date.tm_sec = 0;
    date.tm_isdst = 0;

    return mktime(&date);
}


time_t InputTime(char *prompt, time_t date)
{
    char buffer[100];
    char *result;
    struct tm time;

    time = *localtime(&date);

    do
    {
        printf("%s", prompt);

        fgets(buffer, sizeof(buffer), stdin);
        if (strlen(buffer) > 0)
            buffer[strlen(buffer) - 1] = '\0';

        result = strptime(buffer, "%I:%M%p", &time);
    } while (result == NULL);

    return mktime(&time);
}

Event *OneEventTyped()
{
    Event *event = malloc(sizeof(Event));

    time_t date;

    InputString(event->desc, sizeof(event->desc));

    date = InputDate("Event date: ");

    event->startTime = InputTime("Start time: ", date);
    event->endTime = InputTime("End time: ", date);

    event->next = NULL;
}

Event *InsertEvent(Event *head)
{
    Event *newEvent = NULL;

    Event *nextEvent = head;
    Event *lastEvent = NULL;

    newEvent = OneEventTyped();

    HasOverlap(head, newEvent);
            
    while (nextEvent != NULL && nextEvent->startTime > newEvent->startTime)
    {
        lastEvent = nextEvent;
        nextEvent = nextEvent->next;
    }
    if (nextEvent == NULL && lastEvent == NULL)
    {
        head = newEvent;
    }
    else if (nextEvent != NULL && lastEvent == NULL)
    {
        newEvent->next = nextEvent;
        head = newEvent;
    }
    else if (nextEvent == NULL && lastEvent != NULL )
    {
        lastEvent->next = newEvent;
    }
    else if (nextEvent != NULL && lastEvent != NULL)
    {
        newEvent->next = nextEvent;
        lastEvent->next = newEvent;
    }


    return head;
}

void HasOverlap(Event *head, Event *newEvent)
{
    bool first = true;

    while(head != NULL)
    {
        if (!(head->endTime < newEvent->startTime || head->startTime > newEvent->endTime))
        {
            if (first)
            {
                printf("%s\n", "Warning, this event overlaps: ");
                first = false;
            }

            DisplayEvent(head);
        }

        head = head->next;
    }
}

void DisplayEvent(Event *event)
{

    char *desc;
    struct tm start;
    struct tm end;


    int mon;
    int mday;
    int year;

    int smin;
    int shour;
    char shalfDay[] = "AM";

    int emin;
    int ehour;
    char ehalfDay[] = "AM";

    desc = event->desc;
    start = *localtime(&event->startTime);
    end = *localtime(&event->endTime);
    mon = start.tm_mon + 1;
    mday = start.tm_mday;
    year = start.tm_year + 1900;
    shour = start.tm_hour;
    if (shour > 12)
    {
        shour %= 12;
        strcpy(shalfDay, "PM");
    }
    else
    {
        strcpy(shalfDay, "AM");
    }
    smin = start.tm_min;
    ehour = end.tm_hour;
    if (ehour > 12)
    {
        ehour %= 12;
        strcpy(ehalfDay, "PM");
    }
    else{
        strcpy(ehalfDay, "AM");
    }
    emin = end.tm_min;
    printf(" %d/%d/%d   %d:%02d%s   %d:%02d%s   %s\n", mon, mday, year, shour, smin, shalfDay, ehour, emin, ehalfDay, desc);

}



void DisplayALLEvents(Event *event)
{
    char *desc;
    struct tm start;
    struct tm end;


    int mon;
    int mday;
    int year;

    int smin;
    int shour;
    char shalfDay[] = "AM";

    int emin;
    int ehour;
    char ehalfDay[] = "AM";


    bool first = true;


    while (event != NULL)
    {
        if (first)
        {
            printf("%s\n", "Scheduler:");
            first = false;
        }

        desc = event->desc;
        start = *localtime(&event->startTime);
        end = *localtime(&event->endTime);

        mon = start.tm_mon + 1;
        mday = start.tm_mday;
        year = start.tm_year + 1900;

        shour = start.tm_hour;

        if (shour > 12)
        {
            shour %= 12;
            strcpy(shalfDay, "PM");
        }
        else
        {
            strcpy(shalfDay, "AM");
        }
        smin = start.tm_min;

        ehour = end.tm_hour;
        if (ehour > 12)
        {
            ehour %= 12;
            strcpy(ehalfDay, "PM");
        }
        else{
            strcpy(ehalfDay, "AM");
        }
        emin = end.tm_min;


        printf(" %d/%d/%d   %d:%02d%s   %d:%02d%s   %s\n", mon, mday, year, shour, smin, shalfDay, ehour, emin, ehalfDay, desc);

        event = event->next;
    }
}


void DisplayActiveEvents(Event *event)
{
    time_t now;
    time(&now);

    char *desc;
    struct tm start;
    struct tm end;


    int mon;
    int mday;
    int year;

    int smin;
    int shour;
    char shalfDay[] = "AM";

    int emin;
    int ehour;
    char ehalfDay[] = "AM";

    printf("%s\n", "Currently active events:");

    while(event != NULL)
    {
        if (event->startTime <= now && now <= event->endTime)
        {
            desc = event->desc;
            start = *localtime(&event->startTime);
            end = *localtime(&event->endTime);
    
            mon = start.tm_mon + 1;
            mday = start.tm_mday;
            year = start.tm_year + 1900;
    
            shour = start.tm_hour;
    
            if (shour > 12)
            {
                shour %= 12;
                strcpy(shalfDay, "PM");
            }
            else
            {
                strcpy(shalfDay, "AM");
            }
            smin = start.tm_min;
    
            ehour = end.tm_hour;
            if (ehour > 12)
            {
                ehour %= 12;
                strcpy(ehalfDay, "PM");
            }
            else{
                strcpy(ehalfDay, "AM");
            }
            emin = end.tm_min;
    
    
            printf(" %d/%d/%d   %d:%02d%s   %d:%02d%s   Prepare for %s\n", mon, mday, year, shour, smin, shalfDay, ehour, emin, ehalfDay, desc);
        }

        event = event->next;
    }

}



Event *DeleteExpired(Event *event)
{
    Event *head = event;
    bool hasExpired = false;

    Event *tempEvent = NULL;

    time_t now;
    time(&now);


    printf("%s\n", "Deleting:");

    while(event != NULL)
    {
        if (now >= event->endTime)
        {
            DisplayEvent(event);
            hasExpired = true;

            /* delete the current event */
            if (tempEvent == NULL)
            {
                event = event->next;
                free(head);
                head = event;
            }
            else
            {
                tempEvent->next = event->next;
                free(event);
                event = tempEvent->next;
            }
            continue;
        }

        tempEvent = event;
        event = event->next;
    }

    if (!hasExpired)
        printf("%s\n", "No expired events");


    return head;
}