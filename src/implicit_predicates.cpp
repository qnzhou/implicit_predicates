#include <implicit_predicates/implicit_predicates.h>

#include <cmath>
#include <type_traits>

#include "internal/indirect_predicates.h"
#include "internal/stage_stats.h"

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

template <typename T>
T det3(T a, T b, T c, T d, T e, T f, T g, T h, T i) {
    // This version uses 9 multiplications.
    return a * (e * i - f * h) - b * (d * i - g * f) + c * (d * h - e * g);
}

template <typename T>
T det4(T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k, T l, T m, T n,
       T o, T p) {
    // clang-format off

    // This version uses 30 multiplications.  I don't think we get get away with
    // fewer multiplications.
    return (a*f - b*e) * (k*p - l*o) +
           (c*e - a*g) * (j*p - l*n) +
           (a*h - d*e) * (j*o - k*n) +
           (b*g - c*f) * (i*p - l*m) +
           (d*f - b*h) * (i*o - k*m) +
           (c*h - d*g) * (i*n - j*m);
    // clang-format on
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

Orientation orient1d_nonrobust(const double f0[2], const double f1[2]) {
    if (f0[0] == f0[1]) {
        // Function 0 is constant.
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

Orientation orient2d_nonrobust(const double f0[3], const double f1[3],
                               const double f2[3]) {
    auto det2 = [](double a, double b, double c, double d) {
        return a * d - b * c;
    };

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

Orientation orient3d_nonrobust(const double f0[4], const double f1[4],
                               const double f2[4], const double f3[4]) {
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

Orientation orient4d(const double f0[5], const double f1[5], const double f2[5],
                     const double f3[5], const double f4[5]) {
    // clang-format off
    const auto numerator = internal::det5(
            f0[0], f0[1], f0[2], f0[3], f0[4],
            f1[0], f1[1], f1[2], f1[3], f1[4],
            f2[0], f2[1], f2[2], f2[3], f2[4],
            f3[0], f3[1], f3[2], f3[3], f3[4],
            f4[0], f4[1], f4[2], f4[3], f4[4]);
    const auto denominator = internal::det5(
            f0[0], f0[1], f0[2], f0[3], f0[4],
            f1[0], f1[1], f1[2], f1[3], f1[4],
            f2[0], f2[1], f2[2], f2[3], f2[4],
            f3[0], f3[1], f3[2], f3[3], f3[4],
                1,     1,     1,     1,     1);
    // clang-format on
    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(numerator);
    } else {
        return sign_of(-numerator);
    }
}

Orientation orient4d(const Int f0[5], const Int f1[5], const Int f2[5],
                     const Int f3[5], const Int f4[5]) {
    // clang-format off
    const auto d0 = det4(
            f0[1], f0[2], f0[3], f0[4],
            f1[1], f1[2], f1[3], f1[4],
            f2[1], f2[2], f2[3], f2[4],
            f3[1], f3[2], f3[3], f3[4]);
    const auto d1 = -det4(
            f0[0], f0[2], f0[3], f0[4],
            f1[0], f1[2], f1[3], f1[4],
            f2[0], f2[2], f2[3], f2[4],
            f3[0], f3[2], f3[3], f3[4]);
    const auto d2 = det4(
            f0[0], f0[1], f0[3], f0[4],
            f1[0], f1[1], f1[3], f1[4],
            f2[0], f2[1], f2[3], f2[4],
            f3[0], f3[1], f3[3], f3[4]);
    const auto d3 = -det4(
            f0[0], f0[1], f0[2], f0[4],
            f1[0], f1[1], f1[2], f1[4],
            f2[0], f2[1], f2[2], f2[4],
            f3[0], f3[1], f3[2], f3[4]);
    const auto d4 = det4(
            f0[0], f0[1], f0[2], f0[3],
            f1[0], f1[1], f1[2], f1[3],
            f2[0], f2[1], f2[2], f2[3],
            f3[0], f3[1], f3[2], f3[3]);
    // clang-format on

    const auto denominator = d0 + d1 + d2 + d3 + d4;

    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(d0 * f4[0] + d1 * f4[1] + d2 * f4[2] + d3 * f4[3] +
                       d4 * f4[4]);
    } else {
        return sign_of(-d0 * f4[0] - d1 * f4[1] - d2 * f4[2] - d3 * f4[3] -
                       d4 * f4[4]);
    }
}

Orientation orient4d_nonrobust(const double f0[5], const double f1[5],
                               const double f2[5], const double f3[5],
                               const double f4[5]) {
    // clang-format off
    const auto d0 = det4(
            f0[1], f0[2], f0[3], f0[4],
            f1[1], f1[2], f1[3], f1[4],
            f2[1], f2[2], f2[3], f2[4],
            f3[1], f3[2], f3[3], f3[4]);
    const auto d1 = -det4(
            f0[0], f0[2], f0[3], f0[4],
            f1[0], f1[2], f1[3], f1[4],
            f2[0], f2[2], f2[3], f2[4],
            f3[0], f3[2], f3[3], f3[4]);
    const auto d2 = det4(
            f0[0], f0[1], f0[3], f0[4],
            f1[0], f1[1], f1[3], f1[4],
            f2[0], f2[1], f2[3], f2[4],
            f3[0], f3[1], f3[3], f3[4]);
    const auto d3 = -det4(
            f0[0], f0[1], f0[2], f0[4],
            f1[0], f1[1], f1[2], f1[4],
            f2[0], f2[1], f2[2], f2[4],
            f3[0], f3[1], f3[2], f3[4]);
    const auto d4 = det4(
            f0[0], f0[1], f0[2], f0[3],
            f1[0], f1[1], f1[2], f1[3],
            f2[0], f2[1], f2[2], f2[3],
            f3[0], f3[1], f3[2], f3[3]);
    // clang-format on

    const auto denominator = d0 + d1 + d2 + d3 + d4;

    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(d0 * f4[0] + d1 * f4[1] + d2 * f4[2] + d3 * f4[3] +
                       d4 * f4[4]);
    } else {
        return sign_of(-d0 * f4[0] - d1 * f4[1] - d2 * f4[2] - d3 * f4[3] -
                       d4 * f4[4]);
    }
}

Orientation mi_orient1d(const double f0[2], const double f1[2],
                        const double f2[2]) {
    // clang-format off
    const auto numerator = internal::diff_det2(
            f0[0], f0[1],
            f1[0], f1[1],
            f2[0], f2[1]);
    const auto denominator = internal::diff_det2_one(
            f0[0], f0[1],
            f1[0], f1[1]);
    // clang-format on
    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(-numerator);
    } else {
        return sign_of(numerator);
    }
}

Orientation mi_orient1d(const Int f0[2], const Int f1[2], const Int f2[2]) {
    const Int g1[]{f1[0] - f0[0], f1[1] - f0[1]};
    const Int g2[]{f2[0] - f0[0], f2[1] - f0[1]};

    if (g1[0] == g1[1]) {
        return INVALID;
    } else if (g1[0] > g1[1]) {
        return sign_of(g2[0] * g1[1] - g2[1] * g1[0]);
    } else {
        return sign_of(g1[0] * g2[1] - g1[1] * g2[0]);
    }
}

Orientation mi_orient1d_nonrobust(const double f0[2], const double f1[2],
                                  const double f2[2]) {
    const double g1[]{f1[0] - f0[0], f1[1] - f0[1]};
    const double g2[]{f2[0] - f0[0], f2[1] - f0[1]};

    if (g1[0] == g1[1]) {
        return INVALID;
    } else if (g1[0] > g1[1]) {
        return sign_of(g2[0] * g1[1] - g2[1] * g1[0]);
    } else {
        return sign_of(g1[0] * g2[1] - g1[1] * g2[0]);
    }
}

Orientation mi_orient2d(const double f0[3], const double f1[3],
                        const double f2[3], const double f3[3]) {
    // clang-format off
    const auto numerator = internal::diff_det3(
            f0[0], f0[1], f0[2],
            f1[0], f1[1], f1[2],
            f2[0], f2[1], f2[2],
            f3[0], f3[1], f3[2]);
    const auto denominator = internal::diff_det3_one(
            f0[0], f0[1], f0[2],
            f1[0], f1[1], f1[2],
            f2[0], f2[1], f2[2]);
    // clang-format on
    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(-numerator);
    } else {
        return sign_of(numerator);
    }
}

Orientation mi_orient2d(const Int f0[3], const Int f1[3], const Int f2[3],
                        const Int f3[3]) {
    const Int g1[3]{f1[0] - f0[0], f1[1] - f0[1], f1[2] - f0[2]};
    const Int g2[3]{f2[0] - f0[0], f2[1] - f0[1], f2[2] - f0[2]};
    const Int g3[3]{f3[0] - f0[0], f3[1] - f0[1], f3[2] - f0[2]};

    const Int D01 = g1[0] * g2[1] - g1[1] * g2[0];
    const Int D12 = g1[1] * g2[2] - g1[2] * g2[1];
    const Int D20 = g1[2] * g2[0] - g1[0] * g2[2];

    const Int denominator = D01 + D12 + D20;

    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(-g3[0] * D12 - g3[1] * D20 - g3[2] * D01);
    } else {
        return sign_of(g3[0] * D12 + g3[1] * D20 + g3[2] * D01);
    }
}

Orientation mi_orient2d_nonrobust(const double f0[3], const double f1[3],
                                  const double f2[3], const double f3[3]) {
    const double g1[3]{f1[0] - f0[0], f1[1] - f0[1], f1[2] - f0[2]};
    const double g2[3]{f2[0] - f0[0], f2[1] - f0[1], f2[2] - f0[2]};
    const double g3[3]{f3[0] - f0[0], f3[1] - f0[1], f3[2] - f0[2]};

    const double D01 = g1[0] * g2[1] - g1[1] * g2[0];
    const double D12 = g1[1] * g2[2] - g1[2] * g2[1];
    const double D20 = g1[2] * g2[0] - g1[0] * g2[2];

    const double denominator = D01 + D12 + D20;

    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(-g3[0] * D12 - g3[1] * D20 - g3[2] * D01);
    } else {
        return sign_of(g3[0] * D12 + g3[1] * D20 + g3[2] * D01);
    }
}

Orientation mi_orient3d(const double f0[4], const double f1[4],
                        const double f2[4], const double f3[4],
                        const double f4[4]) {
    // clang-format off
    const auto numerator = internal::diff_det4(
            f0[0], f0[1], f0[2], f0[3],
            f1[0], f1[1], f1[2], f1[3],
            f2[0], f2[1], f2[2], f2[3],
            f3[0], f3[1], f3[2], f3[3],
            f4[0], f4[1], f4[2], f4[3]);
    const auto denominator = internal::diff_det4_one(
            f0[0], f0[1], f0[2], f0[3],
            f1[0], f1[1], f1[2], f1[3],
            f2[0], f2[1], f2[2], f2[3],
            f3[0], f3[1], f3[2], f3[3]);
    // clang-format on
    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(-numerator);
    } else {
        return sign_of(numerator);
    }
}

Orientation mi_orient3d(const Int f0[4], const Int f1[4], const Int f2[4],
                        const Int f3[4], const Int f4[4]) {
    const Int g1[]{f1[0] - f0[0], f1[1] - f0[1], f1[2] - f0[2], f1[3] - f0[3]};
    const Int g2[]{f2[0] - f0[0], f2[1] - f0[1], f2[2] - f0[2], f2[3] - f0[3]};
    const Int g3[]{f3[0] - f0[0], f3[1] - f0[1], f3[2] - f0[2], f3[3] - f0[3]};
    const Int g4[]{f4[0] - f0[0], f4[1] - f0[1], f4[2] - f0[2], f4[3] - f0[3]};

    // clang-format off
    const Int D0 = det3(g1[1], g1[2], g1[3],
                        g2[1], g2[2], g2[3],
                        g3[1], g3[2], g3[3]);
    const Int D1 = det3(g1[0], g1[2], g1[3],
                        g2[0], g2[2], g2[3],
                        g3[0], g3[2], g3[3]);
    const Int D2 = det3(g1[0], g1[1], g1[3],
                        g2[0], g2[1], g2[3],
                        g3[0], g3[1], g3[3]);
    const Int D3 = det3(g1[0], g1[1], g1[2],
                        g2[0], g2[1], g2[2],
                        g3[0], g3[1], g3[2]);
    // clang-format on

    const Int denominator = -D0 + D1 - D2 + D3;

    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(D0 * g4[0] - D1 * g4[1] + D2 * g4[2] - D3 * g4[3]);
    } else {
        return sign_of(-D0 * g4[0] + D1 * g4[1] - D2 * g4[2] + D3 * g4[3]);
    }
}

Orientation mi_orient3d_nonrobust(const double f0[4], const double f1[4],
                                  const double f2[4], const double f3[4],
                                  const double f4[4]) {
    const double g1[]{f1[0] - f0[0], f1[1] - f0[1], f1[2] - f0[2],
                      f1[3] - f0[3]};
    const double g2[]{f2[0] - f0[0], f2[1] - f0[1], f2[2] - f0[2],
                      f2[3] - f0[3]};
    const double g3[]{f3[0] - f0[0], f3[1] - f0[1], f3[2] - f0[2],
                      f3[3] - f0[3]};
    const double g4[]{f4[0] - f0[0], f4[1] - f0[1], f4[2] - f0[2],
                      f4[3] - f0[3]};

    // clang-format off
    const auto D0 = det3(g1[1], g1[2], g1[3],
                         g2[1], g2[2], g2[3],
                         g3[1], g3[2], g3[3]);
    const auto D1 = det3(g1[0], g1[2], g1[3],
                         g2[0], g2[2], g2[3],
                         g3[0], g3[2], g3[3]);
    const auto D2 = det3(g1[0], g1[1], g1[3],
                         g2[0], g2[1], g2[3],
                         g3[0], g3[1], g3[3]);
    const auto D3 = det3(g1[0], g1[1], g1[2],
                         g2[0], g2[1], g2[2],
                         g3[0], g3[1], g3[2]);
    // clang-format on

    const auto denominator = -D0 + D1 - D2 + D3;

    if (denominator == 0) {
        return INVALID;
    } else if (denominator > 0) {
        return sign_of(D0 * g4[0] - D1 * g4[1] + D2 * g4[2] - D3 * g4[3]);
    } else {
        return sign_of(-D0 * g4[0] + D1 * g4[1] - D2 * g4[2] + D3 * g4[3]);
    }
}

std::array<size_t, 3> get_stage_stats() {
    return {internal::semi_static_filter_stage,
            internal::interval_arithmetic_stage,
            internal::exact_computation_stage};
}

}  // namespace implicit_predicates
