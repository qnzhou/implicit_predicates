#include <implicit_predicates/implicit_predicates.h>

#include <catch2/catch.hpp>
#include <limits>
#include <random>
#include <vector>

TEST_CASE("benchmark", "[predicate][.benchmark]") {
    using namespace implicit_predicates;

    constexpr size_t N = 1e3;
    std::vector<Int> int_data;
    std::vector<double> double_data;
    int_data.reserve(N);
    double_data.reserve(N);

    // std::random_device rd;
    std::mt19937 gen(7);
    std::uniform_int_distribution<> distrib(-(1 << 12), 1 << 12);

    for (size_t i = 0; i < N; i++) {
        int_data.push_back(distrib(gen));
        double_data.push_back(static_cast<double>(int_data.back()));
        REQUIRE(static_cast<int>(double_data.back()) == int_data.back());
    }

    for (size_t i = 0; i < N - 16; i++) {
        auto int_ptr = int_data.data() + i;
        auto double_ptr = double_data.data() + i;
        REQUIRE(orient1d(double_ptr, double_ptr + 2) ==
                orient1d(int_ptr, int_ptr + 2));
        REQUIRE(orient2d(double_ptr, double_ptr + 3, double_ptr + 6) ==
                orient2d(int_ptr, int_ptr + 3, int_ptr + 6));
        REQUIRE(orient3d(double_ptr, double_ptr + 4, double_ptr + 8,
                         double_ptr + 12) ==
                orient3d(int_ptr, int_ptr + 4, int_ptr + 8, int_ptr + 12));
    }

    BENCHMARK("orient1d with int", i) {
        size_t offset = i % (N - 4);
        return orient1d(int_data.data() + offset, int_data.data() + offset + 2);
    };
    BENCHMARK("orient1d with double", i) {
        size_t offset = i % (N - 4);
        return orient1d(double_data.data() + offset,
                        double_data.data() + offset + 2);
    };
    BENCHMARK("orient1d with double (non-robust)", i) {
        size_t offset = i % (N - 4);
        return orient1d_nonrobust(double_data.data() + offset,
                                  double_data.data() + offset + 2);
    };
    BENCHMARK("orient2d with int", i) {
        size_t offset = i % (N - 9);
        return orient2d(int_data.data() + offset, int_data.data() + offset + 3,
                        int_data.data() + offset + 6);
    };
    BENCHMARK("orient2d with double", i) {
        size_t offset = i % (N - 9);
        return orient2d(double_data.data() + offset,
                        double_data.data() + offset + 3,
                        double_data.data() + offset + 6);
    };
    BENCHMARK("orient2d with double (non-robust)", i) {
        size_t offset = i % (N - 9);
        return orient2d_nonrobust(double_data.data() + offset,
                                  double_data.data() + offset + 3,
                                  double_data.data() + offset + 6);
    };
    BENCHMARK("orient3d with int", i) {
        size_t offset = i % (N - 16);
        return orient3d(int_data.data() + offset, int_data.data() + offset + 4,
                        int_data.data() + offset + 8,
                        int_data.data() + offset + 12);
    };
    BENCHMARK("orient3d with double", i) {
        size_t offset = i % (N - 16);
        return orient3d(
            double_data.data() + offset, double_data.data() + offset + 4,
            double_data.data() + offset + 8, double_data.data() + offset + 12);
    };
    BENCHMARK("orient3d with double (non-robust)", i) {
        size_t offset = i % (N - 16);
        return orient3d_nonrobust(
            double_data.data() + offset, double_data.data() + offset + 4,
            double_data.data() + offset + 8, double_data.data() + offset + 12);
    };
    BENCHMARK("orient4d with int", i) {
        size_t offset = i % (N - 25);
        return orient4d(int_data.data() + offset, int_data.data() + offset + 5,
                        int_data.data() + offset + 10,
                        int_data.data() + offset + 15,
                        int_data.data() + offset + 20);
    };
    BENCHMARK("orient4d with double", i) {
        size_t offset = i % (N - 25);
        return orient4d(
            double_data.data() + offset, double_data.data() + offset + 5,
            double_data.data() + offset + 10, double_data.data() + offset + 15,
            double_data.data() + offset + 20);
    };
    BENCHMARK("orient4d with double (non-robust)", i) {
        size_t offset = i % (N - 25);
        return orient4d_nonrobust(
            double_data.data() + offset, double_data.data() + offset + 5,
            double_data.data() + offset + 10, double_data.data() + offset + 15,
            double_data.data() + offset + 20);
    };
}
