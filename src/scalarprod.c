#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*--------------------------------------------------------------
*   Function: scalar_product
*   Return: int
*   Description: Calculates the scalar product of to vectors
*----------------------------------------------------------------
*/

int scalar_product(int vector1[], int vector2[], int size_vector)
{
    int scalar_prod = 0;
    for (int i = 0; i < size_vector; i++)
        scalar_prod += vector1[i] * vector2[i];

    return scalar_prod;
}

/*--------------------------------------------------------------
*   Function: run_prod
*   Return: void
*   Description: Runs the scalar product function
*----------------------------------------------------------------
*/

void run_prod()
{
    int running = 1;
    while(running){
        printf("\n-------------------Scalar Product------------------------\n");
        // alocating the memory
        int number_of_values;
        int *vector1;
        int *vector2;

        printf("Enter the amount of data: ");
        scanf ("%d", &number_of_values);

        if(number_of_values >= 1)
        {
            vector1 = malloc(number_of_values * sizeof(int));
            vector2 = malloc(number_of_values * sizeof(int));
            printf("Enter the first vector data:\n");
            int val;
            for (int i = 0; i < number_of_values; i++)
            {
                scanf("%d", &val);
                *(vector1+ i) = val;
            }

            printf("Enter the second vector data:\n");
            int val2;
            for (int i = 0; i < number_of_values; i++)
            {
                scanf("%d", &val2);
                *(vector2+ i) = val2;
            }

            // calculate the scalar product
            int product;
            product = scalar_product(vector1, vector2, number_of_values);
            printf("The scalar product is: %d\n\n", product);

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