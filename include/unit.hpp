#ifndef MEASUREMENT_UNIT_HPP
#define MEASUREMENT_UNIT_HPP

#include <ratio>
#include "detail/element.hpp"
#include "detail/math.hpp"

namespace measurement {

template <typename Ratio, int Exp, typename Dim>
class unit {
private:
    double value_;

public:
    explicit unit(): value_{0} {}

    explicit unit(double value): value_{value} {}

    double operator () () const { return value_; }

    unit(const unit& other) {
        value_ = other.value_;
    }

    unit(unit&& other) {
        value_ = other.value_;
    }

    unit& operator = (const unit& other) {
        value_ = other.value_;
        return *this;
    }

    unit& operator = (unit&& other) {
        value_ = other.value_;
        return *this;
    }

    // Conversion operator to another unit type
    template <typename RatioB, int ExpB, typename DimB,
             typename = detail::void_t<
                 std::enable_if_t<
                 std::is_same<Dim, DimB>::value>>>
    operator unit<RatioB, ExpB, DimB> () const {
        using ReturnType = unit<RatioB, ExpB, DimB>;
        using DiffRatio = std::ratio_divide<Ratio, RatioB>;
        constexpr int diff_exp = Exp - ExpB;
        constexpr double ratio = 
                detail::pow(10, diff_exp) *
                (double)DiffRatio::num / DiffRatio::den;
            
        return ReturnType{ratio * value_};
    }

    // Conversion operator to double
    template <typename U = Dim>
    operator typename std::enable_if<
        std::is_same<U, detail::si_scalar>::value, double>::type () const {
        using DiffRatio = std::ratio_divide<Ratio, std::ratio<1, 1>>;
        constexpr int diff_exp = Exp - 0;
        constexpr double ratio = 
                detail::pow(10, diff_exp) *
                (double)DiffRatio::num / DiffRatio::den;
        return ratio * value_;
    }

    unit operator + (const unit& other) const {
        return unit{value_ + other.value_};
    }

    unit operator + (unit&& other) const {
        return unit{value_ + other.value_};
    }

    unit& operator += (const unit& other) {
        value_ += other.value_;
        return *this;
    }

    unit& operator += (unit&& other) {
        value_ += other.value_;
        return *this;
    }

    unit operator - (const unit& other) const {
        return unit{value_ - other.value_};
    }

    unit operator - (unit&& other) const {
        return unit{value_ - other.value_};
    }

    unit& operator -= (const unit& other) {
        value_ -= other.value_;
        return *this;
    }

    unit& operator -= (unit&& other) {
        value_ -= other.value_;
        return *this;
    }

    unit operator - () const {
        return unit{-value_};
    }

    template <typename RatioB, int ExpB, typename DimB>
    auto operator * (const unit<RatioB, ExpB, DimB>& other) const {
        using ReturnDim = detail::dimension_mul_t<Dim, DimB>;
        using ReturnRatio = std::ratio_multiply<Ratio, RatioB>;
        constexpr int return_exp = Exp + ExpB;
        using ReturnType = unit<ReturnRatio, return_exp, ReturnDim>;
        return ReturnType{value_ * other()};
    }

    template <typename RatioB, int ExpB, typename DimB>
    auto operator * (unit<RatioB, ExpB, DimB>&& other) const {
        using ReturnDim = detail::dimension_mul_t<Dim, DimB>;
        using ReturnRatio = std::ratio_multiply<Ratio, RatioB>;
        constexpr int return_exp = Exp + ExpB;
        using ReturnType = unit<ReturnRatio, return_exp, ReturnDim>;
        return ReturnType{value_ * other()};
    }

    template <typename RatioB, int ExpB, typename DimB>
    auto operator / (const unit<RatioB, ExpB, DimB>& other) const {
        using ReturnDim = detail::dimension_div_t<Dim, DimB>;
        using ReturnRatio = std::ratio_divide<Ratio, RatioB>;
        constexpr int return_exp = Exp - ExpB;
        using ReturnType = unit<ReturnRatio, return_exp, ReturnDim>;
        return ReturnType{value_ / other()};
    }

    template <typename RatioB, int ExpB, typename DimB>
    auto operator / (unit<RatioB, ExpB, DimB>&& other) const {
        using ReturnDim = detail::dimension_div_t<Dim, DimB>;
        using ReturnRatio = std::ratio_divide<Ratio, RatioB>;
        constexpr int return_exp = Exp - ExpB;
        using ReturnType = unit<ReturnRatio, return_exp, ReturnDim>;
        return ReturnType{value_ / other()};
    }

    unit operator * (double k) const {
        return unit{value_ * k};
    }

    unit operator / (double k) const {
        return unit{value_ / k};
    }

    bool operator == (const unit& other) const {
        return value_ == other.value_;
    }

    bool operator == (unit&& other) const {
        return value_ == other.value_;
    }

    bool operator != (const unit& other) const {
        return value_ != other.value_;
    }

    bool operator != (unit&& other) const {
        return value_ != other.value_;
    }

    bool operator < (const unit& other) const {
        return value_ < other.value_;
    }

    bool operator < (unit&& other) const {
        return value_ < other.value_;
    }

    bool operator > (const unit& other) const {
        return value_ > other.value_;
    }

    bool operator > (unit&& other) const {
        return value_ > other.value_;
    }

    bool operator <= (const unit& other) const {
        return value_ <= other.value_;
    }

    bool operator <= (unit&& other) const {
        return false <= other.value_;
    }

    bool operator >= (const unit& other) const {
        return value_ >= other.value_;
    }

    bool operator >= (unit&& other) const {
        return value_ >= other.value_;
    }

};

template <typename Ratio, int Exp, typename Dim>
auto operator * (double k, const unit<Ratio, Exp, Dim>& other) {
    return unit<Ratio, Exp, Dim>{k * other()};
}

template <typename Ratio, int Exp, typename Dim>
auto operator * (double k, unit<Ratio, Exp, Dim>&& other) {
    return unit<Ratio, Exp, Dim>{k * other()};
}

using kilometres = unit<std::ratio<1>, 3, detail::si_length>;
using metres = unit<std::ratio<1>, 0, detail::si_length>;

using seconds = unit<std::ratio<1>, 0, detail::si_time>;
using milliseconds = unit<std::ratio<1>, -3, detail::si_time>;
using microseconds = unit<std::ratio<1>, -6, detail::si_time>;
using hours = unit<std::ratio<36, 10>, 3, detail::si_time>;

// Velocity
using velocity = detail::dimension_div_t<
        detail::si_length, detail::si_time>;
using metres_per_second = unit<std::ratio<1>, 0, velocity>;
using kilometres_per_hour = unit<std::ratio<10, 36>, 0, velocity>;

// Scalar
using scalar = unit<std::ratio<1, 1>, 0, detail::si_scalar>;

} // namespace measurement

#endif
