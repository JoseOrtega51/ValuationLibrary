#ifndef EUROPEAN_OPTION
#define EUROPEAN_OPTION

#include "FinancialDerivative.h"
#include "ValuationMathTools.h"

namespace ValLry{

    enum OptionType{
        CALL,
        PUT
    };

    enum class PricingModel{
        BLACK_SCHOLES,
        BINOMIAL
    };

    // class EuropeanOptionSolver{
    //     private:
    //         OptionType      _type;
    //         double          _strike;
    //         double          _expiry;

    //     public:
    //         EuropeanOptionSolver(){};
    //         EuropeanOptionSolver(OptionType type, double strike, double expiry);
    //         double BlackScholes(const OptionType &type, double K, double expiry, double S, double t, double sigma, double r);
    // };

    class EuropeanOption: FinancialDerivative{
        private:
            OptionType      _type;
            PricingModel    _model;
            double          _strike;
            double          _expiry;
            
        public:

            //EuropeanOptionSolver _solver;
            //Constructor
            double BlackScholes(const OptionType &type, double K, double expiry, double S, double t, double sigma, double r);
            EuropeanOption(){};
            EuropeanOption(OptionType type, PricingModel model, double strike, double expiry);

            //getters

            //get value of _model
            void getPricingModel(PricingModel &model);

            //setters

            //set value of _model
            void setPricingModel(const PricingModel &model);


    };

    

}

#endif