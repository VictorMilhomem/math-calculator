#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"



int main(int argc, char* argv[])
{
    if (argc < 2)
    {
            help();
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
        else{
            return 1;
        }
    }
    else {
        return 1;
    }

    return 0;
}


