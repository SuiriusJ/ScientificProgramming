#include "WOS.h"
#include <cmath>

double sample_theta(double uniform){
    return acos(1-2*uniform);
}

double sample_phi(double uniform){
    return 2*M_PI*uniform;
}