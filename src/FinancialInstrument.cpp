#include "FinancialInstrument.h"

namespace ValLry{

    double FinancialInstrument::getMTM() const{
        return _MTM;
    }

    double FinancialInstrument::getNPV() const{
        return _NPV;
    }

    void FinancialInstrument::getBookPosition(Position &BookPosition){
        BookPosition = _BookPosition;
    }

    void FinancialInstrument::setMTM(const double MTM){
        _MTM = MTM;
    }

    void FinancialInstrument::setNPV(const double NPV){
        _NPV = NPV;
    }

    void FinancialInstrument::setBookPosition(const Position &BookPosition){
        _BookPosition = BookPosition;
    }
}