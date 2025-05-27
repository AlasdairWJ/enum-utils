#ifndef __AA_EU_FLAGS_HPP
#define __AA_EU_FLAGS_HPP

#include "utility.hpp"

#define enum_flag(E) template <> struct aa::enum_utils::is_flag<E> : std::true_type {}

namespace aa
{

namespace enum_utils
{

template <typename E>
struct is_flag;

template <typename E>
constexpr bool is_flag_v = is_flag<E>::value;

template <typename E>
concept enum_flag = is_flag_v<E>;

namespace flags
{

template <enum_flag E>
constexpr bool empty(const E value) noexcept
{
	return value == E{};
}

template <enum_flag E>
constexpr bool has(const E mask, const E flag) noexcept
{
	return (mask & flag) != E{};
}

template <enum_flag E>
constexpr E& set(E& mask, const E flag) noexcept
{
	return mask |= flag;
}

template <enum_flag E>
constexpr E& unset(E& mask, const E flag) noexcept
{
	return mask &= ~flag;
}

} // flags

} // enum_utils

} // aa

template <aa::enum_utils::enum_flag E>
constexpr E operator|(const E left, const E right) noexcept
{
	return static_cast<E>(aa::enum_utils::to_underlying(left) | aa::enum_utils::to_underlying(right));
}

template <aa::enum_utils::enum_flag E>
constexpr E operator&(const E left, const E right) noexcept
{
	return static_cast<E>(aa::enum_utils::to_underlying(left) & aa::enum_utils::to_underlying(right));
}

template <aa::enum_utils::enum_flag E>
constexpr E operator^(const E left, const E right) noexcept
{
	return static_cast<E>(aa::enum_utils::to_underlying(left) ^ aa::enum_utils::to_underlying(right));
}

template <aa::enum_utils::enum_flag E>
constexpr E operator~(const E value) noexcept
{
	return static_cast<E>(~aa::enum_utils::to_underlying(value));
}

template <aa::enum_utils::enum_flag E>
constexpr E operator|=(E& left, const E right) noexcept
{
	return left = left | right;
}

template <aa::enum_utils::enum_flag E>
constexpr E operator&=(E& left, const E right) noexcept
{
	return left = left & right;
}

template <aa::enum_utils::enum_flag E>
constexpr E operator^=(E& left, const E right) noexcept
{
	return left = left ^ right;
}

#endif // __AA_EU_FLAGS_HPP
