#include <stdio.h>
#include <stdlib.h>
#include "calc.h"



void run()
{
    while (1)
    {
        intro();

        int value;
        printf("Desired option: ");
        scanf("%d", &value);

        switch (value)
        {
        case 0:
            help(); break;
        case 1:
            runStd(); break;
        case 2:
            run_regression(); break;
        case 3:
            run_prod(); break;
        case 4:
            runEllipsoid(); break;
        case 5:
            exit(0); break;
        default:
            break;
        }
    }
    
}

void intro()
{
    printf("\n######################### MENU ################################\n");
    printf("#    (0) - Help                                               #\n");
    printf("#    (1) - Calculates the Standard Deviation                  #\n");
    printf("#    (2) - Function Approximation with Regression Analysis    #\n");
    printf("#    (3) - Calculates the Scalar Product                      #\n");
    printf("#    (4) - Calculates Ellipsoid                               #\n");
    printf("#    (5) - Exit                                               #\n");
    printf("###############################################################\n");
}