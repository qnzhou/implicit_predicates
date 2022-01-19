#include <implicit_point.h>
#include "stage_stats.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
//#define CHECK_FOR_XYZERFLOWS

namespace implicit_predicates::internal {

int det2_filtered(double p0, double p1, double q0, double q1)
{
   double d1 = p0 * q1;
   double d2 = p1 * q0;
   double m = d1 - d2;

   double _tmp_fabs;

   double max_var = 0.0;
   if ((_tmp_fabs = fabs(p0)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(p1)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(q0)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(q1)) > max_var) max_var = _tmp_fabs;
   double epsilon = max_var;
   epsilon *= epsilon;
   epsilon *= 4.440892098500627e-16;
   if (m > epsilon) return IP_Sign::POSITIVE;
   if (-m > epsilon) return IP_Sign::NEGATIVE;
   return Filtered_Sign::UNCERTAIN;
}

int det2_interval(interval_number p0, interval_number p1, interval_number q0, interval_number q1)
{
   setFPUModeToRoundUP();
   interval_number d1(p0 * q1);
   interval_number d2(p1 * q0);
   interval_number m(d1 - d2);
   setFPUModeToRoundNEAR();

   if (!m.signIsReliable()) return Filtered_Sign::UNCERTAIN;
   return m.sign();
}

int det2_exact(double p0, double p1, double q0, double q1)
{
   expansionObject o;
   double d1[2];
   o.Two_Prod(p0, q1, d1);
   double d2[2];
   o.Two_Prod(p1, q0, d2);
   double m[4];
   o.Two_Two_Diff(d1, d2, m);

   double return_value = m[4 - 1];

 if (return_value > 0) return IP_Sign::POSITIVE;
 if (return_value < 0) return IP_Sign::NEGATIVE;
 if (return_value == 0) return IP_Sign::ZERO;
 return IP_Sign::UNDEFINED;
}

int det2(double p0, double p1, double q0, double q1)
{
   int ret;
#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   semi_static_filter_stage++;
#endif
   ret = det2_filtered(p0, p1, q0, q1);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;

#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   interval_arithmetic_stage++;
#endif
   ret = det2_interval(p0, p1, q0, q1);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;

#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   exact_computation_stage++;
#endif
   return det2_exact(p0, p1, q0, q1);
}

}
