#ifndef FIXED_INCOME_H
#define FIXED_INCOME_H

#include "FinancialInstrument.h"

namespace ValLry{

    class bond : FinancialInstrument{
        private:
            double _nominal;    //Face value
            double _maturity;   //Maturity as fraction of years
            double _YTM;        // Yield to maturity (The yield that makes the sum of the discounted cash flows = Market price)

            const bool _is_ZCB;       //Is it a Zero Coupon Bond? Set value in constructor!

            std::vector<double> _coupon_dates;
            std::vector<double> _coupon_yields;
        
        public:
            //ZCB constructor
            bond(double maturity, double nominal);

            //Bond constructor
            bond(double maturity, double nominal, const std::vector<double> &coupon_dates, const std::vector<double> &coupon_yields);

            double getNominal();
            double getMaturity();
            double getYield();

    };

}

#endif