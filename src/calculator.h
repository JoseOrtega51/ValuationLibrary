// src/calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    Calculator();
    void add(int value);
    void subtract(int value);
    int get_result() const;

private:
    int result;
};

#endif