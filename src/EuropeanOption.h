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

    class EuropeanOption;

    class BSM_EuropeanOption {
        private:
            EuropeanOption* _option;    //EuropeanOption class that contains this BSM_EuropeanOption
            double          _r;         //risk free rate
            double          _vol;       //volatility
        public:
            //class constructor
            explicit BSM_EuropeanOption(EuropeanOption* option);

            //Set the value for the parameters of the model
            void setup(const double vol, const double r);

            //Price the option according to BSM model for time t and underlying price S
            double price(const double t, const double S);
    };

    class EuropeanOption : FinancialDerivative{
        private:
            OptionType      _type;
            PricingModel    _model;
            double          _strike;
            double          _expiry;

            friend class BSM_EuropeanOption;
            
        public:

            //EuropeanOptionSolver _solver;
            //Constructor
            double BlackScholes(const OptionType &type, double K, double expiry, double S, double t, double sigma, double r);
            //EuropeanOption(){};
            EuropeanOption(OptionType type, PricingModel model, double strike, double expiry);


            BSM_EuropeanOption BSM;

            //getters

            //get value of _model
            void getPricingModel(PricingModel &model);

            //setters

            //set value of _model
            void setPricingModel(const PricingModel &model);


    };

    

}

#endif