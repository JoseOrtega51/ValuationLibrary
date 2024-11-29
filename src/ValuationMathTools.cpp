#include "ValuationMathTools.h"

namespace ValLry{
    double normalCDF(double value)
    {
        return 0.5 * erfc(-value * M_SQRT1_2);
    }

    std::deque<double> trisol(int k, const std::vector<double> &a, const std::deque<double> &c, const std::vector<double> &b){
        std::vector<double> l;
        std::vector<double> u;
        std::deque<double> x;

        u.push_back(a[0]);
        for(int i = 0; i<k; i++){
            l.push_back(c[i]/u[i]);
            u.push_back(a[i+1] - l[i] * c[i]);
        }

        x.push_back(b[0]);
        for(int i = 1; i<k+1; i++){
            x.push_back(b[i] - l[i-1] * x[i-1]);
        }
        x[k] = x[k] / u[k];

        for(int i = k-1; i>-1; i--){
            x[i]=x[i]/u[i]-l[i]*x[i+1];
        }
        return x;
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
        z = trisol( n - 2, a, h, b);
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
}