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
