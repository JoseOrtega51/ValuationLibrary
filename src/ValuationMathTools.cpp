#include "ValuationMathTools.h"

namespace ValLry{
    double normalCDF(double value)
    {
        return 0.5 * erfc(-value * M_SQRT1_2);
    }
}