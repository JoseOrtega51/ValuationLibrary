#include "Portfolio.h"
#include <iostream>
namespace ValLry{

    double portfolio::price(const double t, const double S){
        double price = 0;
        for(auto &instrument : _composition){
            price +=instrument.second->price(t,S);
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
        }
        auto price_np = vector2numpy(price);
        return price_np;
    }
    
    py::array_t<double> portfolio::price(const double t, const py::array_t<double> S){
        try{
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
        std::shared_ptr<std::vector<double>> price_ptr = std::make_shared<std::vector<double>>(price);
        py::array_t<double> price_np = vector2numpy(price_ptr);
        return price_np;
        }
        catch(...){
            throw std::runtime_error("SOmething went wrong");
        }
    }

    void portfolio::addInstrument(std::string label, const std::shared_ptr<FinancialInstrument> &instrument){
        if(_composition.find(label)==_composition.end()){
            _label_list.insert(label);
            _composition[label] = instrument;
        }else{
            throw(std::runtime_error("portfolio::addInstrument : label is already in the porfolio"));
        }
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