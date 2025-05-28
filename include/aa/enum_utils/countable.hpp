#ifndef __AA_EU_ENUM_COUNTABLE_HPP
#define __AA_EU_ENUM_COUNTABLE_HPP

#include "utility.hpp"

namespace aa
{

namespace enum_utils
{

template <typename E, typename = void>
struct is_countable_enum : std::false_type {};

template <typename E>
struct is_countable_enum<E, std::void_t<decltype(E::_Count)>> : std::bool_constant<is_scoped_enum_v<E>> {};

template <typename E>
constexpr bool is_countable_enum_v = is_countable_enum<E>::value;

template <typename E>
concept countable_enum = is_countable_enum_v<E>;

template <countable_enum E>
using enum_count = std::integral_constant<std::size_t, std::size_t(E::_Count)>;

template <countable_enum E>
constexpr std::size_t enum_count_v = enum_count<E>::value;

template <countable_enum E>
constexpr E invalid = E::_Count;

template <countable_enum E>
constexpr bool valid(const E e)
{
	return to_underlying(e) >= std::underlying_type_t<E>{} && to_underlying(e) < to_underlying(invalid<E>);
}

} // enum_utils

} // aa

#endif // __AA_EU_ENUM_COUNTABLE_HPP
