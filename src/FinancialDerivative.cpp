#include "FinancialDerivative.h"

namespace ValLry{

    double FinancialDerivative::getMTM() const{
        return _MTM;
    }

    double FinancialDerivative::getNPV() const{
        return _NPV;
    }

    void FinancialDerivative::getBookPosition(Position &BookPosition){
        BookPosition = _BookPosition;
    }

    void FinancialDerivative::setMTM(const double MTM){
        _MTM = MTM;
    }

    void FinancialDerivative::setNPV(const double NPV){
        _NPV = NPV;
    }

    void FinancialDerivative::setBookPosition(const Position &BookPosition){
        _BookPosition = BookPosition;
    }
}