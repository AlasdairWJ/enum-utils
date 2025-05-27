#ifndef __AA_EU_ENUM_VARIANT_HPP
#define __AA_EU_ENUM_VARIANT_HPP

#include "countable.hpp"
#include <variant>

namespace aa
{

namespace enum_utils
{

template <countable_enum E, typename... Ts>
struct enum_variant : std::variant<Ts...>
{
	using base_type = std::variant<Ts...>;
	using self_type = enum_variant<E, Ts...>;

	template <typename T>
	enum_variant(T&& value)
		: base_type{ value }
	{
	}

	template <typename T>
	self_type& operator=(T&& value)
	{
		base_type::operator=(value);
		return *this;
	}

	E index() const noexcept
	{
		return static_cast<E>(base_type::index());
	}

	self_type& index(const E index)
	{
		int ix = 0;
		((ix++ == sphere::to_underlying(index) && (operator=(Ts{}), true)) || ...);
		return *this;
	}
};

} // enum_utils

} // aa

#endif // __AA_EU_ENUM_VARIANT_HPP