#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct Event
{

    char desc[50];             /* the event description */
    time_t startTime;          /* the start time        */
    time_t endTime;            /* the end time          */
    struct Event *next;

} Event;



/*****prototypes******/
int InputOption(char *prompt);
time_t InputDate(char *prompt);
time_t InputTime(char *prompt, time_t date);
void InputString(char *str, int max);
Event *OneEventTyped();
Event *InsertEvent(Event *event);
void HasOverlap(Event *head, Event *newEvent);
void DisplayEvent(Event *event);
void DisplayAllEvents(Event *head);
void DisplayActiveEvents(Event *event);
Event *DeleteExpired(Event *head);




#endif