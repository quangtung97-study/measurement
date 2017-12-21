#ifndef MEASUREMENT_DETAIL_MATH_HPP
#define MEASUREMENT_DETAIL_MATH_HPP

#include "util.hpp"

namespace measurement {
namespace detail {

constexpr double pow(double base, int n) {
    if (n == 0)
        return 1;

    double result = 1.0;
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            result *= base;
        }
    }
    else {
        for (int i = 0; i < -n; i++) {
            result /= base;
        }
    }
    return result;
}


} // namespace detail
} // namespace measurement

#endif
