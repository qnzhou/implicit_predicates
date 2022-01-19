#include <implicit_point.h>
#include "stage_stats.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
//#define CHECK_FOR_XYZERFLOWS

namespace implicit_predicates::internal {

int det3_filtered(double p0, double p1, double p2, double q0, double q1, double q2, double r0, double r1, double r2)
{
   double q0r1 = q0 * r1;
   double q1r0 = q1 * r0;
   double q1r2 = q1 * r2;
   double q2r1 = q2 * r1;
   double q2r0 = q2 * r0;
   double q0r2 = q0 * r2;
   double d0 = q1r2 - q2r1;
   double d1 = q2r0 - q0r2;
   double d2 = q0r1 - q1r0;
   double m0 = p0 * d0;
   double m1 = p1 * d1;
   double m2 = p2 * d2;
   double m01 = m0 + m1;
   double m = m01 + m2;

   double _tmp_fabs;

   double max_var = 0.0;
   if ((_tmp_fabs = fabs(p0)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(p1)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(p2)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(q0)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(q1)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(q2)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(r0)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(r1)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(r2)) > max_var) max_var = _tmp_fabs;
   double epsilon = max_var;
   epsilon *= epsilon;
   epsilon *= max_var;
   epsilon *= 2.886579864025408e-15;
   if (m > epsilon) return IP_Sign::POSITIVE;
   if (-m > epsilon) return IP_Sign::NEGATIVE;
   return Filtered_Sign::UNCERTAIN;
}

int det3_interval(interval_number p0, interval_number p1, interval_number p2, interval_number q0, interval_number q1, interval_number q2, interval_number r0, interval_number r1, interval_number r2)
{
   setFPUModeToRoundUP();
   interval_number q0r1(q0 * r1);
   interval_number q1r0(q1 * r0);
   interval_number q1r2(q1 * r2);
   interval_number q2r1(q2 * r1);
   interval_number q2r0(q2 * r0);
   interval_number q0r2(q0 * r2);
   interval_number d0(q1r2 - q2r1);
   interval_number d1(q2r0 - q0r2);
   interval_number d2(q0r1 - q1r0);
   interval_number m0(p0 * d0);
   interval_number m1(p1 * d1);
   interval_number m2(p2 * d2);
   interval_number m01(m0 + m1);
   interval_number m(m01 + m2);
   setFPUModeToRoundNEAR();

   if (!m.signIsReliable()) return Filtered_Sign::UNCERTAIN;
   return m.sign();
}

int det3_exact(double p0, double p1, double p2, double q0, double q1, double q2, double r0, double r1, double r2)
{
   expansionObject o;
   double q0r1[2];
   o.Two_Prod(q0, r1, q0r1);
   double q1r0[2];
   o.Two_Prod(q1, r0, q1r0);
   double q1r2[2];
   o.Two_Prod(q1, r2, q1r2);
   double q2r1[2];
   o.Two_Prod(q2, r1, q2r1);
   double q2r0[2];
   o.Two_Prod(q2, r0, q2r0);
   double q0r2[2];
   o.Two_Prod(q0, r2, q0r2);
   double d0[4];
   o.Two_Two_Diff(q1r2, q2r1, d0);
   double d1[4];
   o.Two_Two_Diff(q2r0, q0r2, d1);
   double d2[4];
   o.Two_Two_Diff(q0r1, q1r0, d2);
   double m0[8];
   int m0_len = o.Gen_Scale(4, d0, p0, m0);
   double m1[8];
   int m1_len = o.Gen_Scale(4, d1, p1, m1);
   double m2[8];
   int m2_len = o.Gen_Scale(4, d2, p2, m2);
   double m01[16];
   int m01_len = o.Gen_Sum(m0_len, m0, m1_len, m1, m01);
   double m[24];
   int m_len = o.Gen_Sum(m01_len, m01, m2_len, m2, m);

   double return_value = m[m_len - 1];

 if (return_value > 0) return IP_Sign::POSITIVE;
 if (return_value < 0) return IP_Sign::NEGATIVE;
 if (return_value == 0) return IP_Sign::ZERO;
 return IP_Sign::UNDEFINED;
}

int det3(double p0, double p1, double p2, double q0, double q1, double q2, double r0, double r1, double r2)
{
   int ret;
#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   semi_static_filter_stage++;
#endif
   ret = det3_filtered(p0, p1, p2, q0, q1, q2, r0, r1, r2);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;

#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   interval_arithmetic_stage++;
#endif
   ret = det3_interval(p0, p1, p2, q0, q1, q2, r0, r1, r2);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;

#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   exact_computation_stage++;
#endif
   return det3_exact(p0, p1, p2, q0, q1, q2, r0, r1, r2);
}

}
