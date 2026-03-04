#ifndef __EU_VARIANT_HPP
#define __EU_VARIANT_HPP

#include "countable.hpp"
#include <variant>

namespace eu
{

template <countable_enum E, typename... Ts>
struct variant : std::variant<Ts...>
{
	using base_type = std::variant<Ts...>;
	using this_type = variant<E, Ts...>;

	template <typename T>
	variant(T&& value)
		: base_type{ value }
	{
	}

	template <typename T>
	this_type& operator=(T&& value)
	{
		base_type::operator=(value);
		return *this;
	}

	E index() const noexcept
	{
		return static_cast<E>(base_type::index());
	}

	this_type& index(const E index)
	{
		int ix = 0;
		((ix++ == sphere::to_underlying(index) && (operator=(Ts{}), true)) || ...);
		return *this;
	}
};

} // eu

#endif // __EU_VARIANT_HPP