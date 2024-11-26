#include<stdexcept>
#include "EuropeanOption.h"
namespace ValLry{

    //////////////////
    //EuropeanOption
    //////////////////

    EuropeanOption::EuropeanOption(OptionType type, double strike, double expiry) 
        : _type(type), _strike(strike), _expiry(expiry), BSM(this){
    }

    double EuropeanOption::price(const double t, const double S){
        double price = -1;
        if(_default_model_especified){
        switch (_model)
        {
        case PricingModel::BLACK_SCHOLES:
            price = BSM.price(t,S);
            break;
        case PricingModel::BINOMIAL:
            throw(std::runtime_error("Model is not implemented yet"));
            break;
        default:
            throw(std::runtime_error("Model is not valid"));
            break;
        }
        }else{
            throw(std::runtime_error("Default model has not been specified!"));
        }
        return price;
    }

    double EuropeanOption::payoff(double S){
        double payoff_in_S;
        switch (_type)
        {
        case OptionType::CALL:
            payoff_in_S = std::max(S-_strike,0.);
            break;
        case OptionType::PUT:
            payoff_in_S = std::max(_strike-S,0.);
        default:
            throw(std::runtime_error("Option Type is not valid!"));
            break;
        }
        return payoff_in_S;
    }


    void EuropeanOption::getPricingModel(PricingModel &model){
        model = _model;
    }

    void EuropeanOption::setPricingModel(const PricingModel &model){
        _model = model;
        _default_model_especified = true;
    }

    //////////////////////
    // BSM_EuropeanOption
    //////////////////////
    
    double BSM_EuropeanOption::price(const double t, const double S){
        if(_set_up){
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
        }else{
            throw(std::runtime_error("Model has not been set up!\n"));
            double NPV = -1;
            return NPV;
        }
    }

    void BSM_EuropeanOption::setup(const double vol, const double r){
        _vol = vol;
        _r = r;
        _set_up = true;
    }

    BSM_EuropeanOption::BSM_EuropeanOption(EuropeanOption* option) : _option(option){}

    


   
}