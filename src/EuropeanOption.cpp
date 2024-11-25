#include<stdexcept>
#include "EuropeanOption.h"
namespace ValLry{

    ///////////////////////
    //EuropeanOptionSolver
    ///////////////////////

    // EuropeanOptionSolver::EuropeanOptionSolver(OptionType type, double strike, double expiry) : _type(type), _strike(strike), _expiry(expiry) {}

    // double EuropeanOptionSolver::BlackScholes(const OptionType &type, double K, double expiry, double S, double t, double sigma, double r){
    //     double tau = expiry - t;
    //     double dp = 1/sigma/sqrt(tau)*(log(S/K)+(r+sigma*sigma/2)*tau);
    //     double dm = 1/sigma/sqrt(tau)*(log(S/K)+(r-sigma*sigma/2)*tau);
    //     return S*normalCDF(dp)-K*exp(-r*tau)*normalCDF(dm);
    // }


    //////////////////
    //EuropeanOption
    //////////////////

    //constructor

    // EuropeanOption::EuropeanOption(OptionType type, PricingModel model, double strike, double expiry) 
    //     : _type(type), _model(model), _strike(strike), _expiry(expiry){
    //     _solver = EuropeanOptionSolver(_type, _strike, _expiry);
    //     }

    EuropeanOption::EuropeanOption(OptionType type, PricingModel model, double strike, double expiry) 
        : _type(type), _model(model), _strike(strike), _expiry(expiry){
        }


    void EuropeanOption::getPricingModel(PricingModel &model){
        model = _model;
    }

    void EuropeanOption::setPricingModel(const PricingModel &model){
        _model = model;
    }

    double EuropeanOption::BlackScholes(const OptionType &type, double K, double expiry, double S, double t, double sigma, double r){
        double tau = expiry - t;
        double dp = 1/sigma/sqrt(tau)*(log(S/K)+(r+sigma*sigma/2)*tau);
        double dm = 1/sigma/sqrt(tau)*(log(S/K)+(r-sigma*sigma/2)*tau);
        return S*normalCDF(dp)-K*exp(-r*tau)*normalCDF(dm);
    }


   
}