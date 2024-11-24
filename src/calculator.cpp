// src/calculator.cpp
#include "calculator.h"

Calculator::Calculator() : result(0) {}

void Calculator::add(int value) {
    result += value;
}

void Calculator::subtract(int value) {
    result -= value;
}

int Calculator::get_result() const {
    return result;
}