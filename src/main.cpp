// src/main.cpp
#include <pybind11/pybind11.h>
#include "advanced_calculator.h"
#include "operations.h"
#include "EuropeanOption.h"

namespace py = pybind11;

PYBIND11_MODULE(ValuationLibrary, m) {

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

    // EuropeanOption::BSM_EuropeanOption
    py::class_<ValLry::BSM_EuropeanOption>(m, "BSM_EuropeanOption")
        .def("setup", &ValLry::BSM_EuropeanOption::setup)
        .def("price", &ValLry::BSM_EuropeanOption::price);
    
    //Exponer la clase Calculator
    py::class_<ValLry::EuropeanOption>(m, "EuropeanOption")
        .def(py::init<ValLry::OptionType, ValLry::PricingModel, double, double>(),
            py::arg("type"),py::arg("model"),py::arg("strike"),py::arg("expiry"))
        .def("BlackScholes", &ValLry::EuropeanOption::BlackScholes)
        .def_readonly("BSM", &ValLry::EuropeanOption::BSM);  //TODO: def_readonly?
        //.def("_solver", &ValLry::EuropeanOption::_solver);

    

}