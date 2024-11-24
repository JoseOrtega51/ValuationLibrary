// src/main.cpp
#include <pybind11/pybind11.h>
#include "calculator.h"
#include "advanced_calculator.h"
#include "operations.h"

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
}