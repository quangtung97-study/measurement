#include <gmock/gmock.h>
#include <unit.hpp>
#include "util/util.hpp"
#include <ratio>

using namespace measurement;
using namespace testing::util;

TEST(unit, definitions) {
    assert_same<metres, unit<std::ratio<1, 1>, 0, detail::si_length>>();

    assert_same<seconds, unit<std::ratio<1, 1>, 0, detail::si_time>>();
    assert_same<milliseconds, 
        unit<std::ratio<1, 1>, -3, detail::si_time>>();
    assert_same<microseconds, 
        unit<std::ratio<1, 1>, -6, detail::si_time>>();

    using velocity = detail::dimension_div_t<
            detail::si_length, detail::si_time>;
    assert_same<metres_per_second, 
        unit<std::ratio<1, 1>, 0, velocity>>();
    assert_same<kilometres_per_hour, 
        unit<std::ratio<10, 36>, 0, velocity>>();
}

TEST(unit, constructor) {
    metres value1{100};
    metres value2;

    ASSERT_EQ(value1(), 100);
    ASSERT_EQ(value2(), 0);
}

TEST(unit, copy_constructor) {
    milliseconds value1{5};
    milliseconds value2 = value1;
    ASSERT_EQ(value2(), 5);
}

TEST(unit, move_constructor) {
    milliseconds value = milliseconds{4};
    ASSERT_EQ(value(), 4);
}

TEST(unit, copy_assigment) {
    milliseconds value1{3};
    milliseconds value2;
    value2 = value1;
    ASSERT_EQ(value2(), 3);
}

TEST(unit, move_assigment) {
    milliseconds value;
    value = milliseconds{5};
    ASSERT_EQ(value(), 5);
}

TEST(unit, conversion) {
    seconds value1{3};
    milliseconds value2;
    value2 = value1;
    ASSERT_EQ(value2(), 3000);
}

TEST(unit, conversion_velocity) {
    kilometres_per_hour v = metres_per_second{3};
    ASSERT_DOUBLE_EQ(v(), 3 * 3.6);
}

TEST(unit, add) {
    microseconds value;
    microseconds valueA{20};
    microseconds valueB{30};

    value = seconds{3} + milliseconds{5};
    ASSERT_DOUBLE_EQ(value(), 3005000);

    value = valueA + valueB;
    ASSERT_DOUBLE_EQ(value(), 50);
}

TEST(unit, minus) {
    microseconds value;
    microseconds valueA{20};
    microseconds valueB{30};

    value = seconds{3} - milliseconds{5};
    ASSERT_DOUBLE_EQ(value(), 2995000);

    value = milliseconds{5} - seconds{3};
    ASSERT_DOUBLE_EQ(value(), -2995000);

    value = valueA - valueB;
    ASSERT_DOUBLE_EQ(value(), -10);
}

TEST(unit, negative) {
    microseconds value;
    value = -microseconds{20};
    ASSERT_EQ(value(), -20);
}

TEST(unit, plus_assign) {
    microseconds value{30};
    microseconds x{10};
    value += milliseconds{10};
    value += x;
    ASSERT_EQ(value(), 10'040);
}

TEST(unit, minus_assign) {
    microseconds value{30};
    microseconds x{10};
    value -= milliseconds{10};
    value -= x;
    ASSERT_EQ(value(), 30 - 10'000 - 10);
}

TEST(unit, multiply_right_dimension) {
    using dim1 = detail::dimension<2, 0, 1, 3, 0, 0, -2>;
    using dim2 = detail::dimension<1, 2, 0, 2, 0, 1, 0>;
    using result = detail::dimension<3, 2, 1, 5, 0, 1, -2>;

    using ratio1 = std::ratio<1>;
    using unit1 = unit<ratio1, 0, dim1>;
    using unit2 = unit<ratio1, 0, dim2>;

    assert_same<
        unit<ratio1, 0, result>,
        decltype(std::declval<unit1>() * std::declval<unit2>())>();
}

TEST(unit, multiply_right_ratio) {
    using dim = detail::dimension<2, 0, 1, 3, 0, 0, -2>;
    using result_dim = detail::dimension_mul_t<dim, dim>;

    using ratio1 = std::ratio<7, 3>;
    using ratio2 = std::ratio<5, 14>;
    using result = std::ratio<5, 6>;
    using unit1 = unit<ratio1, 0, dim>;
    using unit2 = unit<ratio2, 0, dim>;

    assert_same<
        unit<result, 0, result_dim>,
        decltype(std::declval<unit1>() * std::declval<unit2>())>();
}

TEST(unit, multiply_right_exp) {
    using dim = detail::dimension<2, 0, 1, 3, 0, 0, -2>;
    using result_dim = detail::dimension_mul_t<dim, dim>;

    using ratio = std::ratio<7, 3>;
    using result = std::ratio_multiply<ratio, ratio>;
    using unit1 = unit<ratio, 10, dim>;
    using unit2 = unit<ratio, 3, dim>;

    assert_same<
        unit<result, 13, result_dim>,
        decltype(std::declval<unit1>() * std::declval<unit2>())>();
}

TEST(unit, multiply) {
    metres_per_second v{5};
    milliseconds t{3000};
    metres S = v * t;
    ASSERT_DOUBLE_EQ(S(), 15);

    S = v * milliseconds{2000};
    ASSERT_DOUBLE_EQ(S(), 10);
}

TEST(unit, divide) {
    metres S{15'000};
    hours t{3};
    kilometres_per_hour v = S / t;
    ASSERT_DOUBLE_EQ(v(), 5);

    v = S / hours{1};
    ASSERT_DOUBLE_EQ(v(), 15);
}

TEST(unit, multiply_with_scalar) {
    metres_per_second v{5};
    v = v * 3;
    ASSERT_DOUBLE_EQ(v(), 15);

    v = 4 * v;
    ASSERT_DOUBLE_EQ(v(), 15 * 4);
}

TEST(unit, divide_with_scalar) {
    metres_per_second v{15};
    v = v / 3;
    ASSERT_DOUBLE_EQ(v(), 5);

    kilometres_per_hour v1 = v;
    ASSERT_DOUBLE_EQ(v1(), 5 * 3.6);
}
