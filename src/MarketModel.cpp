#include "MarketModel.h"


namespace ValLry{

    double MarketModel::getRiskFreeRate (double t){

        return _risk_free_rate;
    }

    void MarketModel::addIRCurve(const std::string &id_curve, const IRCurve &curve){
        _IRCurves_map[id_curve] = curve;
        _IRCurves_list.insert(id_curve);
    }
    void MarketModel::eraseIRCurve(const std::string &id_curve){
        if(_IRCurves_list.find(id_curve) != _IRCurves_list.end()){
            _IRCurves_map.erase(id_curve);
            _IRCurves_list.erase(id_curve);
        }else{
            throw std::runtime_error("MarketModel::eraseCurve : Curve is not in this Market model");
        }
    }
    std::set<std::string> MarketModel::getIRCurvesList(){
        return _IRCurves_list;
    }

}