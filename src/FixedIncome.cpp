#include "FixedIncome.h"

namespace ValLry{

    ///////////////////////////////////
    // bond
    ///////////////////////////////////

    double bond::getNominal(){
        return _nominal;
    }

    double bond::getMaturity(){
        return _maturity;
    }

    double bond::getYield(){
        return _YTM;
    }

    //ZCB constructor
    bond::bond(double maturity, double nominal):    
                _is_ZCB(true), _maturity(maturity), _nominal(nominal){}

    //Bond constructor
    bond::bond(double maturity, double nominal, const std::vector<double> &coupon_dates, const std::vector<double> &coupon_yields):
                _is_ZCB(false), _maturity(maturity), _nominal(nominal), _coupon_dates(coupon_dates), _coupon_yields(coupon_yields){}
}