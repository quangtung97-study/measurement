#ifndef MEASUREMENT_DETAIL_ELEMENT_HPP
#define MEASUREMENT_DETAIL_ELEMENT_HPP

#include "util.hpp"

namespace measurement {
namespace detail {

template <int ... Nums>
struct number_sequence {
    static constexpr size_t size = sizeof...(Nums);
};

template <int ... Nums>
using dimension = number_sequence<Nums...>;


using si_length = number_sequence<1, 0, 0, 0, 0, 0, 0>;
using si_mass = number_sequence<0, 1, 0, 0, 0, 0, 0>;
using si_time = number_sequence<0, 0, 1, 0, 0, 0, 0>;
using si_current = number_sequence<0, 0, 0, 1, 0, 0, 0>;
using si_temperature = number_sequence<0, 0, 0, 0, 1, 0, 0>;
using si_mole = number_sequence<0, 0, 0, 0, 0, 1, 0>;
using si_candela = number_sequence<0, 0, 0, 0, 0, 0, 1>;


template <typename Sequence, typename = void>
struct size_of {};

template <typename Sequence>
struct size_of<Sequence, void_t<decltype(Sequence::size)>> {
    static constexpr size_t value = Sequence::size;
};


template <typename DimA, typename DimB>
struct has_same_dimension {};

template <int ... NumsA, int ... NumsB>
struct has_same_dimension<dimension<NumsA...>, dimension<NumsB...>>
    : std::false_type {};

template <int ... Nums>
struct has_same_dimension<dimension<Nums...>, dimension<Nums...>>
    : std::true_type {};


template <typename DimA, typename DimB, typename = void>
struct dimension_mul {};

template <int ... NumsA, int ... NumsB>
struct dimension_mul<
        dimension<NumsA...>, 
        dimension<NumsB...>,
        std::enable_if_t<sizeof...(NumsA) == 7 && sizeof...(NumsB) == 7>> {
    using type = dimension<NumsA + NumsB ...>;
};

template <typename DimA, typename DimB>
using dimension_mul_t = typename dimension_mul<DimA, DimB>::type;


template <typename DimA, typename DimB, typename = void>
struct dimension_div {};

template <int ... NumsA, int ... NumsB>
struct dimension_div<
        dimension<NumsA...>, 
        dimension<NumsB...>,
        std::enable_if_t<sizeof...(NumsA) == 7 && sizeof...(NumsB) == 7>>
{
    using type = dimension<NumsA - NumsB ...>;
};

template <typename DimA, typename DimB>
using dimension_div_t = typename dimension_div<DimA, DimB>::type;


template <typename Dim, int N, typename = void>
struct dimension_pow {};

template <int ... Nums, int N>
struct dimension_pow<
        dimension<Nums...>, N,
        std::enable_if_t<sizeof...(Nums) == 7>>
{
    using type = dimension<Nums * N...>;
};

template <typename Dim, int N>
using dimension_pow_t = typename dimension_pow<Dim, N>::type;

} // namespace detail
} // namespace measurement

#endif
