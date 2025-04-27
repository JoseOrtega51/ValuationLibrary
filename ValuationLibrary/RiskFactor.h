#ifndef RISKFACTOR_H
#define RISKFACTOR_H

#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <memory>
#include <type_traits>

namespace ValLry {

    class RiskFactor {
    private:
        struct BaseHolder {
            virtual ~BaseHolder() = default;
        };

        template <typename T>
        struct Holder : BaseHolder {
            T value;
            explicit Holder(const T& val) : value(val) {}
        };

        std::tuple<std::string, std::shared_ptr<BaseHolder>> _RiskFactor;

    public:
        template <typename T>
        void setRiskFactor(const std::string& name, const T& value) {
            _RiskFactor = std::make_tuple(name, std::make_shared<Holder<T>>(value));
        }

        template <typename T>
        T getRiskFactorValue() const {
            auto holder = std::dynamic_pointer_cast<Holder<T>>(std::get<1>(_RiskFactor));
            if (!holder) {
                throw std::bad_cast();
            }
            return holder->value;
        }

        std::string getRiskFactorName() const {
            return std::get<0>(_RiskFactor);
        }
    };
}

#endif //RISKFACTOR_H