#ifndef PYTHON_UTILS_H
#define PYTHON_UTILS_H

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
#include <memory>

namespace py = pybind11;
namespace ValLry{

//Transform a python numpy array into a std::shared_ptr<std::vector<double>>
std::shared_ptr<std::vector<double>> numpy2vector(py::array_t<double> input_array);

//Transform a std::shared_ptr<std::vector<double>> into a python numpy array 
py::array_t<double> vector2numpy(std::shared_ptr<std::vector<double>> input_array);
} 

#endif