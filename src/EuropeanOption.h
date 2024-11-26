#ifndef EUROPEAN_OPTION
#define EUROPEAN_OPTION

#include "FinancialInstrument.h"
#include "ValuationMathTools.h"
#include <algorithm>
#include<stdexcept>
#include "python_utils.h"

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

            //Overload price function for numpy arrays
            py::array_t<double> price(const py::array_t<double> t, const double S);
            py::array_t<double> price(const double t, const py::array_t<double> S);
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

             // Price the option with the default model in a single point
            double price(const double t, const double S) override;

            // Price the option with the default model in an array of time instants
            py::array_t<double> EuropeanOption:: price(const py::array_t<double> t, const double S)  override;

            // Price the option with the default model in an array of prices
            py::array_t<double> EuropeanOption:: price(const double t, const py::array_t<double> S)  override;

            // template definition for the main pricing function
            template<typename out_type, typename t_type, typename S_type>
            out_type internal_price(t_type t, S_type S){

                if(!_isPositionDefined){throw(std::runtime_error("Position in portfolio has not been set up!\n"));}
                if(!_default_model_especified){throw(std::runtime_error("Default model has not been specified!"));}

                out_type price;
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

                //If we are shorting the instrument, its value is multiplied by -1
                if(_BookPosition == Position::SHORT){
                    price = -price;
                }
                    
                return price;
            }
           

            //BSM model
            BSM_EuropeanOption BSM;

            //Payoff funcion
            double payoff(double S);

            //getters

            //get value of _model
            void getPricingModel(PricingModel &model);
            //get value of _expiry
            double getExpiry();

            //setters

            //set value of _model
            void setPricingModel(const PricingModel &model);
    };

    

}

#endif