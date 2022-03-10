#pragma once

#include <absl/numeric/int128.h>

#ifdef IMPLICIT_PREDICATES_WITH_CGAL
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#endif

namespace implicit_predicates {

using Int = absl::int128;

enum Orientation : int8_t {
    NEGATIVE = -1,
    ZERO = 0,
    POSITIVE = 1,
    INVALID = 2
};

#ifdef IMPLICIT_PREDICATES_WITH_CGAL
using Kernel = CGAL::Epeck;
using FT = Kernel::FT;
#endif

}  // namespace implicit_predicates
