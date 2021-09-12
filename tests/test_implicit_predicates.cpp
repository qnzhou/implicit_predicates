#include <implicit_predicates/implicit_predicates.h>

#include <catch2/catch.hpp>
#include <cmath>
#include <limits>

TEST_CASE("orient1d", "[1D][predicate]") {
    using namespace implicit_predicates;

    auto check = [](auto s, auto b) {
        using T = decltype(s);

        T p0[]{-s, s};
        T p1[]{-b, s};
        T p2[]{b, -s};
        T p3[]{s, -s};

        REQUIRE(orient1d(p0, p0) == ZERO);
        REQUIRE(orient1d(p0, p3) == ZERO);
        REQUIRE(orient1d(p0, p1) == NEGATIVE);
        REQUIRE(orient1d(p1, p0) == POSITIVE);
        REQUIRE(orient1d(p0, p2) == POSITIVE);
        REQUIRE(orient1d(p3, p1) == NEGATIVE);
        REQUIRE(orient1d(p3, p2) == POSITIVE);
    };

    SECTION("float") { check(1., 2.); }

    SECTION("int") {
        Int v0 = 1;
        Int v1 = 2;
        check(v0, v1);
    }

    SECTION("float large") {
        // Cannot use numeric_limits<double>::max() since it will overflow.
        constexpr double v0 = 1e100;
        const double v1 = std::nextafter(v0, v0 * 2);
        check(v0, v1);
    }

    SECTION("float epsilon") {
        constexpr double max_f = std::numeric_limits<double>::epsilon();
        constexpr double min_f = std::numeric_limits<double>::min();
        check(min_f, max_f);
    }

    SECTION("float epsilon 2") {
        constexpr double min_f = std::numeric_limits<double>::epsilon();
        const double max_f = std::nextafter(min_f, 1.0);
        check(min_f, max_f);
    }

    SECTION("large int") {
        constexpr Int max_i = std::numeric_limits<int>::max();
        constexpr Int min_i = std::numeric_limits<int>::max() - 1;
        check(min_i, max_i);
    }
}

TEST_CASE("orient2d", "[2d][predicate]") {
    using namespace implicit_predicates;

    auto check = [](auto s, auto m, auto b) {
        using T = decltype(s);

        T p0[]{-s, s, s};
        T p1[]{s, -s, s};
        T p2[]{s, s, -s};
        T p3[]{b, -s, b};
        T p4[]{0, -b, b};
        T p5[]{m, 0, -m};
        T p6[]{s, -s, 0};

        REQUIRE(orient2d(p0, p1, p2) == POSITIVE);
        REQUIRE(orient2d(p1, p0, p2) == POSITIVE);
        REQUIRE(orient2d(p2, p1, p0) == POSITIVE);
        REQUIRE(orient2d(p0, p2, p1) == POSITIVE);
        REQUIRE(orient2d(p0, p1, p3) == POSITIVE);
        REQUIRE(orient2d(p1, p2, p3) == POSITIVE);
        REQUIRE(orient2d(p2, p0, p3) == POSITIVE);
        REQUIRE(orient2d(p4, p0, p3) == POSITIVE);
        REQUIRE(orient2d(p5, p1, p4) == NEGATIVE);
        REQUIRE(orient2d(p4, p5, p6) == ZERO);
        REQUIRE(orient2d(p4, p5, p0) == POSITIVE);
        REQUIRE(orient2d(p5, p0, p2) == ZERO);
    };

    SECTION("float") { check(1., 2., 3.); }

    SECTION("int") {
        Int v0 = 1;
        Int v1 = 3;
        Int v2 = 10;
        check(v0, v1, v2);
    }

    SECTION("float epsilon") {
        constexpr double v0 = std::numeric_limits<double>::epsilon();
        const double v1 = std::nextafter(v0, 1);
        const double v2 = std::nextafter(v1, 1);
        check(v0, v1, v2);
    }

    SECTION("large int") {
        constexpr Int v0 = std::numeric_limits<int>::max() - 2;
        constexpr Int v1 = std::numeric_limits<int>::max() - 1;
        constexpr Int v2 = std::numeric_limits<int>::max();
        check(v0, v1, v2);
    }
}

TEST_CASE("orient3d", "[3d][predicate]") {
    using namespace implicit_predicates;

    auto check = [](auto a, auto b, auto c, auto d) {
        using T = decltype(a);
        T p0[]{-a, 0, 0, 0};
        T p1[]{0, -b, 0, 0};
        T p2[]{0, 0, -c, 0};
        T p3[]{0, 0, 0, -d};
        T p4[]{a, -a, 0, 0};
        T p5[]{b, 0, -b, 0};
        T p6[]{c, 0, 0, -c};
        T p7[]{0, d, 0, -d};
        T p8[]{0, 0, a, -a};
        T p9[]{-a, b, c, d};
        T p10[]{a, -b, c, d};
        T p11[]{0, a, -a, -a};
        T p12[]{0, -b, b, -b};
        T p13[]{0, -c, -c, c};

        REQUIRE(orient3d(p0, p1, p2, p3) == NEGATIVE);
        REQUIRE(orient3d(p1, p0, p2, p3) == NEGATIVE);
        REQUIRE(orient3d(p4, p5, p6, p7) == ZERO);
        REQUIRE(orient3d(p8, p5, p6, p4) == INVALID);
        REQUIRE(orient3d(p0, p1, p2, p9) == POSITIVE);
        REQUIRE(orient3d(p0, p1, p2, p10) == POSITIVE);
        REQUIRE(orient3d(p3, p1, p2, p9) == NEGATIVE);
        REQUIRE(orient3d(p3, p1, p2, p10) == POSITIVE);
        REQUIRE(orient3d(p11, p12, p13, p0) == NEGATIVE);
        REQUIRE(orient3d(p11, p12, p13, p1) == ZERO);
    };

    SECTION("float") { check(1., 2., 3., 4.); }
    SECTION("int") {
        Int v0 = 1;
        Int v1 = 3;
        Int v2 = 10;
        Int v3 = 11;
        check(v0, v1, v2, v3);
    }
    SECTION("float epsilon") {
        constexpr double v0 = std::numeric_limits<double>::epsilon();
        const double v1 = std::nextafter(v0, 1);
        const double v2 = std::nextafter(v1, 1);
        const double v3 = std::nextafter(v2, 1);
        check(v0, v1, v2, v3);
    }
    SECTION("large int") {
        constexpr Int v0 = std::numeric_limits<int>::max() - 3;
        constexpr Int v1 = std::numeric_limits<int>::max() - 2;
        constexpr Int v2 = std::numeric_limits<int>::max() - 1;
        constexpr Int v3 = std::numeric_limits<int>::max();
        check(v0, v1, v2, v3);
    }

    SECTION("debug example") {
        double p0[]{-2724, 3470, -1513, 345};
        double p1[]{-857, 2022, -3004, -2640};
        double p2[]{1919, 2988, 3584, 3859};
        double p3[]{-580, -200, -2920, -1099};

        Int q0[]{-2724, 3470, -1513, 345};
        Int q1[]{-857, 2022, -3004, -2640};
        Int q2[]{1919, 2988, 3584, 3859};
        Int q3[]{-580, -200, -2920, -1099};

        REQUIRE(orient3d(p0, p1, p2, p3) == orient3d(q0, q1, q2, q3));
    }
}

