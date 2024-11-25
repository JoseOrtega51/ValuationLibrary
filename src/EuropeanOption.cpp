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
        : _type(type), _model(model), _strike(strike), _expiry(expiry), BSM(this){
    }


    void EuropeanOption::getPricingModel(PricingModel &model){
        model = _model;
    }

    void EuropeanOption::setPricingModel(const PricingModel &model){
        _model = model;
    }

    double BSM_EuropeanOption::price(const double t, const double S){
        double K = _option->_strike;
        double expiry = _option->_expiry;
        OptionType type = _option->_type;

        double NPV = 0.;
        double tau = expiry - t;
        double dp = 1/_vol/sqrt(tau)*(log(S/K)+(_r+_vol*_vol/2)*tau);
        double dm = 1/_vol/sqrt(tau)*(log(S/K)+(_r-_vol*_vol/2)*tau);
        switch (type)
        {
        case OptionType::CALL:
            NPV = S*normalCDF(dp)-K*exp(-_r*tau)*normalCDF(dm);
            break;
        case OptionType::PUT:
            NPV = K*exp(-_r*tau)*normalCDF(-dm)-S*normalCDF(-dp);
            break;
        default:
            throw(std::runtime_error("OptionType not defined!\n"));
            break;
        }

        _option->setNPV(NPV);
        return NPV;
    }

    void BSM_EuropeanOption::setup(const double vol, const double r){
        _vol = vol;
        _r = r;
    }

    BSM_EuropeanOption::BSM_EuropeanOption(EuropeanOption* option) : _option(option){}

    double EuropeanOption::BlackScholes(const OptionType &type, double K, double expiry, double S, double t, double sigma, double r){
        double NPV = 0.;
        double tau = expiry - t;
        double dp = 1/sigma/sqrt(tau)*(log(S/K)+(r+sigma*sigma/2)*tau);
        double dm = 1/sigma/sqrt(tau)*(log(S/K)+(r-sigma*sigma/2)*tau);
        switch (type)
        {
        case OptionType::CALL:
            NPV = S*normalCDF(dp)-K*exp(-r*tau)*normalCDF(dm);
            break;
        case OptionType::PUT:
            NPV = K*exp(-r*tau)*normalCDF(-dm)-S*normalCDF(-dp);
            break;
        default:
            throw(std::runtime_error("OptionType not defined!\n"));
            break;
        }

        setNPV(NPV);
        return NPV;
        
    }


   
}