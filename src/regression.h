#ifndef REGRESSION_H
#define REGRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double abs_value(double );
double regression_error(double [], double [], double , double , int , int );
void ab_exponential_regression(double [], double [], int );
void power_regression(double [], double [], int );
void log_regression(double [], double [], int );

void linear_regression(double [], double [], int );
#endif
