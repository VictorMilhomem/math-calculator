#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*--------------------------------------------------------------
*   Function: create_csv
*   Return: void
*   Description: Create or append the datas into a csv file 
*----------------------------------------------------------------
*/

void create_csv(double values[], int N, int append_file, int file_ID)
{  
    FILE* fp;
    if(!append_file)
    {
        fp = fopen("./csv/sample.csv", "w");
        fprintf(fp, "ID,Tamanho_da_amostra(N),Soma_dos_numeros,Media,Desvio_padrão(σ),Variação_da_população(σ²),Desvio_padrão_da_amostra(s),Variação_da_amostra(s²)\n");
    }

    else
    {
        fp = fopen("./csv/sample.csv", "a");
    }

    fprintf(fp, "%d,", file_ID);
    fprintf(fp, "%d,", N);
    
    for(int i = 0; i < 6; i++)
    {
        fprintf(fp, "%lf,", values[i]);
    }
    fputc('\n', fp);
    fflush(fp);
    fclose(fp);
}

void show_results(int N, double results[])
{
    // showing the results
    printf("-----------------Resultados--------------------------");
    printf("\nTamanho da amostra(N): %d\n", N);
    printf("Soma dos numeros: %lf\n", results[0]);
    printf("Media: %lf\n", results[1]);
    printf("Desvio padrão(σ): %lf\n", results[2]);
    printf("Variação da população(σ²): %lf\n", results[3]);
    printf("Desvio padrão da amostra(s): %lf\n", results[4]);
    printf("Variação da amostra(s²): %lf\n", results[5]);
    printf("------------------------------------------------------");
}

/*---------------------------------------------------------------------------------------------------------
*   Function: calculate
*   Return: void
*   Description: Calculates the standard deviation of some sample, and saves using the create_csv function
*----------------------------------------------------------------------------------------------------------
*/


double calculate(double values[], int N, int append_file, int file_ID)
{
    double sum = 0;
    double std_dev, std_dev_sample, medium_value, average, population_variation, sample_population_variation;
    
    for(int i = 0; i < N; i++)
    {
        sum += values[i];
    }

    medium_value = sum/2;
    average = sum/N;


    // calculate the standard deviation 
    double sum_value_average = 0;
    double sub_value_average_pow;
    for(int i = 0; i < N; i++)
    {
        sub_value_average_pow = pow(values[i] - average, 2);
        sum_value_average += sub_value_average_pow;
    }

    std_dev = sqrt(sum_value_average/N);
    population_variation = pow(std_dev, 2);

    // sample standard deviation
    sum_value_average = 0;
    for(int i = 0; i < N; i++)
    {
        sub_value_average_pow = pow(values[i] - medium_value, 2);
        sum_value_average += sub_value_average_pow;
    }

    std_dev_sample = sqrt(sum_value_average/(N-1));
    sample_population_variation = pow(std_dev_sample, 2);

    // showing the results
    double *results = malloc(6 * sizeof(double));
    *(results+0) = sum; *(results+1) = average; *(results+2) = std_dev; *(results+3) = population_variation;
    *(results+4) = std_dev_sample; *(results+5) = sample_population_variation;

    show_results(N, results);

    // storing all of the calculated values

    create_csv(results, N, append_file, file_ID);    
    printf("\nDados salvos no arquivo sample.csv\n");
    free(results);

}

/*--------------------------------------------------------------
*   Function: runStd
*   Return: void
*   Description: Runs the calculate function 
*----------------------------------------------------------------
*/

void runStd()
{
    int append_file = 0;
    int id = 0;
    int running = 1;
    while(running){
        // alocating the memory
        int number_of_values;
        double *values;
        printf("Digite a quantidade de dados a serem inserdos: ");
        scanf ("%d", &number_of_values);

        if(number_of_values >= 1)
        {
            values = malloc(number_of_values * sizeof(double));
            printf("Digite os valores:\n");
            double val;
            for (int i = 0; i < number_of_values; i++)
            {
                scanf("%lf", &val);
                *(values+i) = val;
            }
            calculate(values, number_of_values, append_file, id);
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
            append_file = 1;
            id += 1;
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
