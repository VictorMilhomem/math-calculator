#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"


void run();

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
            run();
    }

    else if (argc == 2)
    {
        if (strcmp(argv[1],"-h") == 0)
            help();
        else if (strcmp(argv[1],"-std") == 0)
            runStd();
        else if (strcmp(argv[1],"-sp") == 0)
            run_prod();
        else if (strcmp(argv[1],"-r") == 0)
            run_regression();
        else if (strcmp(argv[1],"-el") == 0)
            runEllipsoid();
        else{
            return 1;
        }
    }
    else {
        return 1;
    }

    return 0;
}


