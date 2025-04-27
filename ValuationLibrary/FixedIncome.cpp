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

    double bond::getYTM(){
        return _YTM;
    }

    double bond::price(){
        //If it is a ZCB, we can use the formula:
        //Price = Nominal * exp(-YTM * maturity)
        if (_is_ZCB){
            return _nominal * exp(- _curve.getValue(_maturity)* _maturity);
        }else{
            //For a bond, we need to calculate the present value of all cash flows
            double price = 0.0;
            for (size_t i = 0; i < _coupon_dates.size(); ++i) {
                price += _nominal * _coupon_yields[i] * exp(-_curve.getValue(_coupon_dates[i]) * _coupon_dates[i]);
            }
            return price + _nominal * exp(-_curve.getValue(_maturity)* _maturity);
        }
    }

    //ZCB constructor
    bond::bond(double maturity, double nominal, IRCurve &curve):    
                _is_ZCB(true), _maturity(maturity), _nominal(nominal), _curve(curve){
                    //Calculate YTM using the curve
                    _YTM = curve.getValue(maturity);
                    //compute price
                    this->setNPV(this->price());
                }

    //Bond constructor
    bond::bond(double maturity, double nominal, const std::vector<double> &coupon_dates, const std::vector<double> &coupon_yields, IRCurve &curve):
                _is_ZCB(false), _maturity(maturity), _nominal(nominal), _coupon_dates(coupon_dates), _coupon_yields(coupon_yields), _curve(curve){
                    // Check if the maturity is greater or equal to the last coupon date
                    if (maturity < coupon_dates.back()) {
                        throw std::invalid_argument("bond: Maturity must be greater or equal than the last coupon date.");
                    }

                    //Compute price
                    this->setNPV(this->price());
                    //Calculate YTM using the curve
                    auto f = [this](double ytm) {
                        double npv = 0.0;
                        for (size_t i = 0; i < _coupon_dates.size(); ++i) {
                            npv += _nominal * _coupon_yields[i] * exp(-ytm * _coupon_dates[i]);
                        }
                        npv += _nominal * exp(-ytm * _maturity);
                        return npv - this->getNPV(); 
                    };

                    auto f_prime = [this](double ytm) {
                        double derivative = 0.0;
                        for (size_t i = 0; i < _coupon_dates.size(); ++i) {
                            derivative -= _nominal * _coupon_yields[i] * _coupon_dates[i] * exp(-ytm * _coupon_dates[i]);
                        }
                        derivative -= _nominal * _maturity * exp(-ytm * _maturity);
                        return derivative;
                    };

                    double ytm_guess = 0.05; // Initial guess for YTM
                    double tolerance = 1e-6;
                    int max_iterations = 100;

                    ytm_guess = newtonRaphson(f, f_prime, ytm_guess, tolerance, max_iterations);

                    // Set the YTM
                    _YTM = ytm_guess;
                    
                }
}