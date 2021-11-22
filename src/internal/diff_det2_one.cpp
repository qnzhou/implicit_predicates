#include <implicit_point.h>

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
//#define CHECK_FOR_XYZERFLOWS

namespace implicit_predicates::internal {

int diff_det2_one_filtered(double p0, double p1, double q0, double q1)
{
   double a_ = q0 - p0;
   double b_ = q1 - p1;
   double result = a_ - b_;

   double _tmp_fabs;

   double max_var = 0.0;
   if ((_tmp_fabs = fabs(a_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(b_)) > max_var) max_var = _tmp_fabs;
   double epsilon = max_var;
   epsilon *= 4.440892098500627e-16;
   if (result > epsilon) return IP_Sign::POSITIVE;
   if (-result > epsilon) return IP_Sign::NEGATIVE;
   return Filtered_Sign::UNCERTAIN;
}

int diff_det2_one_interval(interval_number p0, interval_number p1, interval_number q0, interval_number q1)
{
   setFPUModeToRoundUP();
   interval_number a_(q0 - p0);
   interval_number b_(q1 - p1);
   interval_number result(a_ - b_);
   setFPUModeToRoundNEAR();

   if (!result.signIsReliable()) return Filtered_Sign::UNCERTAIN;
   return result.sign();
}

int diff_det2_one_exact(double p0, double p1, double q0, double q1)
{
   expansionObject o;
   double a_[2];
   o.two_Diff(q0, p0, a_);
   double b_[2];
   o.two_Diff(q1, p1, b_);
   double result[4];
   o.Two_Two_Diff(a_, b_, result);

   double return_value = result[4 - 1];

 if (return_value > 0) return IP_Sign::POSITIVE;
 if (return_value < 0) return IP_Sign::NEGATIVE;
 if (return_value == 0) return IP_Sign::ZERO;
 return IP_Sign::UNDEFINED;
}

int diff_det2_one(double p0, double p1, double q0, double q1)
{
   int ret;
   ret = diff_det2_one_filtered(p0, p1, q0, q1);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;
   ret = diff_det2_one_interval(p0, p1, q0, q1);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;
   return diff_det2_one_exact(p0, p1, q0, q1);
}

}
