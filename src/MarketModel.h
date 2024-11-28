#ifndef MARKET_MODEL_H
#define MARKET_MODEL_H

#include <vector>
#include <deque>
#include "ValuationMathTools.h"

namespace ValLry{
    class IRCurve {
        public:
            std::vector<double> _buckets;
            std::vector<double> _rates;
            std::deque<double> _spline3_coefs;

            IRCurve(std::vector<double> buckets, std::vector<double> rates);

            double getValue(double t);
    };

    class MarketModel {
        private:
            double _risk_free_rate;
            IRCurve _risk_free_curve; //rate[tenor]

        public:
            double getRiskFreeRate( double t );
    };
}
#endif