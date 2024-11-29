#ifndef MARKET_MODEL_H
#define MARKET_MODEL_H

#include "IRCurve.h"
#include "ValuationMathTools.h"
#include <map>
#include <set>

namespace ValLry{
   
    class MarketModel {
        private:
            double _risk_free_rate;
            std::map<std::string, IRCurve> _IRCurves_map;    //IRCurve[id_curve]
            std::set<std::string> _IRCurves_list;        //id_curve

        public:
            double getRiskFreeRate( double t );

            //IR Curves
            void addIRCurve(const std::string &id_curve, const IRCurve &curve);
            void eraseIRCurve(const std::string &id_curve);
            std::set<std::string> getIRCurvesList();
    };
}
#endif