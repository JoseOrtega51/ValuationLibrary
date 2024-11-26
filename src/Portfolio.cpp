#include "Portfolio.h"
namespace ValLry{

    double portfolio::price(const double t, const double S){
        double price = 0;
        for(auto &instrument : _composition){
            price +=instrument.second->price(t,S);
        }
        return price;
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