#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void run();
void help();
void run_regression();
void runStd();
void runMerge();
void run_prod();

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
            run();
    }

    if (argc == 2)
    {
        if (strcmp(argv[1],"-h") == 0)
            help();
        else if (strcmp(argv[1],"-std") == 0)
            runStd();
        else if (strcmp(argv[1],"-ms") == 0)
            runMerge();
        else if (strcmp(argv[1],"-sp") == 0)
            run_prod();
        else if (strcmp(argv[1],"-r") == 0)
            run_regression();
        else{
            return 1;
        }
    }

    return 0;
}


