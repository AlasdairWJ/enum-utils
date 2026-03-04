#ifndef __EU_COUNTABLE_HPP
#define __EU_COUNTABLE_HPP

/// A countable enum must be contiguous from 0, and end with "EU_COUNTABLE_IDENTIFIER"
/// 
/// EXAMPLE
/// 
/// enum class Colours
/// {
/// 	Red,
/// 	Green,
/// 	Blue,
/// 	
/// 	EU_COUNTABLE_IDENTIFIER
/// };
/// 

#include "utility.hpp"

#ifndef EU_COUNTABLE_IDENTIFIER
#define EU_COUNTABLE_IDENTIFIER _Count

#endif

#ifdef __cpp_lib_concepts
#define EU_ENABLE_IF_COUNTABLE(E) countable_enum E
#else
#define EU_ENABLE_IF_COUNTABLE(E) typename E, typename = std::enable_if_t<is_countable_enum_v<E>>
#endif

namespace eu
{

template <typename E, typename = void>
struct is_countable_enum : std::false_type {};

template <typename E>
struct is_countable_enum<E, std::void_t<decltype(E::EU_COUNTABLE_IDENTIFIER)>> : is_scoped_enum<E> {};

template <typename E>
constexpr bool is_countable_enum_v = is_countable_enum<E>::value;

#ifdef __cpp_lib_concepts

template <typename E>
concept countable_enum = is_countable_enum_v<E>;

#endif

template <EU_ENABLE_IF_COUNTABLE(E)>
struct enum_count : std::integral_constant<std::size_t, std::size_t(E::EU_COUNTABLE_IDENTIFIER)> {};

template <EU_ENABLE_IF_COUNTABLE(E)>
constexpr std::size_t enum_count_v = enum_count<E>::value;

template <EU_ENABLE_IF_COUNTABLE(E)>
struct invalid : std::integral_constant<E, E::EU_COUNTABLE_IDENTIFIER> {};

template <EU_ENABLE_IF_COUNTABLE(E)>
constexpr E invalid_v = invalid<E>::value;

template <EU_ENABLE_IF_COUNTABLE(E)>
constexpr bool valid(const E e)
{
	return to_underlying(e) >= to_underlying(E{}) && to_underlying(e) < to_underlying(invalid_v<E>);
}

} // eu

#endif // __EU_COUNTABLE_HPP
