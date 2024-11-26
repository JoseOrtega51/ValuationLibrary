#ifndef FINANCIAL_INSTRUMENT_H
#define FINANCIAL_INSTRUMENT_H

namespace ValLry{

    enum class Position{
        LONG,
        SHORT
    };

    class FinancialInstrument{
        private:

            double _MTM; //Market Price
            double _NPV; //Computed price
            Position _BookPosition;  //Short or Long

        public:
            //getters

            //get value of MTM
            double getMTM() const;

            //get value of NPV   
            double getNPV() const;   

            //get value of BookPosition
            void getBookPosition(Position &BookPosition);  

            //setters

            //set value of MTM
            void setMTM(const double MTM);   

            //set value of NPV
            void setNPV(const double MTM);   

            //set value of BookPosition
            void setBookPosition(const Position &BookPosition);   

    };

};
#endif