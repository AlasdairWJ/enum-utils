#ifndef __AA_EU_ENUM_ARRAY_HPP
#define __AA_EU_ENUM_ARRAY_HPP

#include "countable.hpp"
#include "range.hpp"

#include <array>

namespace aa
{

namespace enum_utils
{

template <
	typename E,
	typename T,
	std::size_t Size = enum_count_v<E>
> requires std::is_enum_v<E>
struct enum_array : std::array<T, Size>
{
protected:
	using std::array<T, Size>::operator[];

public:
	using self_type = enum_array<E, T, Size>;

	using index_type = E;

	constexpr T& operator[](const E index) noexcept
	{
		return operator[](static_cast<std::size_t>(index));
	}

	constexpr const T& operator[](const E index) const noexcept
	{
		return operator[](static_cast<std::size_t>(index));
	}

	static constexpr auto indices()
	{
		return enum_range(static_cast<E>(Size));
	}
};

template <
	typename E,
	typename T,
	std::size_t Size = enum_count_v<E>
>
bool operator==(const enum_array<E, T, Size>& lhs, const enum_array<E, T, Size>& rhs)
{
	return std::equal(lhs.data(), lhs.data() + lhs.size(), rhs.data());
}

template <
	typename E,
	typename T,
	std::size_t Size = enum_count_v<E>
>
bool operator!=(const enum_array<E, T, Size>& lhs, const enum_array<E, T, Size>& rhs)
{
	return !(lhs == rhs);
}

} // enum_utils

} // aa,

#endif // __AA_EU_ENUM_ARRAY_HPP
