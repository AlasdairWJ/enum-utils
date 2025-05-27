#ifndef __AA_EU_ENUM_DICTIONARY_HPP
#define __AA_EU_ENUM_DICTIONARY_HPP

#include "array.hpp"
#include <string_view>

#define enum_dictionary(E) template <> constexpr aa::enum_utils::enum_array<E, std::string_view> aa::enum_utils::impl::the_enum_dictionary<E>
#define enum_entry(S) std::string_view{ S }

namespace aa
{

namespace enum_utils
{

namespace impl
{

template <typename E>
constexpr enum_array<E, std::string_view> the_enum_dictionary;

}

template <countable_enum E>
constexpr std::string_view to_string(const E value) noexcept
{
	if (static_cast<std::size_t>(value) >= enum_count_v<E>)
		return std::string_view{};

	return impl::the_enum_dictionary<E>[value];
}

template <countable_enum E>
constexpr E parse(const std::string_view str) noexcept
{
	for (const E e : enum_range<E>())
	{
		if (impl::the_enum_dictionary<E>[e] == str)
			return e;
	}

	return invalid<E>;
}

} // enum_utils

} // aa

#endif // __AA_EU_ENUM_DICTIONARY_HPP
