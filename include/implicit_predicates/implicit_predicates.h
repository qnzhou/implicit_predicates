#pragma once

#include <implicit_predicates/common.h>

namespace implicit_predicates {

/**
 * Compute the orientation of two zero crossings on a 2-simplex.
 *
 * @param[in]  f0  Function values at the endpoints of an edge for function 0.
 * @param[in]  f1  Function values at the endpoints of an edge for function 1.
 *
 * @returns
 *     * POSITIVE: if the zero crossing of function 0 is on the positive side of
 *                 funciton 1.
 *     * NEGATIVE: if the zero crossing of function 0 is on the negative side of
 *                 function 1.
 *     * ZERO:     if the zero corssing of function 0 is on the zero level set
 *                 of function 1.
 *     * INVALID:  if function 0 is a constant function, which makes the problem
 *                 ill-posed.
 */
Orientation orient1d(const double f0[2], const double f1[2]);
Orientation orient1d(const Int f0[2], const Int f1[2]);
Orientation orient1d_nonrobust(const double f0[2], const double f1[2]);

/**
 * Compute the orientation of the 2D intersection of function 0 and 1 with
 * respect to function 2.
 *
 * @param[in]  f0  Function values at the corners of a triangle for function 0.
 * @param[in]  f1  Function values at the corners of a triangle for function 1.
 * @param[in]  f2  Function values at the corners of a triangle for function 2.
 *
 * @returns
 *     * POSITIVE: if the intersection of zero crossings of function 0 and 1 is
 *                 on the positive side of funciton 2.
 *     * NEGATIVE: if the intersection of zero crossings of function 0 and 1 is
 *                 on the negative side of function 2.
 *     * ZERO:     if the intersection of zero corssings of function 0 and 1 is
 *                 on the zero level set of function 2.
 *     * INVALID:  if function 0 or 1 is a constant function, or they do not
 *                 intersect at a point, which makes the problem ill-posed.
 */
Orientation orient2d(const double f0[3], const double f1[3],
                     const double f2[3]);
Orientation orient2d(const Int f0[3], const Int f1[3], const Int f2[3]);
Orientation orient2d_nonrobust(const double f0[3], const double f1[3],
                               const double f2[3]);

/**
 * Compute the orientation of the 3D intersection of function 0, 1 and 2 with
 * respect to function 3.
 *
 * @param[in]  f0  Function values at the corners of a tetrahedron for function
 * 0.
 * @param[in]  f1  Function values at the corners of a tetrahedron for
 * function 1.
 * @param[in]  f2  Function values at the corners of a tetrahedron for
 * function 2.
 * @param[in]  f3  Function values at the corners of a tetrahedron for
 * function 3.
 *
 * @returns
 *     * POSITIVE: if the intersection of zero crossings of function 0,1,2 is
 *                 on the positive side of funciton 3.
 *     * NEGATIVE: if the intersection of zero crossings of function 0,1,2 is
 *                 on the negative side of function 3.
 *     * ZERO:     if the intersection of zero corssings of function 0,1,2 is
 *                 on the zero level set of function 3.
 *     * INVALID:  if function 0, 1 or 2 is a constant function, or they do not
 *                 intersect at a point, which makes the problem ill-posed.
 */
Orientation orient3d(const double f0[4], const double f1[4], const double f2[4],
                     const double f3[4]);
Orientation orient3d(const Int f0[4], const Int f1[4], const Int f2[4],
                     const Int f3[4]);
Orientation orient3d_nonrobust(const double f0[4], const double f1[4],
                               const double f2[4], const double f3[4]);

/**
 * Compute the orientation of the 4D intersection of function 0, 1, 2 and 3 with
 * respect to function 4.
 *
 * @param[in]  f0  Function values at the corners of a 4D simplex for
 * function 0.
 * @param[in]  f1  Function values at the corners of a 4D simplex for
 * function 1.
 * @param[in]  f2  Function values at the corners of a 4D simplex for
 * function 2.
 * @param[in]  f3  Function values at the corners of a 4D simplex for
 * function 3.
 * @param[in]  f4  Function values at the corners of a 4D simplex for
 * function 4.
 *
 * @returns
 *     * POSITIVE: if the intersection of zero crossings of function 0,1,2,3 is
 *                 on the positive side of funciton 4.
 *     * NEGATIVE: if the intersection of zero crossings of function 0,1,2,3 is
 *                 on the negative side of function 4.
 *     * ZERO:     if the intersection of zero corssings of function 0,1,2,3 is
 *                 on the zero level set of function 4.
 *     * INVALID:  if function 0, 1, 2 or 2 is a constant function, or they do
 *                 not intersect at a point, which makes the problem ill-posed.
 */
Orientation orient4d(const double f0[5], const double f1[5], const double f2[5],
                     const double f3[5], const double f4[5]);
Orientation orient4d(const Int f0[5], const Int f1[5], const Int f2[5],
                     const Int f3[5], const Int f4[5]);
Orientation orient4d_nonrobust(const double f0[5], const double f1[5],
                               const double f2[5], const double f3[5],
                               const double f4[5]);

/**
 * Compute the orientation of joint material interface of function 0, 1 and 2
 * with respect to function 3.  The joint material interface of function 0, 1
 * and 2 is a point, p, such that f0(p) = f1(p) = f2(p).
 *
 * @param[in]  f0  Function values at the corner of a 2D simplex for function 0.
 * @param[in]  f1  Function values at the corner of a 2D simplex for function 1.
 * @param[in]  f2  Function values at the corner of a 2D simplex for function 2.
 * @param[in]  f3  Function values at the corner of a 2D simplex for function 3.
 *
 * @returns
 *    * POSITIVE: if f3(p) > f0(p)
 *    * NEGATIVE: if f3(p) < f0(p)
 *    * ZERO:     if f3(p) = f0(p)
 *    * INVALID:  if the joint material interface of function 0, 1 and 2 does
 *                not exist.  I.e. at least 2 functions are parallel.
 */
Orientation mi_orient2d(const double f0[3], const double f1[3],
                        const double f2[3], const double f3[3]);
Orientation mi_orient2d(const Int f0[3], const Int f1[3], const Int f2[3],
                        const Int f3[3]);
Orientation mi_orient2d_nonrobust(const double f0[3], const double f1[3],
                                  const double f2[3], const double f3[3]);

/**
 * Compute the orientation of joint material interface of function 0, 1, 2 and
 * 3 with respect to function 4.  The joint material interface of function 0, 1
 * 2 and 3 is a point, p, such that f0(p) = f1(p) = f2(p) = f3(p).
 *
 * @param[in]  f0  Function values at the corner of a 3D simplex for function 0.
 * @param[in]  f1  Function values at the corner of a 3D simplex for function 1.
 * @param[in]  f2  Function values at the corner of a 3D simplex for function 2.
 * @param[in]  f3  Function values at the corner of a 3D simplex for function 3.
 * @param[in]  f4  Function values at the corner of a 3D simplex for function 4.
 *
 * @returns
 *    * POSITIVE: if f4(p) > f0(p)
 *    * NEGATIVE: if f4(p) < f0(p)
 *    * ZERO:     if f4(p) = f0(p)
 *    * INVALID:  if the joint material interface of function 0, 1, 2 and 3 does
 *                not exist.  I.e. at least 2 functions are parallel.
 */
Orientation mi_orient3d(const double f0[4], const double f1[4],
                        const double f2[4], const double f3[4],
                        const double f4[4]);
Orientation mi_orient3d(const Int f0[4], const Int f1[4], const Int f2[4],
                        const Int f3[4], const Int f4[4]);
Orientation mi_orient3d_nonrobust(const double f0[4], const double f1[4],
                                  const double f2[4], const double f3[4],
                                  const double f4[4]);

}  // namespace implicit_predicates
