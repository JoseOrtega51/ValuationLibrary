#include "EuropeanOption.h"
namespace ValLry{

    //////////////////
    //EuropeanOption
    //////////////////

    EuropeanOption::EuropeanOption(OptionType type, double strike, double expiry) 
        : _type(type), _strike(strike), _expiry(expiry), BSM(this){
    }

    double EuropeanOption::price(const double t, const double S){
        double price = internal_price<double, double, double>(t,S);
        return price;
    }

    py::array_t<double> EuropeanOption::price(const py::array_t<double> t, const double S){
        py::array_t<double> price = internal_price<py::array_t<double>, const py::array_t<double>, double>(t,S);
        return price;
    }

    py::array_t<double> EuropeanOption::price(const double t, const py::array_t<double> S){
        py::array_t<double> price = internal_price<py::array_t<double>, double, const py::array_t<double>>(t,S);
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
            break;
        default:
            throw(std::runtime_error("Option Type is not valid!"));
            break;
        }
        return payoff_in_S;
    }


    void EuropeanOption::getPricingModel(PricingModel &model){
        model = _model;
    }

    double EuropeanOption::getExpiry(){
        return _expiry;
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
            double tau = expiry - t;


            //TODO: Include this conditions in an independent function.
            //Check if t is valid
            if(t < 0.)      throw(std::runtime_error("Date t cannot be negative!"));
            if(tau < 0.)    throw(std::runtime_error("Date t cannot be posterior to expiry!"));
            //Check if S is valid 
            if(S < 0.)      throw(std::runtime_error("Price S cannot be negative in BSM!"));

            double NPV = 0.;
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

    py::array_t<double> BSM_EuropeanOption::price(const py::array_t<double> t, const double S){

        auto input_vector = numpy2vector(t);
        // Crear un nuevo vector para la salida
        auto output_vector = std::make_shared<std::vector<double>>(input_vector->size());

        for (size_t i = 0; i < input_vector->size(); ++i) {
            (*output_vector)[i] = price(input_vector->at(i),S);
        }

        auto result = vector2numpy(output_vector);
        return result;
    }


    py::array_t<double> BSM_EuropeanOption::price(const double t, const py::array_t<double> S){
        auto input_vector = numpy2vector(S);
        // Crear un nuevo vector para la salida
        auto output_vector = std::make_shared<std::vector<double>>(input_vector->size());

        for (size_t i = 0; i < input_vector->size(); ++i) {
            (*output_vector)[i] = price(t, input_vector->at(i));
        }

        auto result = vector2numpy(output_vector);
        return result;
    }

    void BSM_EuropeanOption::setup(const double vol, const double r){
        _vol = vol;
        _r = r;
        _set_up = true;
    }

    BSM_EuropeanOption::BSM_EuropeanOption(EuropeanOption* option) : _option(option){}

    


   
}