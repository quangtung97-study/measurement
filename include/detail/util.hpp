#ifndef MEASUREMENT_DETAIL_UTIL_HPP
#define MEASUREMENT_DETAIL_UTIL_HPP

#include <type_traits>

using std::size_t;

namespace measurement {
namespace detail {

template <typename ...>
using void_t = void;

} // namespace detail
} // namespace measurement

#endif
