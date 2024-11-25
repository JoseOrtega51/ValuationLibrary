// src/main.cpp
#include <pybind11/pybind11.h>
#include "calculator.h"
#include "advanced_calculator.h"
#include "operations.h"
#include "EuropeanOption.h"

namespace py = pybind11;

PYBIND11_MODULE(ValuationLibrary, m) {
    // Exponer la clase Calculator
    py::class_<Calculator>(m, "Calculator")
        .def(py::init<>())
        .def("add", &Calculator::add)
        .def("subtract", &Calculator::subtract)
        .def_property_readonly("result", &Calculator::get_result, "Resultado actual");

    // Exponer la clase AdvancedCalculator
    py::class_<AdvancedCalculator>(m, "AdvancedCalculator")
        .def(py::init<>())
        .def("operate", &AdvancedCalculator::operate)
        .def_property_readonly("result", &AdvancedCalculator::get_result, "Resultado actual");

    // Exponer la enumeración OperationType
    py::enum_<OperationType>(m, "OperationType")
        .value("ADD", OperationType::ADD)
        .value("SUBTRACT", OperationType::SUBTRACT)
        .export_values();
    
    // Exponer la enumeración 
    py::enum_<ValLry::OptionType>(m, "OptionType")
        .value("CALL", ValLry::OptionType::CALL)
        .value("PUT", ValLry::OptionType::PUT)
        .export_values();

    // Exponer la enumeración 
    py::enum_<ValLry::PricingModel>(m, "PricingModel")
        .value("BLACK_SCHOLES", ValLry::PricingModel::BLACK_SCHOLES)
        .value("BINOMIAL", ValLry::PricingModel::BINOMIAL)
        .export_values();

    //     // Exponer la clase Calculator
    // py::class_<ValLry::EuropeanOptionSolver>(m, "EuropeanOptionSolver")
    //     .def(py::init<>())
    //     .def("BlackScholes", &ValLry::EuropeanOptionSolver::BlackScholes);

    //Exponer la clase Calculator
    py::class_<ValLry::EuropeanOption>(m, "EuropeanOption")
        .def(py::init<ValLry::OptionType, ValLry::PricingModel, double, double>(),
            py::arg("type"),py::arg("model"),py::arg("strike"),py::arg("expiry"))
        .def("BlackScholes", &ValLry::EuropeanOption::BlackScholes);
        //.def("_solver", &ValLry::EuropeanOption::_solver);

}