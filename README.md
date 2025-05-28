# enum-utils (C++20)
 These are a bunch of enum-related structures & utilities that I actually use regularly, these are the kind of things that are totally obvious in hindsight.

## `countable_enum`

 Countable enums are scoped enums that are contiguous from 0 and include a final value of `_Count`. This allows the other utilities to automatically determine their size/range.

```c++
#include <aa/enum_utils/countable.hpp>

enum class Colour
{
    Red,
    Green,
    Blue,

    _Count
};

static_assert(aa::enum_utils::is_countable_enum_v<Colour>);
```

`aa::enum_utils::enum_count<E>` will alias the `std::size_t` size of a countable enum.

`aa::enum_utils::invalid<E>` will alias `_Count` and is intended to be used to give flexibility to interfaces,

`aa::enum_utils::valid(e)` will check if a countable enum is valid.

## `enum_array`

These are arrays that are index by a countable enum.

```c++
#include <aa/enum_utils/array.hpp>

// ...

aa::enum_utils::enum_array<Colour, int> values{};

values[Colour::Red] = 10;
values[Colour::Green] = 20;
values[Colour::Blue] = 5;
```

## enum dictionary

Provides simple enum-string conversions, but is restricted to countable enums.

```c++
#include <aa/enum_utils/dictionary.hpp>

enum class Colour
{
    Red,
    Green,
    Blue,

    _Count
};

enum_dictionary(Colour) {
    enum_entry("Red"),
    enum_entry("Green"),
    enum_entry("Blue")
};

// ...

std::cout << aa::enum_utils::to_string(Colour::Blue);
const auto c = aa::enum_utils::parse<Color>(...);
```

`aa::enum_utils::parse<E>` is (currently) case sensitive will return `aa::enum_utils::invalid<E>` when not match is found.

## `enum_range`

Exactly what you'd think

```c++
#include <aa/enum_utils/enum_range.hpp>

for (const auto c : aa::enum_utils::enum_range<Colour>())
{
    // ...
}
```

An `enum_range` for an `enum_array` can be accessed via `.indices()`

```c++
aa::enum_utils::enum_array<Colour, int> values{};

for (const Colour c:  values.indices())
{
    // ...
}
```

## flags

Allows bitwise operators on specified enums.

```c++
#include <aa/enum_utils/flags.hpp>

enum class Options
{
    Yes = 0x1,
    No = 0x2,
    Cancel = 0x4
};

enum_flag(Options);

constexpr auto options = Options::Yes | Options::Cancel;
```

## utility

Contains implementations of `std::is_scoped_enum` and `std::to_underlying` for those not on c++23.

## variant
