#ifndef __EU_RANGE_HPP
#define __EU_RANGE_HPP

#include "countable.hpp"

namespace eu
{

template <typename E, typename = std::enable_if_t<std::is_enum_v<E>>>
struct range
{
	struct iterator
	{
	private:
		using underlying_type = std::underlying_type_t<E>;

	public:
		using value_type = E;

		constexpr iterator(const E value) noexcept
			: _value{ to_underlying(value) }
		{
		}

		constexpr E operator*() const noexcept
		{
			return static_cast<E>(_value);
		}

		constexpr iterator& operator++() noexcept
		{
			_value++;
			return *this;
		}

		constexpr iterator operator++(int) noexcept
		{
			const auto temp = *this;
			_value++;
			return temp;
		}

		constexpr iterator& operator--() noexcept
		{
			_value--;
			return *this;
		}

		constexpr iterator operator--(int) noexcept
		{
			const auto temp = *this;
			_value--;
			return temp;
		}

		constexpr bool operator==(const iterator& other) const noexcept
		{
			return _value == other._value;
		}

		constexpr bool operator!=(const iterator& other) const noexcept
		{
			return _value != other._value;
		}

	private:
		underlying_type _value;
	};

	template <typename = std::enable_if_t<is_countable_enum_v<E>>>
	constexpr range() noexcept
		: _begin{ E{} }
		, _end{ invalid_v<E> }
	{
	}

	constexpr range(const E end ) noexcept
		: _begin{ E{} }
		, _end{ end }
	{
	}

	constexpr range(const E begin, const E end) noexcept
		: _begin{ begin }
		, _end{ end }
	{
	}

	constexpr iterator begin() const noexcept { return _begin; }
	constexpr iterator end() const noexcept { return _end; }

private:
	iterator _begin, _end;
};

} // eu

#endif // __EU_RANGE_HPP