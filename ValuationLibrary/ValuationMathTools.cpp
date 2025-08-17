#include "ValuationMathTools.h"

/**
 * @fn double normalCDF(double value)
 * @brief Computes the cumulative distribution function (CDF) of the standard normal distribution.
 * @param value The input value for which the CDF is computed.
 * @return The CDF value for the given input.
 */

/**
 * @fn std::deque<double> trisol(int k, const std::vector<double> &a, const std::deque<double> &c, const std::vector<double> &b)
 * @brief Solves a tridiagonal system of linear equations using the Thomas algorithm.
 * @param k The size of the system minus one.
 * @param a The diagonal elements of the tridiagonal matrix.
 * @param c The sub-diagonal elements of the tridiagonal matrix.
 * @param b The right-hand side vector.
 * @return The solution vector of the system.
 */

/**
 * @fn std::deque<double> spline3_natural_coefs(const std::vector<double> &x, const std::vector<double> &y)
 * @brief Computes the coefficients for a natural cubic spline interpolation.
 * @param x The vector of x-coordinates of the data points.
 * @param y The vector of y-coordinates of the data points.
 * @return A deque containing the second derivatives (z-coefficients) of the spline at the data points.
 */

/**
 * @fn double spline3_natural_eval(const std::vector<double> &x, const std::vector<double> &y, const std::deque<double> &z, double t)
 * @brief Evaluates the natural cubic spline at a single point.
 * @param x The vector of x-coordinates of the data points.
 * @param y The vector of y-coordinates of the data points.
 * @param z The second derivatives (z-coefficients) of the spline at the data points.
 * @param t The x-coordinate at which to evaluate the spline.
 * @return The interpolated y-coordinate at the given x-coordinate.
 * @throws std::runtime_error If the input point is outside the range of the data.
 */

/**
 * @fn std::vector<double> spline3_natural_eval(const std::vector<double> &x, const std::vector<double> &y, const std::deque<double> &z, const std::vector<double> &t)
 * @brief Evaluates the natural cubic spline at multiple points.
 * @param x The vector of x-coordinates of the data points.
 * @param y The vector of y-coordinates of the data points.
 * @param z The second derivatives (z-coefficients) of the spline at the data points.
 * @param t The vector of x-coordinates at which to evaluate the spline.
 * @return A vector of interpolated y-coordinates corresponding to the input x-coordinates.
 */
namespace ValLry{
    double normalCDF(double value)
    {
        return 0.5 * erfc(-value * M_SQRT1_2);
    }



    std::deque<double> trisol(int k, const std::vector<double> &a, const std::deque<double> &b, const std::deque<double> &c, const std::vector<double> &d){
        std::vector<double> l;
        std::vector<double> u;
        std::deque<double> x;

        //Check if the input sizes are correct
        if (a.size() != k + 1 || b.size() != k || c.size() != k || d.size() != k + 1) {
            throw std::invalid_argument("Input sizes do not match the expected dimensions.");
        }

        u.push_back(a[0]);
        for(int i = 0; i<k; i++){
            l.push_back(b[i]/u[i]);
            u.push_back(a[i+1] - l[i] * c[i]);
        }

        x.push_back(d[0]);
        for(int i = 1; i<k+1; i++){
            x.push_back(d[i] - l[i-1] * x[i-1]);
        }
        x[k] = x[k] / u[k];

        for(int i = k-1; i>-1; i--){
            x[i]=x[i]/u[i]-c[i]/u[i]*x[i+1];
        }
        return x;
    }   

    py::array_t<double> trisol(int k, const py::array_t<double> &a, const py::array_t<double> &b, const py::array_t<double> &c, const py::array_t<double> &d){
        // Convert input arrays to vectors
        std::vector<double> a_vec(a.data(), a.data() + a.size());
        std::deque<double> b_deque(b.data(), b.data() + b.size());
        std::deque<double> c_deque(c.data(), c.data() + c.size());
        std::vector<double> d_vec(d.data(), d.data() + d.size());

        // Call the existing trisol function
        std::deque<double> x_deque = trisol(k, a_vec, b_deque, c_deque, d_vec);

        // Convert the result back to a NumPy array
        return deque2numpy(x_deque);
    }


    std::deque<double> spline3_natural_coefs(const std::vector<double> &x, const std::vector<double> &y){

        std::deque<double> z;
        std::vector<double> a;
        std::vector<double> b;
        std::vector<double> d;
        std::deque<double> h;

        size_t n = x.size() - 1;

        for(size_t i = 0; i<n; i++){
            h.push_back(x[i+1]-x[i]);
            d.push_back((y[i+1]-y[i])/h[i]);
        }

        for(size_t i = 0; i<n-1; i++){
            a.push_back(2 * (h[i+1] + h[i]));
            b.push_back(6 * (d[i+1] - d[i]));
        }
        h.pop_front();
        h.pop_back();
        z = trisol( n - 2, a, h, h, b);
        z.push_back(0.);
        z.push_front(0.);

        return z;
    }

    double spline3_natural_eval(const std::vector<double> &x, const std::vector<double> &y, const std::deque<double> &z, double t){
        if(t < x[0] || t > x[x.size()-1]){ throw std::runtime_error("Point is not in the data range for interpolation."); }
        int i = 0;

        //find interpolation interval
        while(t >= x[i] && x[i] != x[x.size()-1]){ i++ ;}
        i--;

        double h = x[i+1] - x[i];

        return z[i+1]/6/h * (t - x[i]) * (t - x[i]) * (t - x[i]) + z[i]/6/h * (x[i+1] - t) * (x[i+1] - t) * (x[i+1] - t) + 
                (y[i+1]/h - z[i+1]/6 * h) * (t - x[i]) + (y[i]/h - z[i]/6 *h) * (x[i+1] - t);
    }

    std::vector<double> spline3_natural_eval(const std::vector<double> &x, const std::vector<double> &y, const std::deque<double> &z, const std::vector<double> &t){
        std::vector<double> spl;
        for(size_t i = 0; i < t.size(); i++){
            spl.push_back(spline3_natural_eval(x, y, z, t[i]));
        }
        return spl;
    }

    double tenorToYears(const std::string &tenor){
        double years = 0.0;
        size_t pos = 0;

        while (pos < tenor.size()) {
            size_t nextPos = pos;
            while (nextPos < tenor.size() && isdigit(tenor[nextPos])) {
            nextPos++;
            }

            if (nextPos == pos || nextPos >= tenor.size()) {
            throw std::invalid_argument("Invalid tenor format");
            }

            int value = std::stoi(tenor.substr(pos, nextPos - pos));
            char unit = tenor[nextPos];
            pos = nextPos + 1;

            switch (unit) {
            case 'Y':
                years += value;
                break;
            case 'M':
                years += value / 12.0;
                break;
            case 'D':
                years += value / 360.0;
                break;
            default:
                throw std::invalid_argument("Invalid tenor unit");
            }
        }

        return years;
    }

    std::vector<double> tenorToYears(const std::vector<std::string> &tenors){
        std::vector<double> years_vector;
        for(const auto& tenor : tenors){
            years_vector.push_back(tenorToYears(tenor));
        }
        return years_vector;
    }

    std::string tenorToString(double tenor){
        int years = static_cast<int>(tenor);
        double months = (tenor - years) * 12.0;
        int months_int = static_cast<int>(months);
        double days = (months - months_int) * 30.0;
        int days_int = static_cast<int>(days);

        std::string result;
        if(years > 0){
            result += std::to_string(years) + "Y";
        }
        if(months_int > 0){
            result += std::to_string(months_int) + "M";
        }
        if(days_int > 0){
            result += std::to_string(days_int) + "D";
        }
        return result;
    }

    std::vector<std::string> tenorToString(const std::vector<double> &tenors){
        std::vector<std::string> tenors_vector;
        for(const auto& tenor : tenors){
            tenors_vector.push_back(tenorToString(tenor));
        }
        return tenors_vector;
    }
    
    std::vector<std::vector<double>> choleskyDecomposition(const std::vector<std::vector<double>>& A) {
        size_t n = A.size();
        
        // Check if matrix is square
        for (const auto& row : A) {
            if (row.size() != n) {
                throw std::invalid_argument("Matrix must be square for Cholesky decomposition");
            }
        }
        
        // Check if matrix is symmetric
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (std::fabs(A[i][j] - A[j][i]) > 1e-10) {
                    throw std::invalid_argument("Matrix must be symmetric for Cholesky decomposition");
                }
            }
        }

        // Initialize the result matrix L with zeros
        std::vector<std::vector<double>> L(n, std::vector<double>(n, 0.0));
        
        // Compute the Cholesky decomposition
        for (size_t i = 0; i < n; ++i) {
            // Diagonal elements: l_{ii} = sqrt(a_{ii} - sum(l_{ik}^2)) for k=1 to i-1
            double sum = 0.0;
            for (size_t k = 0; k < i; ++k) {
                sum += L[i][k] * L[i][k];
            }
            
            double diag_value = A[i][i] - sum;
            
            // Check if matrix is positive definite
            if (diag_value <= 0) {
                throw std::runtime_error("Matrix is not positive definite");
            }
            
            L[i][i] = std::sqrt(diag_value);
            
            // Off-diagonal elements: l_{ji} = (a_{ji} - sum(l_{jk}*l_{ik})) / l_{ii} for j > i
            for (size_t j = i + 1; j < n; ++j) {
                sum = 0.0;
                for (size_t k = 0; k < i; ++k) {
                    sum += L[j][k] * L[i][k];
                }
                L[j][i] = (A[j][i] - sum) / L[i][i];
            }
        }

        return L;
    }
    
    py::array_t<double> choleskyDecomposition(const py::array_t<double>& A) {
        // Check input dimensions
        py::buffer_info buf_info = A.request();
        if (buf_info.ndim != 2) {
            throw std::runtime_error("Input must be a 2-dimensional array");
        }
        
        if (buf_info.shape[0] != buf_info.shape[1]) {
            throw std::runtime_error("Input must be a square matrix");
        }
        
        size_t n = buf_info.shape[0];
        
        // Convert numpy array to vector of vectors
        std::vector<std::vector<double>> matrix(n, std::vector<double>(n));
        double* ptr = static_cast<double*>(buf_info.ptr);
        
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                // Assuming row-major storage
                matrix[i][j] = ptr[i * n + j];
            }
        }
        
        // Perform Cholesky decomposition
        std::vector<std::vector<double>> L = choleskyDecomposition(matrix);
        
        // Create output array
        py::array_t<double> result = py::array_t<double>({n, n});
        py::buffer_info result_buf = result.request();
        double* result_ptr = static_cast<double*>(result_buf.ptr);
        
        // Fill output array
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result_ptr[i * n + j] = L[i][j];
            }
        }
        
        return result;
    }
    
}