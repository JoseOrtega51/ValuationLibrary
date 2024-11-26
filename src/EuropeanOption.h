#ifndef EUROPEAN_OPTION
#define EUROPEAN_OPTION

#include "FinancialInstrument.h"
#include "ValuationMathTools.h"
#include <algorithm>

namespace ValLry{

    enum OptionType{
        CALL,
        PUT
    };

    enum class PricingModel{
        BLACK_SCHOLES,
        BINOMIAL
    };

    class EuropeanOption;

    class BSM_EuropeanOption {
        private:
            EuropeanOption* _option;    //EuropeanOption class that contains this BSM_EuropeanOption
            double          _r;         //risk free rate
            double          _vol;       //volatility
            bool            _set_up = false;   //Has the model been set up?
        public:
            //class constructor
            explicit BSM_EuropeanOption(EuropeanOption* option);

            //Set the value for the parameters of the model
            void setup(const double vol, const double r);

            //Price the option according to BSM model for time t and underlying price S
            double price(const double t, const double S);
    };

    class EuropeanOption : public FinancialInstrument{
        private:
            OptionType      _type;
            PricingModel    _model;
            double          _strike;
            double          _expiry;

            bool            _default_model_especified = false;  //Has the default pricing model been specified?

            friend class BSM_EuropeanOption;
            
        public:

            //EuropeanOptionSolver _solver;
            //Constructor
            //EuropeanOption(){};

            EuropeanOption(OptionType type, double strike, double expiry);

            // Price the option with the default model
            double price(const double t, const double S);

            //BSM model
            BSM_EuropeanOption BSM;

            //Payoff funcion
            double payoff(double S);

            //getters

            //get value of _model
            void getPricingModel(PricingModel &model);

            //setters

            //set value of _model
            void setPricingModel(const PricingModel &model);


    };

    

}

#endif