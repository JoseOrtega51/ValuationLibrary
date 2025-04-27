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

    void bond::computeIRDelta(){
        //Compute the delta of the bond with respect to the IR curve
        //This is a simple finite difference approximation
        double epsilon = 0.01; //1% change in the curve

        std::vector<RiskFactor> risk_factors_curve = _curve.getRiskFactors();
        std::vector<double> original_rates;
        std::vector<std::string> original_tenors;
        for (const auto &rf : risk_factors_curve) {
            double rate = rf.getRiskFactorValue<double>();
            std::string tenor = rf.getRiskFactorName();
            original_rates.push_back(rate);
            original_tenors.push_back(tenor);
        }
        IRCurve original_curve = _curve; // Store the original curve

        for (size_t i = 0; i < risk_factors_curve.size(); ++i) {
            std::vector<double> bumped_rates = original_rates;
            bumped_rates[i] += epsilon * bumped_rates[i]; // Bump the rate by 1%
            IRCurve bumped_curve = IRCurve(original_tenors, bumped_rates, "IR_Delta_Bumped");
            _curve = bumped_curve; // Set the bumped curve
            double bumped_price = this->price(); // Compute the price with the bumped curve
            _IR_Delta[original_tenors[i]] = (bumped_price - _NPV); // Compute the delta
        }
        _curve = original_curve; // Restore the original curve

    }

    std::map<std::string, double> bond::getIRDelta(){
        return _IR_Delta;
    }

    //ZCB constructor
    bond::bond(double maturity, double nominal, IRCurve &curve):    
                _is_ZCB(true), _maturity(maturity), _nominal(nominal), _curve(curve){
                    //Calculate YTM using the curve
                    _YTM = curve.getValue(maturity);
                    //compute price
                    this->setNPV(this->price());

                    // Set the risk factor for the bond
                    RiskFactor IRCurve_RF;
                    IRCurve_RF.setRiskFactor("IRCurve", _curve.getValue(maturity));
                    _risk_factors.push_back(IRCurve_RF);
                    
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

                    // Set the risk factor for the bond

                    RiskFactor IRCurve_RF;
                    IRCurve_RF.setRiskFactor("IRCurve", _curve.getValue(maturity));
                    _risk_factors.push_back(IRCurve_RF);
                    
                }

}