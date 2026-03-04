#ifndef __EU_ARRAY_HPP
#define __EU_ARRAY_HPP

#include "countable.hpp"
#include "range.hpp"

#include <array>

namespace eu
{

template <typename E, typename T, std::size_t Size = enum_count_v<E>>
struct array : std::array<T, Size>
{
private:
	using base_type = std::array<T, Size>;

public:
	constexpr std::size_t size() const noexcept
	{
		return Size;
	}

	constexpr T& operator[](const E index) noexcept
	{
		return base_type::operator[](static_cast<std::size_t>(index));
	}

	constexpr const T& operator[](const E index) const noexcept
	{
		return base_type::operator[](static_cast<std::size_t>(index));
	}

	static constexpr auto indices()
	{
		return range{ static_cast<E>(Size) };
	}
};

template <typename E, typename T, std::size_t Size = enum_count_v<E>>
bool operator==(const array<E, T, Size>& lhs, const array<E, T, Size>& rhs)
{
	return std::equal(lhs.data(), lhs.data() + lhs.size(), rhs.data());
}

template <
	typename E,
	typename T,
	std::size_t Size = enum_count_v<E>
>
bool operator!=(const array<E, T, Size>& lhs, const array<E, T, Size>& rhs)
{
	return !(lhs == rhs);
}

} // eu

#endif // __EU_ARRAY_HPP
