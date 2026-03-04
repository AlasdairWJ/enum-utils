#ifndef __EU_UTILITY_HPP
#define __EU_UTILITY_HPP

#include <type_traits>

namespace eu
{

template <typename E, typename = void>
struct is_scoped_enum : std::false_type {};

template <typename E>
struct is_scoped_enum<E, std::void_t<std::underlying_type_t<E>>> : std::bool_constant<!std::is_convertible_v<E, std::underlying_type_t<E>>> {};

template <typename E>
constexpr bool is_scoped_enum_v = is_scoped_enum<E>::value;

template <typename E, typename = std::enable_if_t<std::is_enum_v<E>>>
constexpr std::underlying_type_t<E> to_underlying(const E e)
{
	return static_cast<std::underlying_type_t<E>>(e);
}

} // eu

#endif // __EU_UTILITY_HPP
