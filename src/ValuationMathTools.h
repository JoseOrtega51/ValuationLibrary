#ifndef VALUATION_MATH_TOOLS_H
#define VALUATION_MATH_TOOLS_H

#include <math.h>

namespace ValLry{
    #ifndef M_SQRT1_2
    #define M_SQRT1_2 sqrt(0.5)
    #endif

    double normalCDF(double value);
    
}

#endif