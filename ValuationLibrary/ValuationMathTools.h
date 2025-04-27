#ifndef VALUATION_MATH_TOOLS_H
#define VALUATION_MATH_TOOLS_H

#include <math.h>
#include <vector>
#include <deque>
#include <stdexcept>
#include "python_utils.h"

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
    
    //Convert tenor string to double in years
    double tenorToYears(const std::string &tenor);
    std::vector<double> tenorToYears(const std::vector<std::string> &tenors);

    //Convert years to tenor string
    std::string tenorToString(double tenor);
    std::vector<std::string> tenorToString(const std::vector<double> &tenors);

    //Newton-Raphson method for root finding
    template <typename Function, typename Derivative>
    double newtonRaphson(Function f, Derivative f_prime, double x0, double tol = 1e-6, int max_iter = 1000){
        double x = x0;
        for(int i = 0; i < max_iter; i++){
            double fx = f(x);
            if(fabs(fx) < tol){
                return x;
            }
            double fpx = f_prime(x);
            if(fabs(fpx) < tol){
                throw std::runtime_error("ValuationMathTools::newtonRaphson: Derivative is too small, no convergence.");
            }
            x -= fx / fpx;
        }
        throw std::runtime_error("ValuationMathTools::newtonRaphson: Maximum iterations reached, no convergence.");
    }
}

#endif