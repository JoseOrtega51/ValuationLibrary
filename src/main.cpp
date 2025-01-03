// src/main.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "operations.h"
#include "EuropeanOption.h"
#include "Portfolio.h"
#include "MarketModel.h"
#include "IRCurve.h"
#include "FixedIncome.h"

namespace py = pybind11;

PYBIND11_MODULE(ValuationLibrary, m) {

    // OptionType
    py::enum_<ValLry::OptionType>(m, "OptionType")
        .value("CALL", ValLry::OptionType::CALL)
        .value("PUT", ValLry::OptionType::PUT)
        .export_values();

    // PricingModel
    py::enum_<ValLry::PricingModel>(m, "PricingModel")
        .value("BLACK_SCHOLES", ValLry::PricingModel::BLACK_SCHOLES)
        .value("BINOMIAL", ValLry::PricingModel::BINOMIAL)
        .export_values();

    // FinancialInstrument
    py::class_<ValLry::FinancialInstrument, std::shared_ptr<ValLry::FinancialInstrument>>(m, "FinancialInstrument");

    // EuropeanOption::BSM_EuropeanOption
    py::class_<ValLry::BSM_EuropeanOption>(m, "BSM_EuropeanOption")
        .def("setup", &ValLry::BSM_EuropeanOption::setup)
        .def("price", py::overload_cast<const double, const double>(&ValLry::BSM_EuropeanOption::price), "price function that takes double as t and S")
        .def("price", py::overload_cast<const py::array_t<double>, const double>(&ValLry::BSM_EuropeanOption::price),"price fuction that takes numpy array as t")
        .def("price", py::overload_cast<const double, const py::array_t<double>>(&ValLry::BSM_EuropeanOption::price),"price fuction that takes numpy array as S");
    
    // EuropeanOPtion
    py::class_<ValLry::EuropeanOption, ValLry::FinancialInstrument, std::shared_ptr<ValLry::EuropeanOption>>(m, "EuropeanOption")
        .def(py::init<ValLry::OptionType, double, double>(),
            py::arg("type"),py::arg("strike"),py::arg("expiry"))
        .def("price", py::overload_cast<const double, const double>(&ValLry::EuropeanOption::price), "price function that takes double as t and S")
        .def("price", py::overload_cast<const py::array_t<double>, const double>(&ValLry::EuropeanOption::price),"price fuction that takes numpy array as t")
        .def("price", py::overload_cast<const double, const py::array_t<double>>(&ValLry::EuropeanOption::price),"price fuction that takes numpy array as S")
        .def("delta", py::overload_cast<const double, const double>(&ValLry::EuropeanOption::delta), "delta function that takes double as t and S")
        .def("delta", py::overload_cast<const py::array_t<double>, const double>(&ValLry::EuropeanOption::delta),"delta fuction that takes numpy array as t")
        .def("delta", py::overload_cast<const double, const py::array_t<double>>(&ValLry::EuropeanOption::delta),"delta fuction that takes numpy array as S")
        .def("payoff", &ValLry::EuropeanOption::payoff)
        .def("setPricingModel", &ValLry::EuropeanOption::setPricingModel)
        .def("getPricingModel", &ValLry::EuropeanOption::getPricingModel)
        .def_readonly("BSM", &ValLry::EuropeanOption::BSM); 

    //Portfolio
     py::class_<ValLry::portfolio, ValLry::FinancialInstrument, std::shared_ptr<ValLry::portfolio>>(m, "portfolio")
        .def(py::init<>())
        .def("price", py::overload_cast<const double, const double>(&ValLry::portfolio::price), "price function that takes double as t and S")
        .def("price", py::overload_cast<const py::array_t<double>, const double>(&ValLry::portfolio::price),"price fuction that takes numpy array as t")
        .def("price", py::overload_cast<const double, const py::array_t<double>>(&ValLry::portfolio::price),"price fuction that takes numpy array as S")
        .def("delta", py::overload_cast<const double, const double>(&ValLry::portfolio::delta), "delta function that takes double as t and S")
        .def("delta", py::overload_cast<const py::array_t<double>, const double>(&ValLry::portfolio::delta),"delta fuction that takes numpy array as t")
        .def("delta", py::overload_cast<const double, const py::array_t<double>>(&ValLry::portfolio::delta),"delta fuction that takes numpy array as S")
        .def("addInstrument", &ValLry::portfolio::addInstrument)
        .def("longInstrument", &ValLry::portfolio::longInstrument)
        .def("shortInstrument", &ValLry::portfolio::shortInstrument)
        .def("eraseInstrument", &ValLry::portfolio::eraseInstrument)
        .def("getLabelList", &ValLry::portfolio::getLabelList);

    py::class_<ValLry::IRCurve, std::shared_ptr<ValLry::IRCurve>>(m, "IRCurve")
        .def(py::init<const py::array_t<double>&,const py::array_t<double>&>(), py::arg("bucket"), py::arg("rates"))
        .def("getValue",py::overload_cast<const py::array_t<double>&>( &ValLry::IRCurve::getValue), "Cubic spline of IR curve for a point")
        .def("getValue",py::overload_cast<double> (&ValLry::IRCurve::getValue),"Cubic spline of IR curve for a point");

    py::class_<ValLry::MarketModel, std::shared_ptr<ValLry::MarketModel>>(m, "MarketModel")
        .def(py::init<>())
        .def("addIRCurve", &ValLry::MarketModel::addIRCurve)
        .def("eraseIRCurve", &ValLry::MarketModel::eraseIRCurve)
        .def("getIRCurvesList", &ValLry::MarketModel::getIRCurvesList);
}