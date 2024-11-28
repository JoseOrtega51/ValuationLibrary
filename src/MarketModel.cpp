#include "MarketModel.h"


namespace ValLry{

    IRCurve::IRCurve(std::vector<double> buckets, std::vector<double> rates) : _buckets(buckets), _rates(rates){
        _spline3_coefs = spline3_natural_coefs(_buckets, _rates);
    }

    double IRCurve::getValue(double t){
        return spline3_natural_eval(_buckets, _rates, _spline3_coefs, t);
    }

    double MarketModel::getRiskFreeRate (double t){
        return _risk_free_rate;
    }

}