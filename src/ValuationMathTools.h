#ifndef VALUATION_MATH_TOOLS_H
#define VALUATION_MATH_TOOLS_H

#include <math.h>
#include <vector>
#include <deque>
#include <stdexcept>

namespace ValLry{
    #ifndef M_SQRT1_2
    #define M_SQRT1_2 sqrt(0.5)
    #endif

    double normalCDF(double value);
    std::deque<double> trisol(int k, std::vector<double> a, std::vector<double> c, std::vector<double> b);
    std::deque<double> spline3_natural_coefs(std::vector<double> x, std::vector<double> y);
    double spline3_natural_eval(std::vector<double> x, std::vector<double> y, std::deque<double> z, double t);
    
}

#endif