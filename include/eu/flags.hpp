#ifndef __EU_FLAGS_HPP
#define __EU_FLAGS_HPP

/// A flags enum must contain "EU_FLAGS_IDENTIFIER", with the only criteria being that in
/// order for "mask" to contain the correct value, it must immediately follow the highest flag
///
/// EXAMPLE
/// 
///	enum class chars_format 
/// {
///		scientific = 0x1,
///		fixed = 0x2,
///		hex = 0x4,
///		
///		EU_FLAGS_IDENTIFIER
/// };
///	

#include "utility.hpp"

#ifndef EU_FLAGS_IDENTIFIER
#define EU_FLAGS_IDENTIFIER _Flags
#endif

#ifdef __cpp_lib_concepts
#define __EU_ENABLE_IF_FLAGS(E) flags_enum E
#else
#define __EU_ENABLE_IF_FLAGS(E) typename E, typename = std::enable_if_t<is_flags_v<E>>
#endif

namespace eu
{

template <typename E, typename = void>
struct is_flags : std::false_type {};

template <typename E>
struct is_flags<E, std::void_t<decltype(E::EU_FLAGS_IDENTIFIER)>> : is_scoped_enum<E> {};

template <typename E>
constexpr bool is_flags_v = is_flags<E>::value;

#ifdef __cpp_lib_concepts

template <typename E>
concept flags_enum = is_flags_v<E>;

#endif

namespace flags
{

template <__EU_ENABLE_IF_FLAGS(E)>
struct empty : std::integral_constant<E, E{}> {};

template <__EU_ENABLE_IF_FLAGS(E)>
constexpr E empty_v = empty<E>::value;

template <__EU_ENABLE_IF_FLAGS(E)>
struct mask : std::integral_constant<E, static_cast<E>(((to_underlying(E::EU_FLAGS_IDENTIFIER) - 1) << 1) - 1)> {};

template <__EU_ENABLE_IF_FLAGS(E)>
constexpr E mask_v = mask<E>::value;

namespace operators
{

template <__EU_ENABLE_IF_FLAGS(E)>
constexpr E operator|(const E left, const E right) noexcept
{
	return static_cast<E>(to_underlying(left) | to_underlying(right));
}

template <__EU_ENABLE_IF_FLAGS(E)>
constexpr E operator&(const E left, const E right) noexcept
{
	return static_cast<E>(to_underlying(left) & to_underlying(right));
}

template <__EU_ENABLE_IF_FLAGS(E)>
constexpr E operator^(const E left, const E right) noexcept
{
	return static_cast<E>(to_underlying(left) ^ to_underlying(right));
}

template <__EU_ENABLE_IF_FLAGS(E)>
constexpr E operator~(const E value) noexcept
{
	return static_cast<E>(~to_underlying(value));
}

template <__EU_ENABLE_IF_FLAGS(E)>
constexpr E operator|=(E& left, const E right) noexcept
{
	return left = left | right;
}

template <__EU_ENABLE_IF_FLAGS(E)>
constexpr E operator&=(E& left, const E right) noexcept
{
	return left = left & right;
}

template <__EU_ENABLE_IF_FLAGS(E)>
constexpr E operator^=(E& left, const E right) noexcept
{
	return left = left ^ right;
}

} // operators

template <typename T, typename = std::enable_if_t<std::is_integral_v<T> || is_flags_v<T>>>
constexpr bool any(const T value) noexcept
{
	using namespace operators;
	return value != T();
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T> || is_flags_v<T>>>
constexpr bool has(const T mask, const T flag) noexcept
{
	using namespace operators;
	return (mask & flag) != T();
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T> || is_flags_v<T>>>
constexpr T& set(T& mask, const T flag) noexcept
{
	using namespace operators;
	return mask |= flag;
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T> || is_flags_v<T>>>
constexpr T& unset(T& mask, const T flag) noexcept
{
	using namespace operators;
	return mask &= ~flag;
}

} // flags

} // eu

#endif // __EU_FLAGS_HPP
