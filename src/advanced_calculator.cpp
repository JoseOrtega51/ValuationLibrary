// src/advanced_calculator.cpp
#include "advanced_calculator.h"

void AdvancedCalculator::operate(OperationType op, int value) {
    if (op == OperationType::ADD) result += value;
    else if (op == OperationType::SUBTRACT) result -= value;
}

int AdvancedCalculator::get_result() const {
    return result;
}