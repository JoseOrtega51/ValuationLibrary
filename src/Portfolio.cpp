#include "Portfolio.h"
#include <iostream>
namespace ValLry{

    double portfolio::price(const double t, const double S){
        double price = 0;
        for(auto &instrument : _composition){
            price +=instrument.second->price(t,S);
        }
        
        if(_isPositionDefined){ //We do not always need the our portfolio has a position, only when is a portfolio in other portfolio
            //If we are shorting the portfolio, its value is multiplied by -1
            if(_BookPosition == Position::SHORT){
                price = -price;
            }
        }
        return price;
    }

    py::array_t<double> portfolio::price(const py::array_t<double> t, const double S){
        std::shared_ptr<std::vector<double>> price;
        auto t_vector = numpy2vector(t);
        for(auto &instrument : _composition){
            py::array_t<double> price_ins = instrument.second->price(t,S);
            auto price_ins_vector = numpy2vector(price_ins);
            for (size_t i = 0; i < t_vector->size(); ++i) {
                (*price)[i] += price_ins_vector->at(i);
            }

            if(_isPositionDefined){ //We do not always need the our portfolio has a position, only when is a portfolio in other portfolio
                for (size_t i = 0; i < t_vector->size(); ++i) {
                    //If we are shorting the portfolio, its value is multiplied by -1
                    if(_BookPosition == Position::SHORT){
                        (*price)[i]*=(-1);
                    }
                }
            }
        }
        
        auto price_np = vector2numpy(price);
        return price_np;
    }
    
    py::array_t<double> portfolio::price(const double t, const py::array_t<double> S){
        std::vector<double> price;
        std::shared_ptr<std::vector<double>> S_vector = numpy2vector(S);
        for (size_t i = 0; i < S_vector->size(); ++i) {price.push_back(0.0);}
        for(auto &instrument : _composition){
            py::array_t<double> price_ins = instrument.second->price(t,S);
            auto price_ins_vector = numpy2vector(price_ins);
            for (size_t i = 0; i < S_vector->size(); ++i) {
                price[i] += price_ins_vector->at(i);
            }
        }
        if(_isPositionDefined){ //We do not always need the our portfolio has a position, only when is a portfolio in other portfolio
            for (size_t i = 0; i < S_vector->size(); ++i) {
                //If we are shorting the portfolio, its value is multiplied by -1
                if(_BookPosition == Position::SHORT){
                    price[i]*=(-1);
                }
            }
        }
        std::shared_ptr<std::vector<double>> price_ptr = std::make_shared<std::vector<double>>(price);
        py::array_t<double> price_np = vector2numpy(price_ptr);
        return price_np;
    }


    //// DELTA


    double portfolio::delta(const double t, const double S){
        double delta = 0;
        for(auto &instrument : _composition){
            delta +=instrument.second->delta(t,S);
        }
        
        if(_isPositionDefined){ //We do not always need the our portfolio has a position, only when is a portfolio in other portfolio
            //If we are shorting the portfolio, its value is multiplied by -1
            if(_BookPosition == Position::SHORT){
                delta = -delta;
            }
        }
        return delta;
    }

    py::array_t<double> portfolio::delta(const py::array_t<double> t, const double S){
        std::shared_ptr<std::vector<double>> delta;
        auto t_vector = numpy2vector(t);
        for(auto &instrument : _composition){
            py::array_t<double> delta_ins = instrument.second->delta(t,S);
            auto delta_ins_vector = numpy2vector(delta_ins);
            for (size_t i = 0; i < t_vector->size(); ++i) {
                (*delta)[i] += delta_ins_vector->at(i);
            }

            if(_isPositionDefined){ //We do not always need the our portfolio has a position, only when is a portfolio in other portfolio
                for (size_t i = 0; i < t_vector->size(); ++i) {
                    //If we are shorting the portfolio, its value is multiplied by -1
                    if(_BookPosition == Position::SHORT){
                        (*delta)[i]*=(-1);
                    }
                }
            }
        }
        
        auto delta_np = vector2numpy(delta);
        return delta_np;
    }
    
    py::array_t<double> portfolio::delta(const double t, const py::array_t<double> S){
        std::vector<double> delta;
        std::shared_ptr<std::vector<double>> S_vector = numpy2vector(S);
        for (size_t i = 0; i < S_vector->size(); ++i) {delta.push_back(0.0);}
        for(auto &instrument : _composition){
            py::array_t<double> delta_ins = instrument.second->delta(t,S);
            auto delta_ins_vector = numpy2vector(delta_ins);
            for (size_t i = 0; i < S_vector->size(); ++i) {
                delta[i] += delta_ins_vector->at(i);
            }
        }
        if(_isPositionDefined){ //We do not always need the our portfolio has a position, only when is a portfolio in other portfolio
            for (size_t i = 0; i < S_vector->size(); ++i) {
                //If we are shorting the portfolio, its value is multiplied by -1
                if(_BookPosition == Position::SHORT){
                    delta[i]*=(-1);
                }
            }
        }
        std::shared_ptr<std::vector<double>> delta_ptr = std::make_shared<std::vector<double>>(delta);
        py::array_t<double> delta_np = vector2numpy(delta_ptr);
        return delta_np;
    }

    void portfolio::addInstrument(std::string label, const std::shared_ptr<FinancialInstrument> &instrument){
        if(_composition.find(label)==_composition.end()){
            _label_list.insert(label);
            _composition[label] = instrument;
        }else{
            throw(std::runtime_error("portfolio::addInstrument : label is already in the porfolio"));
        }
    }

    void portfolio::longInstrument(std::string label, std::shared_ptr<FinancialInstrument> &instrument){
        instrument->setBookPosition(Position::LONG);
        addInstrument(label, instrument);
    }

    void portfolio::shortInstrument(std::string label, std::shared_ptr<FinancialInstrument> &instrument){
        instrument->setBookPosition(Position::SHORT);
        addInstrument(label, instrument);
    }

    void portfolio::eraseInstrument(const std::string label){
        if(_composition.find(label)!=_composition.end()){
            _label_list.erase(label);
            _composition.erase(label);
        }else{
            throw(std::runtime_error("portfolio::addInstrument : label is not in the porfolio"));
        }
    }
    std::set<std::string> portfolio::getLabelList(){
        return _label_list;
    }
}