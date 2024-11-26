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
            //Price the instrument according to its configuration. It needs to be defined in each inherited class.
            virtual double price(const double t, const double S) = 0;
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