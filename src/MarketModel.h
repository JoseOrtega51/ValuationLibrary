#ifndef MARKET_MODEL_H
#define MARKET_MODEL_H

#include <map>

class MarketModel {
    private:
        double _risk_free_rate;
        std::map <double,double> _risk_free_curve; //rate[tenor]

    public:
        double getRiskFreeRate( double t );
};

#endif