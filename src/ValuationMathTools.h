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
    std::deque<double> trisol(int k, const std::vector<double> &a, const std::vector<double> &c, const std::vector<double> &b);

    //natural cubic spline second derivatives in nodes
    std::deque<double> spline3_natural_coefs(const std::vector<double> &x, const std::vector<double> &y);

    //Evaluation of natural cubic spline in t
    double spline3_natural_eval(const std::vector<double> &x, const std::vector<double> &y, const std::deque<double> &z, double t);

    //Evaluation of natural cubic spline in vector t
    std::vector<double> spline3_natural_eval(const std::vector<double> &x, const std::vector<double> &y, const std::deque<double> &z, const std::vector<double> &t);
    
}

#endif