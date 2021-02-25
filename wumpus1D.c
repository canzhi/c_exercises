#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * Name :  Chen Xiaohui
 * 
 * Simple Wumpus game in 1D
*/

/* Add any #defines here */
#define Empty 0
#define Wumpus 1
#define End 2

/* Number of rooms in our Cave */
#define CaveSize 20  
#define ArraySize (CaveSize + 2)

/* Directions I can face */
#define Left 0
#define Right 1

/* Add any function prototypes here */
void CreateWorld(int cave[]);
int *GetEmptyRoom(int cave[]);
void DisplayWorld(int cave[], int *agent, int agentDir);
int DifferenceByDirection(int dir);
bool DisplayStatus(int cave[], int *agent);

 
int main()
{
    int cave[ArraySize];

    int *agentRoom;
    int agentDirection;

    char command[20];

    int direction;

    int *arrow;
    
    /* Seed the random number generator */
    srand(time(NULL));

    CreateWorld(cave);

    agentRoom = GetEmptyRoom(cave);
    agentDirection = rand() % 2;

    /* The game loop */
    while (true)
    {

        if (DisplayStatus(cave, agentRoom))
            break;

        // DisplayWorld(cave, agentRoom, agentDirection);

        printf("command: ");
        scanf("%20s", command);

        if (strcmp(command, "quit") == 0)
        {
            /* Exit, we are doing */
            break;
        }
        else if (strcmp(command, "move") == 0)
        {
            /* Move command */
            /* What way do we need to go? */
            direction = DifferenceByDirection(agentDirection);
            if ( *(agentRoom + direction) != End)
                agentRoom += direction;
        }
        else if (strcmp(command, "turn") == 0)
        {
            agentDirection = !agentDirection;
        }
        else if (strcmp(command, "fire") == 0)
        {
            arrow = agentRoom;
            int i;
            for (i = 0; i < 3; i++)
            {
                if (agentDirection == 0)
                {
                    arrow--;
                }
                else
                {
                    arrow++;
                }


                if (*arrow != End)
                {
                    if (*arrow = Wumpus)
                    {
                        /* Do something here */
                        *arrow = Empty;
                    }
                    else
                    {
                        continue;
                    }
                }

                break;
            }
        }
        else
        {
            printf("I don't know what you are talking about\n");
        }
    }
    
}


/*********************************************************/

void CreateWorld(int cave[])
{
    int i;
    int *room;

    /* Initialize cave to empty */
    for (i = 0; i < ArraySize; i++)
    {
        cave[i] = Empty;
    }

    /* Set the ends */
    cave[0] = cave[ArraySize - 1] = End;

    /* Get a random empty room and put the Wumpus in it */
    room = GetEmptyRoom(cave);
    *room = Wumpus;
}


int *GetEmptyRoom(int cave[])
{
    int room;

    do
    {
        room = rand() % ArraySize;
    } while (cave[room] != Empty);

    return &cave[room];
}

void DisplayWorld(int cave[], int *agent, int agentDir)
{
    int *room;
    for (room = cave + 1; *room != End; room++)
    {
        if (room == agent)
        {
            switch (agentDir)
            {
            case Left:
                printf("<A  ");
                break;

            case Right:
                printf(" A> ");
            }

            continue;
        }


        switch (*room)
        {
        case Wumpus:
            printf("-W- ");
            break;

        default:
            printf(" .  ");
            break;
        }
    }

    printf("\n");
}

int DifferenceByDirection(int dir)
{
    return dir == Left ? -1 : 1;
}

bool DisplayStatus(int cave[], int *agent)
{
    if (*agent == Wumpus)
    {
        printf("You have been eaten by the Wumpus\n");
        /* We will return true to indicate we are dead! */
        return true;
    }


    if ( *(agent + 1) == Wumpus || *(agent - 1) == Wumpus)
    {
        printf("I smell a Wumpus\n");
    }


    bool deadOfWupus = false;
    int i;
    for (i = 0; i < ArraySize; i++)
    {
        if (cave[i] == Wumpus)
        {
            deadOfWupus = true;
        }
    }
    if (!deadOfWupus)
    {
        printf("The Wumpus has dead, and You won the game\n");
        /* We will return true to indicate the Wumpus has dead! */
        return true;
    }


    return false;
}