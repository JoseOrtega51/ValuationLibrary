#ifndef IRCURVE_H
#define IRCURVE_H

#include <vector>
#include <deque>
#include "python_utils.h"
#include <iostream>
#include "ValuationMathTools.h"

/**
 * @class IRCurve
 * @brief Represents an interest rate curve with functionality for interpolation and evaluation.
 *
 * The IRCurve class provides methods to store and evaluate interest rate curves
 * using given tenors and rates. It also supports spline interpolation for smooth
 * curve fitting.
 */
namespace ValLry{

     class IRCurve {
        public:
            std::vector<double> _tenors_num;
            std::vector<std::string> _tenors_str;
            std::vector<double> _rates;
            std::deque<double> _spline3_coefs;

            // Constructor
            IRCurve(){};
            IRCurve(const py::array_t<double> &tenors, const py::array_t<double> &rates);
            IRCurve(const std::vector<std::string> &tenors, const py::array_t<double> &rates);

            double getValue(double t);
            py::array_t<double> getValue(const py::array_t<double> &t);
    };

}

#endif