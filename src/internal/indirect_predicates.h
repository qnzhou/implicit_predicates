/****************************************************************************
 * Indirect predicates for geometric constructions					         *
 *                                                                           *
 * Consiglio Nazionale delle Ricerche                                        *
 * Istituto di Matematica Applicata e Tecnologie Informatiche                *
 * Sezione di Genova                                                         *
 * IMATI-GE / CNR                                                            *
 *                                                                           *
 * Authors: Marco Attene                                                     *
 * Copyright(C) 2019: IMATI-GE / CNR                                         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This program is free software; you can redistribute it and/or modify      *
 * it under the terms of the GNU Lesser General Public License as published  *
 * by the Free Software Foundation; either version 3 of the License, or (at  *
 * your option) any later version.                                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser  *
 * General Public License for more details.                                  *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this program.  If not, see http://www.gnu.org/licenses/.       *
 *                                                                           *
 ****************************************************************************/

/* This code was generated automatically. Do not edit unless you exactly   */
/* know what you are doing!                                                */

namespace implicit_predicates::internal {
// clang-format off

int det2(double p0, double p1,
         double q0, double q1);

int det3(double p0, double p1, double p2,
         double q0, double q1, double q2,
         double r0, double r1, double r2);

int det4(double p0, double p1, double p2, double p3,
         double q0, double q1, double q2, double q3,
         double r0, double r1, double r2, double r3,
         double s0, double s1, double s2, double s3);

int det5(double p0, double p1, double p2, double p3, double p4,
         double q0, double q1, double q2, double q3, double q4,
         double r0, double r1, double r2, double r3, double r4,
         double s0, double s1, double s2, double s3, double s4,
         double t0, double t1, double t2, double t3, double t4);

int diff_det3(double p0, double p1, double p2,
              double q0, double q1, double q2,
              double r0, double r1, double r2,
              double s0, double s1, double s2);

int diff_det3_one(double p0, double p1, double p2,
                  double q0, double q1, double q2,
                  double r0, double r1, double r2);

int diff_det4(double p0, double p1, double p2, double p3,
              double q0, double q1, double q2, double q3,
              double r0, double r1, double r2, double r3,
              double s0, double s1, double s2, double s3,
              double t0, double t1, double t2, double t3);

int diff_det4_one(double p0, double p1, double p2, double p3,
                  double q0, double q1, double q2, double q3,
                  double r0, double r1, double r2, double r3,
                  double s0, double s1, double s2, double s3);

int diff_det2(double p0, double p1,
              double q0, double q1,
              double r0, double r1);

int diff_det2_one(double p0, double p1,
                  double q0, double q1);

// clang-format on
}  // namespace implicit_predicates::internal
