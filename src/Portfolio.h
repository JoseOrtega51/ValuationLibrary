#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include<vector>
#include<string>
#include<map>
#include<set>
#include <algorithm>
#include<stdexcept>
#include <memory>
#include"FinancialInstrument.h"

namespace ValLry{

    class portfolio{
        private:
            std::map<std::string, std::shared_ptr<FinancialInstrument>>  _composition;
            std::set<std::string>                    _label_list;
        
        public:
            //Compute price of whole portfolio
            double price(const double t, const double S);

            void addInstrument(std::string label, const std::shared_ptr<FinancialInstrument> &instrument);
            void eraseInstrument(const std::string label);
            std::set<std::string> getLabelList();

    };


};


#endif