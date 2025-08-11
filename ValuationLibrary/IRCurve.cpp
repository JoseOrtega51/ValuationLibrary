#include "IRCurve.h"


namespace ValLry{

    IRCurve::IRCurve(const py::array_t<double> &tenors, const py::array_t<double> &rates, const std::string &label){
        _tenors_num = (*numpy2vector(tenors));
        _tenors_str = tenorToString(_tenors_num);
        _rates = (*numpy2vector(rates));
        _spline3_coefs = spline3_natural_coefs(_tenors_num, _rates);
        _label = label;
        _setRiskFactors();
    }

    IRCurve::IRCurve(const std::vector<std::string> &tenors, const py::array_t<double> &rates, const std::string &label){
        _tenors_str = tenors;
        _tenors_num = tenorToYears(_tenors_str);
        _rates = (*numpy2vector(rates));
        _spline3_coefs = spline3_natural_coefs(_tenors_num, _rates);
        _label = label;
        _setRiskFactors();
    }

    IRCurve::IRCurve(const std::vector<std::string> &tenors, const std::vector<double> &rates, const std::string &label){
        _tenors_str = tenors;
        _tenors_num = tenorToYears(_tenors_str);
        _rates = rates  ;
        _spline3_coefs = spline3_natural_coefs(_tenors_num, _rates);
        _label = label;
        _setRiskFactors();
    }

    double IRCurve::getValue(double t){
        double value = spline3_natural_eval(_tenors_num, _rates, _spline3_coefs, t);
        return value;
    }

    py::array_t<double> IRCurve::getValue(const py::array_t<double> &t){
        std::vector<double> t_vector = (*numpy2vector(t));
        std::vector<double> value_vector = spline3_natural_eval(_tenors_num, _rates, _spline3_coefs, t_vector);
        py::array_t<double> value_numpy = vector2numpy(std::make_shared<std::vector<double>>(value_vector));
        return value_numpy;
    }

    std::vector<RiskFactor> IRCurve::getRiskFactors() const {
        return _risk_factors;
    }

    void IRCurve::_setRiskFactors() {
        for (size_t i = 0; i < _tenors_num.size(); ++i) {
            RiskFactor risk_factor;
            risk_factor.setRiskFactor(_tenors_str[i], _rates[i]);
            _risk_factors.push_back(risk_factor);
        }
    }

}