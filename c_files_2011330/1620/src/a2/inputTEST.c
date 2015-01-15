/*------------------------------------------------------------*/
/*  Program chapter2_3                                        */
/*                                                            */
/*  This program estimates new velocity and                   */
/*  acceleration values for a specified time.                 */
 
#include <stdio.h>
#include <math.h>

 
int main(void)
{
   /*  Declare variables.  */
   double time, velocity, cheap_vel, acceleration;

   setbuf( stdout, 0); /* make stdout unbuffered */

   /*  Get time value from the keyboard.  */
   printf("Enter new time value in seconds: \n");
   scanf("%lf",&time);
 
   /*  Compute velocity and acceleration.  */
   velocity = 0.00001*pow(time,3) - 0.00488*pow(time,2)
              + 0.75795*time + 181.3566;
   
   cheap_vel = ((0.00001*time - 0.0048)*time + 0.75795)*time 
               + 181.3566;
   
   acceleration = 3 - 0.000062*velocity*velocity;
 
   /*  Print time velocity and acceleration.  */
   printf("Time = %g\n", time);
   printf("Velocity = %8.3f m/s \n",velocity);
   printf("Cheap Velocity = %8.3f m/s \n", cheap_vel);
   printf("Acceleration = %8.3f m/s^2 \n",acceleration);
   
   /*   Exit program.  */
   return 0;
}
/*------------------------------------------------------------*/

