#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * Name :  Chen Xiaohui
 * 
 * Simple Wumpus game in 2D
*/

/* Id's for things in our Cave */
#define Empty 0
#define Wumpus 1
#define End 2
#define Pit 3

/* Number of rooms in our Cave in each dimension */
#define CaveSize 10
#define ArraySize (CaveSize + 2)

/* Directions I can face */
#define Left 0
#define Up 1
#define Right 2
#define Down 3

/* prototypes */
void CreateWorld(int cave[ArraySize][ArraySize]);
int *GetEmptyRoom(int cave[ArraySize][ArraySize]);
void DisplayWorld(int cave[ArraySize][ArraySize], int *agent, int agentDir);
int DifferenceByDirection(int dir);
bool DisplayStatus(int cave[ArraySize][ArraySize], int *agentRoom);




int main()
{
    int cave[ArraySize][ArraySize];

    int *agentRoom;
    int agentDirection;
    char command[20];

    int d; /* difference of moving */

    int *arrow;


    /* Seed the random number generator */
    srand(time(NULL));
    
    /* create the world */
    CreateWorld(cave);

    /* place the agent */
    agentRoom = GetEmptyRoom(cave);
    agentDirection = rand() % 4;
    
    /* The game loop */
    while(true)
    {
        if (DisplayStatus(cave, agentRoom))
            break;

        /* DisplayWorld */
        DisplayWorld(cave, agentRoom, agentDirection);

        /* Get the command */
        printf("Command: ");
        scanf("%20s", command);
        if(strcmp(command, "quit") == 0)
        {
            /* Exit, we are doing */
            break;
        }
        else if(strcmp(command, "move") == 0)
        {
            d = DifferenceByDirection(agentDirection);

            if (*(agentRoom + d) != End)
            {
                agentRoom += d;
            }
        }
        else if(strcmp(command, "turn") == 0)
        {
            agentDirection = ++agentDirection % 4;
        }
        else if(strcmp(command, "fire") == 0)
        {
            arrow = agentRoom;
            int i;
            for (i = 0; i < 3; i++)
            {
                switch (agentDirection)
                {
                case Up:
                    arrow -= ArraySize;
                    break;

                case Down:
                    arrow += ArraySize;
                    break;

                case Right:
                    arrow += 1;
                    break;

                case Left:
                    arrow -= 1;
                    break;
                }

                if (*arrow == End)
                {
                    break;
                }
                else
                {
                    if (*arrow == Wumpus)
                    {
                        *arrow = Empty;
                    }
                }
            }
        }
        else
        {
            printf("I don't know what you are talking about\n");
        }
    }
    
}

/********************************************************/
void CreateWorld(int cave[ArraySize][ArraySize])
{
    int row, col;
    int *room;

    for (row = 0; row < ArraySize; row++)
    {
        for (col = 0; col < ArraySize; col++)
        {
            if (row == 0 || col == 0 || row == ArraySize - 1 || col == ArraySize - 1)
            {
                cave[row][col] = End;
            }
            else
            {
                cave[row][col] = Empty;
            }
        }
    }

    room = GetEmptyRoom(cave);
    *room = Wumpus;

    int i;
    for (i = 0; i < 10; i++)
    {
        room = GetEmptyRoom(cave);
        *room = Pit;
    }

}


int *GetEmptyRoom(int cave[ArraySize][ArraySize])
{
    int row, col;
    int *room;

    do
    {
        row = rand() % ArraySize;
        col = rand() % ArraySize;

        room = &cave[row][col];
    } while (*room != Empty);

    return room;
}


void DisplayWorld(int cave[ArraySize][ArraySize], int *agent, int agentDir)
{
    int row, col;
    int *room;
    
    /* Loop over the rows of the cave */
    for(row=1;  row <= CaveSize + 1;  row++)
    {
        /* 
         * This loop lets us print an up direction 
         * above the agent or a v below the agent
         */
         
        for(col=1; col<=CaveSize; col++)
        {
            if(&cave[row][col] == agent && agentDir == Up)
            {
                printf(" ^  ");
            }
            else if(&cave[row-1][col] == agent && agentDir == Down)
            {
                printf(" v  ");
            }
            else
            {
                printf("    ");
            }
        }
        printf("\n");

        /* 第CaveSize + 1次循环的第2层不用打印 */
        if(row > CaveSize)
            break;
            
        /*
         * This loop prints the agent or the room contents
         */ 
         
        for(col=1; col<=CaveSize; col++)
        {
            room = &cave[row][col];
            if(room == agent)
            {
                switch(agentDir)
                {
                case Left:
                    printf("<A  ");
                    break;
                    
                case Right:
                    printf(" A> ");
                    break;
                    
                default:
                    printf(" A  ");
                    break;
                }
            }
            else
            {
                switch(*room)
                {
                case Wumpus:
                    printf("-🐉- ");
                    break;

                case Pit:
                    printf(" 🕸  ");
                    break;
                    
                default:
                    printf(" .  ");
                    break;    
                }  
            }
            
            
        }

        printf("\n");
    }
    
}


int DifferenceByDirection(int dir)
{
    switch(dir)
    {
    case Up:
        return -ArraySize;
    case Down:
        return ArraySize;
    case Left:
        return -1;
    case Right:
        return 1;
    }
}


bool DisplayStatus(int cave[ArraySize][ArraySize], int *agentRoom)
{
    if (*agentRoom == Wumpus)
    {
        printf("You have been eaten by the Wumpus\n");
        /* We will return true to indicate we are dead! */
        return true;
    }
    else if (*agentRoom == Pit)
    {
        printf("You fell into a pit\n");
        return true;
    }
    else if (
        *(agentRoom + 1) == Wumpus || *(agentRoom - 1) == Wumpus || *(agentRoom + ArraySize) == Wumpus || *(agentRoom - ArraySize) == Wumpus || *(agentRoom + 1) == Pit || *(agentRoom - 1) == Pit || *(agentRoom + ArraySize) == Pit || *(agentRoom - ArraySize) == Pit
        )
    {
        if (*(agentRoom + 1) == Wumpus || *(agentRoom - 1) == Wumpus || *(agentRoom + ArraySize) == Wumpus || *(agentRoom - ArraySize) == Wumpus)
        {
            printf("I smell a Wumpus\n");
        }

        if (*(agentRoom + 1) == Pit || *(agentRoom - 1) == Pit || *(agentRoom + ArraySize) == Pit || *(agentRoom - ArraySize) == Pit)
        {
            printf("I feel a draft\n");
        }
    }


    /* if wumpus has dead */
    bool deadOfWupus = true;
    int row, col;
    for (row = 0; row < ArraySize; row++)
    {
        for (col = 0; col < ArraySize; col++)
        {
            if (cave[row][col] == Wumpus)
            {
                deadOfWupus = !deadOfWupus;
            }
        }
    }
    if (deadOfWupus)
    {
        printf("The Wumpus has dead, and You won the game!!!\n");
        return true;
    }
    /* We will return true to indicate the Wumpus has dead! */
    return false;
}