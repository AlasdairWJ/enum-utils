#ifndef __EU_DICTIONARY_HPP
#define __EU_DICTIONARY_HPP

#include <string_view>

#define EU_DEFINE_NAME(E, V, S) template <> struct eu::impl::dictionary_entry<E, E::V> { static constexpr std::string_view value{ S }; }
#define EU_DEFINE_DEFAULT_NAME(E, V) EU_DEFINE_NAME(E, V, #V)

namespace eu
{

namespace impl
{

template <typename E, E V>
struct dictionary_entry
{
	static constexpr std::string_view value{};
};

template <typename E, std::size_t... Ixs>
std::string_view to_string(const E value, std::integer_sequence<std::size_t, Ixs...>)
{
	static constexpr std::string_view Values[]{ eu::impl::dictionary_entry<E, static_cast<E>(Ixs)>::value...  };
	return Values[static_cast<std::size_t>(value)];
}

} // impl

template <typename E>
std::string_view to_string(const E value)
{
	return impl::to_string(value, std::make_integer_sequence<std::size_t, eu::enum_count_v<E>>{});
}


} // eu

#endif // __EU_DICTIONARY_HPP
