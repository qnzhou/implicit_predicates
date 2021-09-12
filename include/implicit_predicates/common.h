#pragma once

#include <absl/numeric/int128.h>

namespace implicit_predicates {

using Int = absl::int128;

enum Orientation : int8_t {
    NEGATIVE = -1,
    ZERO = 0,
    POSITIVE = 1,
    INVALID = 2
};

}  // namespace implicit_predicates
