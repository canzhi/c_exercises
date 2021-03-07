#include <stdio.h>


#define __USE_XOPEN
#include <time.h>

#include "Scheduler.h"



int main()
{



    Event *head = NULL;
    


    time_t now;

    int option = 0;
    do
    {
        option = InputOption("1 - Insert a new event\n2 - Display all events\n3 - Now?\n4 - Delete expired\n0 - Exit\nPlease select an option: ");

        switch (option)
        {
        case 1:
            head = InsertEvent(head);

            break;
        case 2:
            DisplayALLEvents(head);

            break;
        case 3:
            DisplayActiveEvents(head);

            break;
        case 4:
            head = DeleteExpired(head);

            break;
        default:
            option = 0;
        }

    } while (option != 0);
}
