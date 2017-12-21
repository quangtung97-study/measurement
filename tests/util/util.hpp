#ifndef TESTING_UTIL_HPP
#define TESTING_UTIL_HPP

#include <type_traits>

namespace testing {
namespace util {

template <typename ... Types>
using void_t = void;

template <typename T, typename U>
struct assert_same {
    static_assert(std::is_same<T, U>::value, "Not is the same");
};

template <int I, int J>
struct assert_equals {
    static_assert(I == J, "Not equal");
};

template <typename Type, typename = void>
struct has_type_member: std::false_type {};

template <typename Type>
struct has_type_member<Type, void_t<typename Type::type>>
    : std::true_type {};

template <typename Type, typename = void>
struct has_value_member: std::false_type {};

template <typename Type>
struct has_value_member<Type, void_t<decltype(Type::value)>>
    : std::true_type {};

template <typename Type>
struct assert_has_type_member {
    static_assert(has_type_member<Type>::value, "Has a type member");
};

template <typename Type>
struct assert_has_not_type_member {
    static_assert(!has_type_member<Type>::value, "Has not a type member");
};

template <typename Type>
struct assert_has_value_member {
    static_assert(has_value_member<Type>::value, "Has a value member");
};

template <typename Type>
struct assert_has_not_value_member {
    static_assert(!has_value_member<Type>::value, "Has not a value member");
};

} // namespace util
} // namespace testing


#endif
