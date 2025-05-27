#ifndef __AA_EU_UTILITY_HPP
#define __AA_EU_UTILITY_HPP

#include <type_traits>

namespace aa
{

namespace enum_utils
{

template <typename E, typename = void>
struct is_scoped_enum : std::false_type {};

template <typename E>
struct is_scoped_enum<E, std::void_t<std::underlying_type_t<E>>> : std::bool_constant<
	std::is_enum_v<E> && !std::is_convertible_v<E, std::underlying_type_t<E>>
> {};

template <typename E>
constexpr bool is_scoped_enum_v = is_scoped_enum<E>::value;

template <typename E> requires is_scoped_enum_v<E>
constexpr auto to_underlying(const E e)
{
	return static_cast<std::underlying_type_t<E>>(e);
}

} // enum_utils

} // aa

#endif // __AA_EU_UTILITY_HPP
