#ifndef FIXED_INCOME_H
#define FIXED_INCOME_H

#include "FinancialInstrument.h"

namespace ValLry{

    class bond : public FinancialInstrument{
        private:
            double _nominal;    //Face value
            double _maturity;   //Maturity as fraction of years
            double _YTM;        // Yield to maturity (The yield that makes the sum of the discounted cash flows = Market price)
            IRCurve _curve;     //Interest rate curve used for pricing

            const bool _is_ZCB;       //Is it a Zero Coupon Bond? Set value in constructor!

            std::vector<double> _coupon_dates;
            std::vector<double> _coupon_yields;

            std::map<std::string, double> _IR_Delta; //Delta of the bond with respect to the IR curve
        
        public:
            //ZCB constructor
            bond(double maturity, double nominal, IRCurve &curve);

            //Bond constructor
            bond(double maturity, double nominal, const std::vector<double> &coupon_dates, const std::vector<double> &coupon_yields, IRCurve &curve);

            //Price the instrument according to its configuration. It needs to be defined in each inherited class.
            double price() override;

            //compute the delta of the bond with respect to the IR curve
            void computeIRDelta();

            double getNominal();
            double getMaturity();
            double getYTM();

            std::map<std::string, double> getIRDelta();

            

    };

}

#endif