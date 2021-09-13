# Implicit Exact Predicates

## Overview

Given one or more implicit functions defined over 1, 2 or 3 simplex, implicit
predicates provide the following exact checks:

* `orient1d(f0, f1)`: Defined over a 1-simplex, define whether the zero crossing
  of function `f0` lies on the on positive/zero/negative side of function `f1`.
* `orient2d(f0, f1, f2)`: Defined over a 2-simplex, compute whether the
  intersection of the zero crossings of function `f0` and `f1` lies on the
  positive/zero/negative side of function `f2`.
* `orient3d(f0, f1, f2, f3)`: Defined over a 3-simplex, compute whether the
  intersection of the zero crossings of function `f0`, `f1` and `f2` lies on the
  positive/zero/negative side of function `f3`.

## Build

```sh
mkdir build
cd build
cmake ..
make
```

## Usage

All predicates support either double or 128 bit integer inputs.  Here is an
example usage:

```c++
#include <implicit_predicates/implicit_predicates.h>

// Double version
double f0[]{1.0, 0.0, 0.0, 0.0};
double f1[]{0.0, 1.0, 0.0, 0.0};
double f2[]{0.0, 0.0, 1.0, 0.0};
double f3[]{0.0, 0.0, 0.0, 1.0};

auto r1 = implicit_predicates::orient3d(f0, f1, f2, f3);

// Int version
using Int = implicit_predicates::Int;
Int g0[]{1, 0, 0, 0};
Int g1[]{0, 1, 0, 0};
Int g2[]{0, 0, 1, 0};
Int g3[]{0, 0, 0, 1};

auto r2 = implicit_predicates::orient3d(g0, g1, g2, g3);
assert(r1 == r2);
```

## Benchmark

```
% ./implicit_predicates_tests benchmark
Filters: benchmark

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
implicit_predicates_tests is a Catch v2.13.6 host application.
Run with -? for options

-------------------------------------------------------------------------------
benchmark
-------------------------------------------------------------------------------
/Users/qzhou/Research/implicit_predicates/tests/benchmark.cpp:8
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
orient1d with int                              100          7027     2.8108 ms
                                        4.31935 ns    4.29984 ns     4.4005 ns
                                       0.174831 ns  0.0327342 ns   0.408809 ns

orient1d with double                           100          2161     3.2415 ms
                                        16.2146 ns    15.3247 ns    18.0175 ns
                                        6.18326 ns    3.38024 ns    9.90453 ns

orient2d with int                              100          2670      3.204 ms
                                        12.2684 ns    11.7265 ns     13.492 ns
                                        3.95364 ns     1.8807 ns    6.80433 ns

orient2d with double                           100           581     3.2536 ms
                                        51.4849 ns    50.1665 ns    54.4506 ns
                                        9.53472 ns    5.17177 ns    17.9264 ns

orient3d with int                              100          1238     3.2188 ms
                                         25.405 ns    24.8074 ns    26.8083 ns
                                        4.42921 ns     1.8628 ns    7.66629 ns

orient3d with double                           100           234      3.276 ms
                                        87.5675 ns    86.7056 ns    89.5709 ns
                                        6.34282 ns    3.13095 ns    11.7194 ns


===============================================================================
All tests passed (3952 assertions in 1 test case)
```
