#ifndef __AA_EU_ENUM_RANGE_HPP
#define __AA_EU_ENUM_RANGE_HPP

#include "countable.hpp"

namespace aa
{

namespace enum_utils
{

template <typename E> requires std::is_enum_v<E>
struct enum_range_iterator
{
	using self_type = enum_range_iterator<E>;

	using value_type = E;

	constexpr enum_range_iterator(const E value) noexcept
		: _value{ static_cast<underlying_type>(value) }
	{
	}

	constexpr E operator*() const noexcept
	{
		return static_cast<E>(_value);
	}

	constexpr self_type& operator++() noexcept
	{
		_value++;
		return *this;
	}

	constexpr self_type operator++(int) noexcept
	{
		const auto temp = *this;
		_value++;
		return temp;
	}

	constexpr self_type& operator--() noexcept
	{
		_value--;
		return *this;
	}

	constexpr self_type operator--(int) noexcept
	{
		const auto temp = *this;
		_value--;
		return temp;
	}

	constexpr bool operator==(const self_type& other) const noexcept
	{
		return _value == other._value;
	}

	constexpr bool operator!=(const self_type& other) const noexcept
	{
		return _value != other._value;
	}

private:
	using underlying_type = std::underlying_type_t<E>;

	underlying_type _value;
};

template <typename It>
struct range_t
{
	constexpr range_t(const It b, const It e) noexcept
		: _begin{ b }
		, _end{ e }
	{
	}

	constexpr It begin() const noexcept { return _begin; }
	constexpr It end() const noexcept { return _end; }

private:
	It _begin, _end;
};

template <countable_enum E>
constexpr auto enum_range() noexcept
{
	return range_t<enum_range_iterator<E>>{ { E{} }, { invalid<E> } };
}

template <typename E> requires std::is_enum_v<E>
constexpr auto enum_range(const E end) noexcept
{
	return range_t<enum_range_iterator<E>>{ { E{} }, { end } };
}

template <typename E> requires std::is_enum_v<E>
constexpr auto enum_range(const E begin, const E end) noexcept
{
	return range_t<enum_range_iterator<E>>{ { begin }, { end } };
}

} // enum_utils

} // aa

#endif __AA_EU_ENUM_RANGE_HPP
