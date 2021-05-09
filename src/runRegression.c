#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regression.h"

/*----------------------------------------------------
*   Function: run_regression
*   Description: Runs all of the regression functions
*-----------------------------------------------------
*/

void run_regression()
{
    int running = 1;
    while(running){
        // alocating the memory
        int number_of_values;
        double *vector1 = malloc(number_of_values * sizeof(double));
        double *vector2 = malloc(number_of_values * sizeof(double));
        printf("Enter the amount of data: ");
        scanf ("%d", &number_of_values);

        if(number_of_values >= 1)
        {
            printf("Enter the X data:\n");
            double val;
            for (int i = 0; i < number_of_values; i++)
            {
                scanf("%lf", &val);
                *(vector1+ i) = val;
            }
            printf("Enter the y data:\n");
            double val2;
            for (int i = 0; i < number_of_values; i++)
            {
                scanf("%lf", &val2);
                *(vector2+ i) = val2;
            }
            // calculate the regression
            linear_regression(vector1, vector2, number_of_values);
            log_regression(vector1, vector2, number_of_values);
            power_regression(vector1, vector2, number_of_values);
            ab_exponential_regression(vector1, vector2, number_of_values);
            hyperbolic_regression(vector1, vector2, number_of_values);
            exponential_regression(vector1, vector2, number_of_values);


            free(vector1);
            free(vector2);
            
        }
        else
        {
            printf("\nERROR\n");
            exit(1);
        }


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