#include <gmock/gmock.h>
#include <detail/element.hpp>
#include "../util/util.hpp"

using namespace measurement::detail;
using namespace testing::util;

TEST(element, SI_base_units) {
    assert_has_not_value_member<size_of<int>>();
    assert_has_value_member<size_of<si_length>>();
    assert_equals<size_of<si_length>::value, 7>();

    assert_same<si_length, number_sequence<1, 0, 0, 0, 0, 0, 0>>();
    assert_same<si_mass, number_sequence<0, 1, 0, 0, 0, 0, 0>>();
    assert_same<si_time, number_sequence<0, 0, 1, 0, 0, 0, 0>>();
    assert_same<si_current, number_sequence<0, 0, 0, 1, 0, 0, 0>>();
    assert_same<si_temperature, number_sequence<0, 0, 0, 0, 1, 0, 0>>();
    assert_same<si_mole, number_sequence<0, 0, 0, 0, 0, 1, 0>>();
    assert_same<si_candela, number_sequence<0, 0, 0, 0, 0, 0, 1>>();
}

TEST(element, has_same_dimension) {
    static_assert(
            has_same_dimension<si_length, si_length>::value, 
            "Has the same dimension" 
    );
    assert_has_not_value_member<has_same_dimension<int, int>>();
    static_assert(
            !has_same_dimension<si_time, si_mole>::value,
            "Has not the same dimension"
    );
}

TEST(element, dimension_mul) {
    using dim1 = dimension<1, 0, 0, 1, 2, 0, 0>;
    using dim2 = dimension<2, 0, 1, -2, 1, 0, 0>;
    using result = dimension<3, 0, 1, -1, 3, 0, 0>;
    assert_same<dimension_mul_t<dim1, dim2>, result>();

    using dimx = dimension<2, 0, 3, 4>;
    assert_has_not_type_member<dimension_mul<dimx, dimx>>();
    assert_has_not_type_member<dimension_mul<dim1, dimx>>();
    assert_has_not_type_member<dimension_mul<int, float>>();
}

TEST(element, dimension_div) {
    using dim1 = dimension<1, 0, 0, 1, 2, 0, 0>;
    using dim2 = dimension<2, 0, 1, -2, 1, 0, 0>;
    using result = dimension<-1, 0, -1, 3, 1, 0, 0>;
    assert_same<dimension_div_t<dim1, dim2>, result>();

    using dimx = dimension<2, 0, 3, 4>;
    assert_has_not_type_member<dimension_div<dim1, dimx>>();
    assert_has_not_type_member<dimension_div<float, int>>();
}

TEST(element, dimension_pow) {
    using dim = dimension<1, 0, 0, 1, 2, 0, 0>;
    using result1 = dimension<2, 0, 0, 2, 4, 0, 0>;
    using result2 = dimension<-2, 0, 0, -2, -4, 0, 0>;
    using result3 = dimension<0, 0, 0, 0, 0, 0, 0>;
    assert_same<dimension_pow_t<dim, 2>, result1>();
    assert_same<dimension_pow_t<dim, -2>, result2>();
    assert_same<dimension_pow_t<dim, 0>, result3>();
}
