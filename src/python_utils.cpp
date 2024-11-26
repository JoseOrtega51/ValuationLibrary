#include "python_utils.h"

namespace ValLry{

std::shared_ptr<std::vector<double>> numpy2vector(py::array_t<double> input_array){

    // Solicitar el buffer del array de entrada
    auto buf = input_array.request();
    if (buf.ndim != 1) {
        throw std::runtime_error("Array dimension should be 1");
    }

    // Convertir los datos a un std::shared_ptr<std::vector<double>>
    auto input_vector = std::make_shared<std::vector<double>>(
        static_cast<double*>(buf.ptr), 
        static_cast<double*>(buf.ptr) + buf.size
    );
    return input_vector;
}

py::array_t<double> vector2numpy(std::shared_ptr<std::vector<double>> output_vector){
    // Crear un array NumPy desde el std::vector
    auto result = py::array_t<double>(output_vector->size());
    auto result_buf = result.request();
    double* result_ptr = static_cast<double*>(result_buf.ptr);

    // Copiar los datos desde el std::vector al array NumPy
    std::copy(output_vector->begin(), output_vector->end(), result_ptr);

    // Configurar el nuevo array con la misma forma que la entrada
    result.resize({output_vector->size()});

    return result;
}
}