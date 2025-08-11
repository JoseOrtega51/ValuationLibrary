#ifndef MARKET_MODEL_H
#define MARKET_MODEL_H

#include "IRCurve.h"
#include "ValuationMathTools.h"
#include <map>
#include <set>

namespace ValLry{
   
    /**
     * @class MarketModel
     * @brief Represents a financial market model containing interest rate curves and a risk-free rate.
     *
     * The MarketModel class manages a collection of interest rate curves (IRCurves) identified by unique string IDs,
     * and provides access to the risk-free rate for a given time. It allows adding, removing, and listing IR curves.
     *
     * @private
     *   - _risk_free_rate: The base risk-free interest rate.
     *   - _IRCurves_map: A mapping from curve IDs to IRCurve objects.
     *   - _IRCurves_list: A set of curve IDs currently stored in the model.
     *
     * @public
     *   - double getRiskFreeRate(double t): Returns the risk-free rate at time t.
     *   - void addIRCurve(const std::string &id_curve, const IRCurve &curve): Adds a new IR curve to the model.
     *   - void eraseIRCurve(const std::string &id_curve): Removes an IR curve from the model by its ID.
     *   - std::set<std::string> getIRCurvesList(): Returns a set of all IR curve IDs in the model.
     */
    
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