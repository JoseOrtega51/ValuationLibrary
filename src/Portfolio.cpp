#include "Portfolio.h"
namespace ValLry{

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