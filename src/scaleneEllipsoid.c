#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef PI
#define PI 3.14159265359
#endif


/*-------------------------------------------------------------------
*   Function: scalene_ellipsoid
*   Return: void
*   Description: Calculate the volume and the surface of an ellipsoid
*--------------------------------------------------------------------
*/

void scalene_ellipsoid(double pos[])
{
    double volume, surface, a_times_b, a_times_c, b_times_c;
    register double p = 1.6075;
    register double pos_a = pos[0];register double pos_b = pos[1]; register double pos_c = pos[2];

    volume = 4 * PI * pos_a * pos_b * pos_c / 3;

    a_times_b = pow(pos_a, p) * pow(pos_b, p);
    a_times_c = pow(pos_a, p) * pow(pos_c, p);
    b_times_c = pow(pos_c, p) * pow(pos_c, p);
    surface = 4 * PI * pow((a_times_c + a_times_b + b_times_c)/3, 1/p);

    printf("\n----------------Scalene Ellipsoid---------------------\n");
    printf("Volume of Ellipsoid: %lf\n", volume);
    printf("Surface of Ellipsoid: %lf\n", surface);
    printf("\n----------------------------------------------------------\n");
}

void runEllipsoid()
{
    int running = 1;
    while(running){
        // alocating the memory
        int number_of_values = 3;
        double *vector1 = malloc(number_of_values * sizeof(double));
       
        printf("Enter the Semi-axis a, Semi-axis b, Semi-axis c, respectively:\n");
        double val;
        for (int i = 0; i < number_of_values; i++)
        {
            scanf("%lf", &val);
            *(vector1+ i) = val;
        }
        // calculate 
        scalene_ellipsoid(vector1);
        free(vector1);

        char resp[1];
        printf("You want to use new data(y/n)? ");
        scanf("%s", &resp);

        if(strcmp(resp, "y") == 0)
        {
            continue;
        }
        else if (strcmp(resp, "n") == 0)
        {
            running = 0;
        }

        else
        {
            printf("\nERROR\n");
            exit(1);
        }
        
    }
}