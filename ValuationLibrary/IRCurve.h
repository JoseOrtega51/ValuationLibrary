#ifndef IRCURVE_H
#define IRCURVE_H

#include <vector>
#include <deque>
#include "python_utils.h"
#include <iostream>
#include "ValuationMathTools.h"
#include "RiskFactor.h"


namespace ValLry{

    /**
     * @class IRCurve
     * @brief Represents an interest rate curve with associated risk factors, tenors, and rates.
     *
     * The IRCurve class provides functionality to construct and query an interest rate curve,
     * supporting multiple input formats for tenors and rates, and associating risk factors
     * with the curve. It also supports value interpolation and retrieval of risk factors.
     *
     * @private
     * - std::vector<RiskFactor> _risk_factors: Risk factors associated with the curve.
     * - void _setRiskFactors(): Helper to set risk factors for the curve.
     * - std::string _label: Label identifying the curve.
     * - std::vector<double> _tenors_num: Numeric representation of tenors.
     * - std::vector<std::string> _tenors_str: String representation of tenors.
     * - std::vector<double> _rates: Interest rates corresponding to tenors.
     * - std::deque<double> _spline3_coefs: Spline coefficients for interpolation.
     *
     * @public
     * - IRCurve(): Default constructor.
     * - IRCurve(const py::array_t<double>& tenors, const py::array_t<double>& rates, const std::string& label): 
     *      Constructs curve from numeric tenors and rates.
     * - IRCurve(const std::vector<std::string>& tenors, const py::array_t<double>& rates, const std::string& label): 
     *      Constructs curve from string tenors and rates.
     * - IRCurve(const std::vector<std::string>& tenors, const std::vector<double>& rates, const std::string& label): 
     *      Constructs curve from string tenors and rates.
     * - double getValue(double t): Returns interpolated rate at time t.
     * - py::array_t<double> getValue(const py::array_t<double>& t): Returns interpolated rates for array of times.
     * - std::vector<RiskFactor> getRiskFactors() const: Retrieves associated risk factors.
     */

     class IRCurve {
        private:
            std::vector<RiskFactor> _risk_factors; //Risk factors associated with the instrument
            void _setRiskFactors(); //Set risk factors associated with the instrument
            std::string _label; //Label for the instrument
            std::vector<double> _tenors_num;
            std::vector<std::string> _tenors_str;
            std::vector<double> _rates;
            std::deque<double> _spline3_coefs;

        public:


            // Constructor
            IRCurve(){};
            IRCurve(const py::array_t<double> &tenors, const py::array_t<double> &rates, const std::string &label);
            IRCurve(const std::vector<std::string> &tenors, const py::array_t<double> &rates, const std::string &label);
            IRCurve(const std::vector<std::string> &tenors, const std::vector<double> &rates, const std::string &label);

            double getValue(double t);
            py::array_t<double> getValue(const py::array_t<double> &t);

            std::vector<RiskFactor> getRiskFactors() const; //get risk factors associated with the instrument

    };

}

#endif