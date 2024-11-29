#ifndef IRCURVE_H
#define IRCURVE_H

#include <vector>
#include <deque>
#include "python_utils.h"
#include <iostream>
#include "ValuationMathTools.h"

namespace ValLry{

     class IRCurve {
        public:
            std::vector<double> _buckets;
            std::vector<double> _rates;
            std::deque<double> _spline3_coefs;

            IRCurve(){};
            IRCurve(const std::vector<double> &buckets, const std::vector<double> &rates);
            IRCurve(const py::array_t<double> &buckets, const py::array_t<double> &rates);

            double getValue(double t);
            py::array_t<double> getValue(const py::array_t<double> &t);
    };

}

#endif