#include <implicit_point.h>

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
//#define CHECK_FOR_XYZERFLOWS

namespace implicit_predicates::internal {

int diff_det2_filtered(double p0, double p1, double q0, double q1, double r0, double r1)
{
   double a_ = q0 - p0;
   double b_ = q1 - p1;
   double c_ = r0 - p0;
   double d_ = r1 - p1;
   double ad = a_ * d_;
   double bc = b_ * c_;
   double result = ad - bc;

   double _tmp_fabs;

   double max_var = 0.0;
   if ((_tmp_fabs = fabs(a_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(b_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(c_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(d_)) > max_var) max_var = _tmp_fabs;
   double epsilon = max_var;
   epsilon *= epsilon;
   epsilon *= 8.881784197001253e-16;
   if (result > epsilon) return IP_Sign::POSITIVE;
   if (-result > epsilon) return IP_Sign::NEGATIVE;
   return Filtered_Sign::UNCERTAIN;
}

int diff_det2_interval(interval_number p0, interval_number p1, interval_number q0, interval_number q1, interval_number r0, interval_number r1)
{
   setFPUModeToRoundUP();
   interval_number a_(q0 - p0);
   interval_number b_(q1 - p1);
   interval_number c_(r0 - p0);
   interval_number d_(r1 - p1);
   interval_number ad(a_ * d_);
   interval_number bc(b_ * c_);
   interval_number result(ad - bc);
   setFPUModeToRoundNEAR();

   if (!result.signIsReliable()) return Filtered_Sign::UNCERTAIN;
   return result.sign();
}

int diff_det2_exact(double p0, double p1, double q0, double q1, double r0, double r1)
{
   expansionObject o;
   double a_[2];
   o.two_Diff(q0, p0, a_);
   double b_[2];
   o.two_Diff(q1, p1, b_);
   double c_[2];
   o.two_Diff(r0, p0, c_);
   double d_[2];
   o.two_Diff(r1, p1, d_);
   double ad[8];
   int ad_len = o.Gen_Product(2, a_, 2, d_, ad);
   double bc[8];
   int bc_len = o.Gen_Product(2, b_, 2, c_, bc);
   double result[16];
   int result_len = o.Gen_Diff(ad_len, ad, bc_len, bc, result);

   double return_value = result[result_len - 1];

 if (return_value > 0) return IP_Sign::POSITIVE;
 if (return_value < 0) return IP_Sign::NEGATIVE;
 if (return_value == 0) return IP_Sign::ZERO;
 return IP_Sign::UNDEFINED;
}

int diff_det2(double p0, double p1, double q0, double q1, double r0, double r1)
{
   int ret;
   ret = diff_det2_filtered(p0, p1, q0, q1, r0, r1);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;
   ret = diff_det2_interval(p0, p1, q0, q1, r0, r1);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;
   return diff_det2_exact(p0, p1, q0, q1, r0, r1);
}

}
