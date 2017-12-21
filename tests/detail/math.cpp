#include <gmock/gmock.h>
#include <detail/math.hpp>
#include "../util/util.hpp"

using namespace measurement;
using namespace testing::util;

TEST(math, pow_double) {
    ASSERT_EQ(detail::pow(2, 3), 8);
    ASSERT_EQ(detail::pow(2.0, -2), 0.25);
}
