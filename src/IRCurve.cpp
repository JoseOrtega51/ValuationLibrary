#include "IRCurve.h"


namespace ValLry{

    IRCurve::IRCurve(const std::vector<double> &buckets, const std::vector<double> &rates) : _buckets(buckets), _rates(rates){
        _spline3_coefs = spline3_natural_coefs(_buckets, _rates);
    }

    IRCurve::IRCurve(const py::array_t<double> &buckets, const py::array_t<double> &rates){
        _buckets = (*numpy2vector(buckets));
        _rates = (*numpy2vector(rates));
        _spline3_coefs = spline3_natural_coefs(_buckets, _rates);
    }

    double IRCurve::getValue(double t){
        double value = spline3_natural_eval(_buckets, _rates, _spline3_coefs, t);
        return value;
    }

    py::array_t<double> IRCurve::getValue(const py::array_t<double> &t){
        std::vector<double> t_vector = (*numpy2vector(t));
        std::vector<double> value_vector = spline3_natural_eval(_buckets, _rates, _spline3_coefs, t_vector);
        py::array_t<double> value_numpy = vector2numpy(std::make_shared<std::vector<double>>(value_vector));
        return value_numpy;
    }

}