#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* 
 * Simple lunar lander program.
 * By:  I. M. Genius
 * Best landing: Time = 22 seconds, Fuel = 77.0, Velocity = -1.36
 */
 
int main()
{
    double altitude = 100;        /* Meters */
    double velocity = 0;        /* Meters per second */
    double fuel = 100;      /* Kilograms */
    double power = 1.5;     /* Acceleration per pound of fuel */
    double g = -1.63;       /* Moon gravity in m/s^2 */
    double burn;            /* Amount of fuel to burn */

    bool valid;             /* Valid data entry flag */

    int times = 0;              /* times to takes */


    printf("Lunar Lander - (c) 2021, by Chen Xiaohui\n");
        
    while (altitude > 0)
    {
        printf("Altitude: %.2f\n", altitude);
        printf("Velocity: %.2f\n", velocity);
        printf("You have %.1f Kilograms of fuel\n", fuel);
        
        do
        {
            valid = false;  /* Assume invalid until we know otherwise */
    
            printf("How much fuel would you like to burn: ");
            scanf(" %lf", &burn);
        
            if (burn < 0)
            {
                printf("You can't burn negative fuel\n");
            }
            else if (burn > 5 )
            {
            printf("You can't burn more than 5 kilograms per second\n");
            }
            else if (burn > fuel)
            {
                printf("You can't burn fuel you don't have\n");
            }
            else
            {
                printf("Burning %.1f kilograms of fuel\n", burn);
                valid = true;
            }
        } while (!valid);
    
    
        velocity = velocity + g * 1.0 + power * burn * 1.0;
        altitude += velocity * 1.0;
        fuel -= burn;

        times++;
    }

    printf("You landed with a velocity of %.2f\n", velocity);
    
    if(fabs(velocity) > 3)
    {
        printf("Your next of kin have been notified\n");
    }

    printf("The game takes %d seconds,and  fuel remaining: %.1f kilograms\n", times, fuel);
}
