#include "mean.h"
#include <cmath>

double Calc_Mean(double* arr, int n){
    double result = 0;
    for(int i=0; i< n; i++){
        result += arr[i] / n;
    }

    return result;
}

double Calc_Std(double* arr, int n){
    double result = 0;
    double mean = Calc_Mean(arr,n);
    for(int i=0; i< n; i++){
        result += pow(arr[i] - mean, 2) / n;
    }

    return sqrt(result);
}