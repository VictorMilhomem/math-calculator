#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PERCENT 37


/*-----------------------------------------------
*   Function: abs_value
*   Return: double
*   Description: Returns the absolute value
*-------------------------------------------------
*/

double abs_value(double value)
{
    if (value >= 0 )
        return value;
    
    return value * -1;
}


/*-------------------------------------------------------------
*   Function: regression_error
*   Return: double
*   Description: standard error of regression function
*-------------------------------------------------------------
*/

double regression_error(double y_values[], double x_values[], double coef_a, double coef_b, int n, int id)
{
    double regr_error;
    double sum = 0;
    double *y_equation = malloc(n * sizeof(double));

    switch (id)
    {
    case 1: // linear regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = (coef_a * x_values[i]) + coef_b;
        break;

    case 2: // logarithmic regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = coef_a + (coef_b * log(x_values[i]));
        break;

    case 3: // power regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = coef_a * pow(x_values[i], coef_b); 
        break;
    
    case 4: // ab-Exponential regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = coef_a * pow(coef_b, x_values[i]);
        break;
    
    case 5: // hyperbolic regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = coef_a + (coef_b / x_values[i]);
        break;

    case 6: // exponential regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) =  exp(coef_a + (coef_b * x_values[i]));
        break;  
    
    default:
        break;
    }



    for (int j = 0; j < n; j++)
    {
        double aux = (y_values[j] - y_equation[j]) / y_values[j];
        sum += abs_value(aux);
    }

    regr_error = sum * 100 / n;

    free(y_equation);

    return regr_error;

}


/*-------------------------------------------------------------------------------------------
*   Function: coefficient
*   Return: void
*   Description: Calculates the correlation coefficient and the coefficient of determination
*--------------------------------------------------------------------------------------------
*/

double coefficient(double x_values[], double y_values[], double sum_yi, double coef_a, double coef_b, int n, int coef_id, int id)
{
    double coef_r, R_square, aux_down, aux_up;
    double *y_equation = malloc(n * sizeof(double)); double sum_yi_y_equation = 0; double sum_yi_y = 0;
    double y_aux = sum_yi / n;  // y = (∑yi) / n

    switch (id)
    {
    case 1: // linear regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = (coef_a * x_values[i]) + coef_b;
        break;

    case 2: // logarithmic regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = coef_a + (coef_b * log(x_values[i]));
        break;

    case 3: // power regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = coef_a * pow(x_values[i], coef_b); 
        break;
    
    case 4: // ab-Exponential regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = coef_a * pow(coef_b, x_values[i]);
        break;
    
    case 5: // hyperbolic regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) = coef_a + (coef_b / x_values[i]);
        break;

    case 6: // exponential regression
        for (int i = 0; i < n; i++)
            *(y_equation+i) =  exp(coef_a + (coef_b * x_values[i]));
        break;
    
    default:
        break;
    }
    
    aux_down = 0;
    aux_up = 0;
    for (int j = 0; j < n; j++)
    {
        aux_up += pow((y_values[j] - y_equation[j]), 2);  // ∑(yi - ŷi)²
        aux_down += pow(y_values[j] - y_aux, 2);  // ∑(yi - y)²
    }
    sum_yi_y_equation = aux_up / aux_down;

    // correlation coefficient
    coef_r = sqrt(1 - sum_yi_y_equation);

    // coefficient of determination
    R_square = pow(coef_r, 2);

    free(y_equation);

    switch (coef_id)
    {
    case 1:
        return coef_r;
        break;
    case 2:
        return R_square;
        break;
    
    default:
        break;
    }
}


/*----------------------------------------------------------------
*   Function: linear_regression
*   Return: void
*   Description: Approximate the function using linear regression 
*-----------------------------------------------------------------
*/

void linear_regression(double x_values[], double y_values[], int n)
{
    int id = 1;
    double coef_a, coef_b, coef_r, R_square, std_err_of_reg, aux_up, aux_down;
    register double sum_xi = 0; register double sum_yi = 0;
    register double sum_xi_times_yi = 0; register double sum_xi_pow = 0; register double sum_yi_pow = 0;
    
    // Setting up the variables
    for (int i = 0; i < n; i++)
    {
        sum_xi += x_values[i];  // ∑xi
        sum_xi_pow += pow(x_values[i], 2);  // ∑xi²
        
        sum_yi += y_values[i];  // ∑yi        
        sum_yi_pow += pow(y_values[i], 2);  // ∑yi²

        sum_xi_times_yi += x_values[i] * y_values[i];  // ∑(xi*yi)
    }

    // coef_a = (∑xi * ∑yi - n * ∑(xi*yi)) / (∑xi)² - n*∑xi²
    aux_up = (sum_xi * sum_yi)- (n * sum_xi_times_yi);
    aux_down = pow(sum_xi, 2)- (n * sum_xi_pow);

    coef_a = aux_up / aux_down;

    // coef_b = (∑xi * ∑(xi*yi) - ∑xi²∑yi) / (∑xi)² - n*∑xi²
    aux_up = (sum_xi * sum_xi_times_yi) - (sum_xi_pow * sum_yi);
    aux_down = pow(sum_xi, 2) - (n * sum_xi_pow);

    coef_b = aux_up /  aux_down;

    // coef_r = (n*∑(xi*yi) - ∑xi * ∑yi) / sqrt(n * ∑xi² - (∑xi)² * (n * ∑yi² - (∑yi)²))
    
    double value_right = (n * sum_yi_pow) - pow(sum_yi, 2);  // n * ∑yi² - (∑yi)²
    double value_left = (n * sum_xi_pow) - pow(sum_xi, 2);  // n * ∑xi² - (∑xi)²

    // correlation coefficient
    coef_r = ((n * sum_xi_times_yi) - sum_xi * sum_yi) / sqrt(value_left * value_right);

    // coefficient of determination
    R_square = pow(coef_r, 2);

    // standard error of regression
    std_err_of_reg = regression_error(y_values, x_values, coef_a, coef_b, n, id);

    // Showing the results
    printf("\n----------------Regressão Linear------------------------\n");
    if (coef_b >= 0)
        printf("\ny = %lfx + %lf\n", coef_a, coef_b);
    else
        printf("\ny = %lfx - %lf\n", coef_a, abs_value(coef_b));

    printf("Coeficiente de correlação: %lf\n", coef_r);
    printf("Coeficiente de determinaão: %lf\n", R_square);
    printf("Erro padrão da regressão: %lf %c \n", std_err_of_reg, PERCENT);
    printf("\n-------------------------------------------------------\n");
}


/*-----------------------------------------------------------------------
*   Function: log_regression
*   Return: void
*   Description: Approximate the function using logarithmic regression 
*----------------------------------------------------------------------
*/

void log_regression(double x_values[], double y_values[], int n)
{
    int id = 2;
    double coef_a, coef_b, coef_r, R_square, std_err_of_reg, aux_up, aux_down;
    register double sum_ln_xi = 0; register double sum_yi = 0;
    register double sum_lnxi_times_yi = 0; register double sum_ln_xi_pow = 0;

    // Setting up the values to varibles
    for (int i = 0; i < n; i++)
    {
        sum_ln_xi += log(x_values[i]); // ∑ln(xi) 
        sum_ln_xi_pow += pow(log(x_values[i]), 2); // ∑ln²(xi) 

        sum_yi += y_values[i];  // ∑yi

        sum_lnxi_times_yi += log(x_values[i]) * y_values[i];  // ∑ln(xi)*yi
    }

    aux_up = (n * sum_lnxi_times_yi) - (sum_ln_xi * sum_yi);  // (n * ∑ln(xi)*yi) - (∑ln(xi) * ∑yi)
    aux_down = (n * sum_ln_xi_pow) - pow((sum_ln_xi), 2);  // (n * ∑ln²(xi)) - (∑ln(xi) )

    coef_b = aux_up / aux_down;

    coef_a = (sum_yi / n) - (coef_b * sum_ln_xi / n);  // (∑yi / n) - (b * ∑ln(xi) / n)


    // correlation coefficient
    coef_r = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 1, id);

    // coefficient of determination
    R_square = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 2, id);

    // standard error of regression
    std_err_of_reg = regression_error(y_values, x_values, coef_a, coef_b, n, id);

    // Showing the results

    printf("\n----------------Regressão Logarítmica------------------\n");

    if (coef_b >= 0)
        printf("\ny = %lf + %lfln(x)\n", coef_a, coef_b);
    else
        printf("\ny = %lfx - %lfln(x)\n", coef_a, abs_value(coef_b));

    printf("Coeficiente de correlação: %lf\n", coef_r);
    printf("Coeficiente de determinaão: %lf\n", R_square);
    printf("Erro padrão da regressão: %lf %c\n", std_err_of_reg, PERCENT);
    printf("\n-------------------------------------------------------\n");

}


/*--------------------------------------------------------------
*   Function: power_regression
*   Return: void
*   Description: Approximate the function using power regression 
*----------------------------------------------------------------
*/

void power_regression(double x_values[], double y_values[], int n)
{
    int id = 3;
    double coef_a, coef_b, coef_r, R_square, std_err_of_reg, aux_up, aux_down;
    register double sum_ln_xi = 0; register double sum_yi = 0; register double sum_ln_yi = 0;
    register double sum_lnxi_times_lnyi = 0; register double sum_ln_xi_pow = 0;

    // Setting up the values to varibles
    for (int i = 0; i < n; i++)
    {
        sum_ln_xi += log(x_values[i]); // ∑ln(xi) 
        sum_ln_xi_pow += pow(log(x_values[i]), 2); // ∑ln²(xi) 

        sum_yi += y_values[i];  // ∑yi
        sum_ln_yi += log(y_values[i]);  // ∑ln(yi)

        sum_lnxi_times_lnyi += log(x_values[i]) * log(y_values[i]);  // ∑ln(xi)* ln(yi)
    }

    aux_up = (n * sum_lnxi_times_lnyi) - (sum_ln_xi * sum_ln_yi);
    aux_down = (n * sum_ln_xi_pow) - pow(sum_ln_xi, 2);

    coef_b = aux_up / aux_down;

    double temp = (sum_ln_yi / n) - (coef_b * sum_ln_xi / n);
    coef_a = exp(temp);


    // correlation coefficient
    coef_r = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 1, id);

    // coefficient of determination
    R_square = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 2, id);

    std_err_of_reg = regression_error(y_values, x_values, coef_a, coef_b, n, id);

    // Showing the results

    printf("\n----------------Regressão de Potência------------------\n");

    if (coef_b >= 0)
        printf("\ny = %lf . x^%lf\n", coef_a, coef_b);
    else
        printf("\ny = %lfx . x^(%lf)\n", coef_a, coef_b);

    printf("Coeficiente de correlação: %lf\n", coef_r);
    printf("Coeficiente de determinaão: %lf\n", R_square);
    printf("Erro padrão da regressão: %lf %c\n", std_err_of_reg, PERCENT);
    printf("\n-------------------------------------------------------\n");

}

/*-----------------------------------------------------------------------
*   Function: ab_exponential_regression
*   Return: void
*   Description: Approximate the function using ab-Exponencial regression 
*------------------------------------------------------------------------
*/

void ab_exponential_regression(double x_values[], double y_values[], int n)
{
    int id = 4;
    double coef_a, coef_b, coef_r, R_square, std_err_of_reg, aux_up, aux_down;
    register double sum_xi = 0; register double sum_ln_yi = 0; register double sum_yi = 0;
    register double sum_xi_times_lnyi = 0; register double sum_xi_pow = 0;

    // Setting up the values to varibles
    for (int i = 0; i < n; i++)
    {
        sum_xi += x_values[i]; // ∑(xi) 
        sum_xi_pow += pow(x_values[i], 2); // ∑(xi)² 

        sum_ln_yi += log(y_values[i]);  // ∑ln(yi)
        sum_yi += y_values[i];

        sum_xi_times_lnyi += x_values[i] * log(y_values[i]);  // ∑(xi)* ln(yi)
    }

    aux_up = (n * sum_xi_times_lnyi) - (sum_xi * sum_ln_yi);
    aux_down = (n * sum_xi_pow) - pow(sum_xi, 2);

    coef_b = exp(aux_up / aux_down);

    coef_a = exp((sum_ln_yi / n) - (log(coef_b) * sum_xi / n));


    // correlation coefficient
    coef_r = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 1, id);

    // coefficient of determination
    R_square = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 2, id);

    std_err_of_reg = regression_error(y_values, x_values, coef_a, coef_b, n, id);

    // Showing the results

    printf("\n----------------Regressão ab-Exponencial------------------\n");

    if (coef_b >= 0)
        printf("\ny = %lf . %lf^x\n", coef_a, coef_b);
    else
        printf("\ny = %lfx . %lf^x\n", coef_a, coef_b);

    printf("Coeficiente de correlação: %lf\n", coef_r);
    printf("Coeficiente de determinaão: %lf\n", R_square);
    printf("Erro padrão da regressão: %lf %c\n", std_err_of_reg, PERCENT);
    printf("\n----------------------------------------------------------\n");
}


/*-----------------------------------------------------------------------
*   Function: hyperbolic_regression
*   Return: void
*   Description: Approximate the function using hyperbolic regression 
*------------------------------------------------------------------------
*/


void hyperbolic_regression(double x_values[], double y_values[], int n)
{
    int id = 5;
    double coef_a, coef_b, coef_r, R_square, std_err_of_reg, aux_up, aux_down;
    register double sum_xi = 0; register double sum_yi = 0;
    register double sum_yi_div_xi = 0; register double sum_xi_pow = 0;

    for (int i = 0; i < n; i++)
    {
        sum_xi += 1 / x_values[i];  // ∑(xi)
        sum_xi_pow += 1 / pow(x_values[i], 2);  // ∑(xi)²

        sum_yi += y_values[i];  // ∑(yi)
        sum_yi_div_xi += y_values[i] / x_values[i];  // ∑(yi / xi)
    }

    aux_up = (n * sum_yi_div_xi) - (sum_xi * sum_yi);
    aux_down = (n * sum_xi_pow) - (pow(sum_xi, 2));

    coef_b = aux_up / aux_down;

    coef_a = (sum_yi / n) - (coef_b * sum_xi / n);

    coef_r = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 1, id);

    R_square = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 2, id);

    std_err_of_reg = regression_error(y_values, x_values, coef_a, coef_b, n, id);
    
    // Showing the results

    printf("\n----------------Regressão Hiperbolica------------------\n");

    if (coef_b >= 0)
        printf("\ny = %lf + (%lf / x)\n", coef_a, coef_b);
    else
        printf("\ny = %lfx - (%lf / x)\n", coef_a, abs_value(coef_b));

    printf("Coeficiente de correlação: %lf\n", coef_r);
    printf("Coeficiente de determinaão: %lf\n", R_square);
    printf("Erro padrão da regressão: %lf %c\n", std_err_of_reg, PERCENT);
    printf("\n----------------------------------------------------------\n");
}


/*-----------------------------------------------------------------------
*   Function: exponential_regression
*   Return: void
*   Description: Approximate the function using exponential regression 
*------------------------------------------------------------------------
*/

void exponential_regression(double x_values[], double y_values[], int n)
{
    int id = 6;
    double coef_a, coef_b, coef_r, R_square, std_err_of_reg, aux_up, aux_down;
    register double sum_xi = 0; register double sum_yi = 0; register double sum_lnyi = 0;
    register double sum_lnyi_times_xi = 0; register double sum_xi_pow = 0;

    for (int i = 0; i < n; i++) 
    {
        sum_xi += x_values[i];  // ∑(xi)
        sum_xi_pow += pow(x_values[i], 2);  // ∑(xi)²

        sum_yi += y_values[i];  // ∑(yi)
        sum_lnyi += log(y_values[i]);  // ∑ln(yi)

        sum_lnyi_times_xi += x_values[i] * log(y_values[i]);  // ∑(xi * ln(yi))
    }

    aux_up = (n * sum_lnyi_times_xi) - (sum_xi * sum_lnyi);
    aux_down = (n * sum_xi_pow) - pow(sum_xi, 2);

    coef_b = aux_up / aux_down;

    coef_a = (sum_lnyi / n) - (coef_b * sum_xi / n);

    coef_r = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 1, id);

    R_square = coefficient(x_values, y_values, sum_yi, coef_a, coef_b, n, 2, id);

    std_err_of_reg = regression_error(y_values, x_values, coef_a, coef_b, n, id);
    
    // Showing the results

    printf("\n----------------Regressão Exponencial---------------------\n");

    if (coef_b >= 0)
        printf("\ny = e^(%lf + %lfx)\n", coef_a, coef_b);
    else
        printf("\ny = e^(%lf - %lfx)\n", coef_a, abs_value(coef_b));

    printf("Coeficiente de correlação: %lf\n", coef_r);
    printf("Coeficiente de determinaão: %lf\n", R_square);
    printf("Erro padrão da regressão: %lf %c\n", std_err_of_reg, PERCENT);
    printf("\n----------------------------------------------------------\n");

}

