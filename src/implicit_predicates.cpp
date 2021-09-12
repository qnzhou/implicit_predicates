#include <implicit_predicates/implicit_predicates.h>
#include <implicit_predicates/internal/indirect_predicates.h>

#include <cmath>
#include <type_traits>

namespace implicit_predicates {

namespace {

template <typename T>
Orientation sign_of(T val) {
    if constexpr (std::is_same<T, double>::value) {
        // Check for nan and inf.
        assert(std::isfinite(val));
    }

    if (val > 0)
        return POSITIVE;
    else if (val < 0)
        return NEGATIVE;
    else
        return ZERO;
}

}  // namespace

Orientation orient1d(const double f0[2], const double f1[2]) {
    if (f0[0] == f0[1]) {
        // Function 0 is constant.
        return INVALID;
    } else if (f0[1] < f0[0]) {
        return sign_of(internal::det2(f0[0], f0[1], f1[0], f1[1]));
    } else {
        return sign_of(-internal::det2(f0[0], f0[1], f1[0], f1[1]));
    }
}

Orientation orient1d(const Int f0[2], const Int f1[2]) {
    if (f0[0] == f0[1]) {
        return INVALID;
    } else if (f0[1] < f0[0]) {
        return sign_of(f0[0] * f1[1] - f0[1] * f1[0]);
    } else {
        return sign_of(-f0[0] * f1[1] + f0[1] * f1[0]);
    }
}

Orientation orient2d(const double f0[3], const double f1[3],
                     const double f2[3]) {
    // clang-format off
    const auto denominator = internal::det3(
            f0[0], f0[1], f0[2],
            f1[0], f1[1], f1[2],
                1,     1,     1);
    const auto numerator = internal::det3(
            f0[0], f0[1], f0[2],
            f1[0], f1[1], f1[2],
            f2[0], f2[1], f2[2]);
    // clang-format on

    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(numerator);
    } else {
        return sign_of(-numerator);
    }
}

Orientation orient2d(const Int f0[3], const Int f1[3], const Int f2[3]) {
    auto det2 = [](Int a, Int b, Int c, Int d) { return a * d - b * c; };

    const auto d0 = det2(f0[1], f0[2], f1[1], f1[2]);
    const auto d1 = -det2(f0[0], f0[2], f1[0], f1[2]);
    const auto d2 = det2(f0[0], f0[1], f1[0], f1[1]);

    const auto denominator = d0 + d1 + d2;

    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(f2[0] * d0 + f2[1] * d1 + f2[2] * d2);
    } else {
        return sign_of(-f2[0] * d0 - f2[1] * d1 - f2[2] * d2);
    }
}

Orientation orient3d(const double f0[4], const double f1[4], const double f2[4],
                     const double f3[4]) {
    // clang-format off
    const auto numerator = internal::det4(
            f0[0], f0[1], f0[2], f0[3],
            f1[0], f1[1], f1[2], f1[3],
            f2[0], f2[1], f2[2], f2[3],
            f3[0], f3[1], f3[2], f3[3]);
    const auto denominator = internal::det4(
            f0[0], f0[1], f0[2], f0[3],
            f1[0], f1[1], f1[2], f1[3],
            f2[0], f2[1], f2[2], f2[3],
                1,     1,     1,     1);
    // clang-format on
    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(numerator);
    } else {
        return sign_of(-numerator);
    }
}

Orientation orient3d(const Int f0[4], const Int f1[4], const Int f2[4],
                     const Int f3[4]) {
    auto det3 = [](Int a, Int b, Int c, Int d, Int e, Int f, Int g, Int h,
                   Int i) {
        return a * (e * i - f * h) - b * (d * i - g * f) + c * (d * h - e * g);
    };

    // clang-format off
    const auto d0 = -det3(
            f0[1], f0[2], f0[3],
            f1[1], f1[2], f1[3],
            f2[1], f2[2], f2[3]);
    const auto d1 = det3(
            f0[0], f0[2], f0[3],
            f1[0], f1[2], f1[3],
            f2[0], f2[2], f2[3]);
    const auto d2 = -det3(
            f0[0], f0[1], f0[3],
            f1[0], f1[1], f1[3],
            f2[0], f2[1], f2[3]);
    const auto d3 = det3(
            f0[0], f0[1], f0[2],
            f1[0], f1[1], f1[2],
            f2[0], f2[1], f2[2]);
    // clang-format on

    const auto denominator = d0 + d1 + d2 + d3;

    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(d0 * f3[0] + d1 * f3[1] + d2 * f3[2] + d3 * f3[3]);
    } else {
        return sign_of(-d0 * f3[0] - d1 * f3[1] - d2 * f3[2] - d3 * f3[3]);
    }
}

}  // namespace implicit_predicates
