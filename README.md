# enum-utils (C++17)
 These are a bunch of enum-related utilities that I actually use regularly, these are the kind of things that are totally obvious in hindsight.

## `countable_enum`

 Countable enums are scoped enums that are contiguous from 0 and include a final value of `_Count` (or `EU_COUNTABLE_IDENTIFIER`). This allows the other utilities to automatically determine their size/range.

```c++
#include <eu/countable.hpp>

enum class Colour
{
    Red,
    Green,
    Blue,

    _Count
};

static_assert(eu::is_countable_enum_v<Colour>);
```

If concepts are available, `eu::countable_enum` is defined.

`eu::enum_count<E>` / `eu::enum_count_v<E>` will provide the number of elements in the enum.

`eu::invalid<E>` / `eu::invalid_v<E>` will alias `_Count` and is intended to be used to give flexibility to interfaces.

`eu::valid(e)` will check if a countable enum is valid (i.e. `0 <= e < _Count`).

## `array`

These are arrays that are indexed by a countable enum, from which the size is automatically deduced. 

```c++
#include <eu/array.hpp>

// ...

eu::array<Colour, int> values{};

values[Colour::Red] = 1;
values[Colour::Green] = 23;
values[Colour::Blue] = 456;
```

## flags

Allows bitwise operators on enums that contains `_Flags` (or `EU_FLAGS_IDENTIFIER`)

```c++
#include <eu/flags.hpp>

enum class Options
{
    Yes = 0x1,
    No = 0x2,
    Cancel = 0x4,

    _Flags
};

static_assert(eu::is_flags_v<Options>); 

using namespace eu::flags::operators;

constexpr auto options = Options::Yes | Options::Cancel;
```

If concepts are available, `eu::flags_enum` is defined.

`_Flags` should be defined _after the highest bit_. 

`eu::mask<E>` / `eu::mask_v<E>` will provide the mask of all bits.

```
static_assert(eu::mask_v<Options> == Options{ 0x7 });
```

Also provides some explicit flag-related functions `eu::flags::any`, `eu::flags::has`, `eu::flags::set`, and `eu::flags::unset`.

## dictionary

Provides simple enum-string conversions, but is restricted to countable enums. I don't necessarily recommend this, its best use is probably to for debugging, but it's mostly fun template science project.

Use `EU_DEFINE_NAME` to define an enums name.
Use `EU_DEFINE_DEFAULT_NAME` will use the enum value as the name.

```c++
#include <eu/dictionary.hpp>

enum class Colour
{
    Red,
    Green,
    LightBlue,

    _Count
};

EU_DEFINE_DEFAULT_NAME(Colour, Red);
EU_DEFINE_DEFAULT_NAME(Colour, Green);
EU_DEFINE_NAME(Colour, LightBlue, "Light-blue");


// ...

std::cout << eu::to_string(Colour::LightBlue);
```

## `range`

```c++
#include <eu/range.hpp>

for (const auto c : eu::enum_range<Colour>())
{
    // ...
}
```

An `range` for an `array` can be accessed via `.indices()`

```c++
eu::enum_array<Colour, int> values{};

for (const Colour c : values.indices())
{
    // ...
}
```

## utility

Contains `eu::is_scoped_enum` and `eu::to_underlying` for those not on c++23.

## variant

Also exists
