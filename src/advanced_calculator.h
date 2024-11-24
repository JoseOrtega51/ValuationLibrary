// src/advanced_calculator.h
#ifndef ADVANCED_CALCULATOR_H
#define ADVANCED_CALCULATOR_H

#include "operations.h"

class AdvancedCalculator {
public:
    void operate(OperationType op, int value);
    int get_result() const;

private:
    int result = 0;
};

#endif