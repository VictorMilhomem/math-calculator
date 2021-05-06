#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void help();
void intro();
void runStd();
void run_regression();
void run_prod();
void runMerge();

void run()
{
    while (1)
    {
        intro();

        int value;
        printf("Opção desejada: ");
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
            runMerge(); break;
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
    printf("#    (0) - Ajuda                                              #\n");
    printf("#    (1) - Calculo Desvio Padrão                              #\n");
    printf("#    (2) - Aproximação de Função por Regressão                #\n");
    printf("#    (3) - Calculo do Produto escalar                         #\n");
    printf("#    (4) - Ordernação de valores                              #\n");
    printf("#    (5) - Sair                                               #\n");
    printf("###############################################################\n");
}