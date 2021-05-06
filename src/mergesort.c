#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void merge(int vetor[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){  //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){    //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux-comeco];
    }
    
    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, comeco, meio, fim);
    }
}

void runMerge()
{
    int running = 1;
    while(running){
        // alocating the memory
        int number_of_values;
        int *values;
        printf("Digite a quantidade de dados a serem inserdos: ");
        scanf ("%d", &number_of_values);

        if(number_of_values >= 1)
        {
            values = malloc(number_of_values * sizeof(int));
            printf("Digite os dados:\n");
            int val;
            for (int i = 0; i < number_of_values; i++)
            {
                scanf("%d", &val);
                *(values+i) = val;
            }
            mergeSort(values, 0, number_of_values-1);
            printf("Valores ordenados: ");
            for(int i = 0; i < number_of_values; i++)
                printf("%d, ", values[i]);
            printf("\n");

            free(values);
        }

        else
        {
            printf("\nERROR\n");
            exit(1);
        }

        char resp[1];
        printf("Deseja utilizar novos dados(s/n)? ");
        scanf("%s", &resp);

        if(strcmp(resp, "s") == 0)
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