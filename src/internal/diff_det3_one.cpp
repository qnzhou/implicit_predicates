#include <implicit_point.h>

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
//#define CHECK_FOR_XYZERFLOWS

namespace implicit_predicates::internal {

int diff_det3_one_filtered(double p0, double p1, double p2, double q0, double q1, double q2, double r0, double r1, double r2)
{
   double a_ = q0 - p0;
   double b_ = q1 - p1;
   double c_ = q2 - p2;
   double d_ = r0 - p0;
   double e_ = r1 - p1;
   double f_ = r2 - p2;
   double bf = b_ * f_;
   double ce = c_ * e_;
   double af = a_ * f_;
   double cd = c_ * d_;
   double ae = a_ * e_;
   double bd = b_ * d_;
   double bf_ce = bf - ce;
   double af_cd = af - cd;
   double ae_bd = ae - bd;
   double result0 = bf_ce - af_cd;
   double result = result0 + ae_bd;

   double _tmp_fabs;

   double max_var = 0.0;
   if ((_tmp_fabs = fabs(a_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(b_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(c_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(d_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(e_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(f_)) > max_var) max_var = _tmp_fabs;
   double epsilon = max_var;
   epsilon *= epsilon;
   epsilon *= 3.552713678800501e-15;
   if (result > epsilon) return IP_Sign::POSITIVE;
   if (-result > epsilon) return IP_Sign::NEGATIVE;
   return Filtered_Sign::UNCERTAIN;
}

int diff_det3_one_interval(interval_number p0, interval_number p1, interval_number p2, interval_number q0, interval_number q1, interval_number q2, interval_number r0, interval_number r1, interval_number r2)
{
   setFPUModeToRoundUP();
   interval_number a_(q0 - p0);
   interval_number b_(q1 - p1);
   interval_number c_(q2 - p2);
   interval_number d_(r0 - p0);
   interval_number e_(r1 - p1);
   interval_number f_(r2 - p2);
   interval_number bf(b_ * f_);
   interval_number ce(c_ * e_);
   interval_number af(a_ * f_);
   interval_number cd(c_ * d_);
   interval_number ae(a_ * e_);
   interval_number bd(b_ * d_);
   interval_number bf_ce(bf - ce);
   interval_number af_cd(af - cd);
   interval_number ae_bd(ae - bd);
   interval_number result0(bf_ce - af_cd);
   interval_number result(result0 + ae_bd);
   setFPUModeToRoundNEAR();

   if (!result.signIsReliable()) return Filtered_Sign::UNCERTAIN;
   return result.sign();
}

int diff_det3_one_exact(double p0, double p1, double p2, double q0, double q1, double q2, double r0, double r1, double r2)
{
   expansionObject o;
   double a_[2];
   o.two_Diff(q0, p0, a_);
   double b_[2];
   o.two_Diff(q1, p1, b_);
   double c_[2];
   o.two_Diff(q2, p2, c_);
   double d_[2];
   o.two_Diff(r0, p0, d_);
   double e_[2];
   o.two_Diff(r1, p1, e_);
   double f_[2];
   o.two_Diff(r2, p2, f_);
   double bf[8];
   int bf_len = o.Gen_Product(2, b_, 2, f_, bf);
   double ce[8];
   int ce_len = o.Gen_Product(2, c_, 2, e_, ce);
   double af[8];
   int af_len = o.Gen_Product(2, a_, 2, f_, af);
   double cd[8];
   int cd_len = o.Gen_Product(2, c_, 2, d_, cd);
   double ae[8];
   int ae_len = o.Gen_Product(2, a_, 2, e_, ae);
   double bd[8];
   int bd_len = o.Gen_Product(2, b_, 2, d_, bd);
   double bf_ce[16];
   int bf_ce_len = o.Gen_Diff(bf_len, bf, ce_len, ce, bf_ce);
   double af_cd[16];
   int af_cd_len = o.Gen_Diff(af_len, af, cd_len, cd, af_cd);
   double ae_bd[16];
   int ae_bd_len = o.Gen_Diff(ae_len, ae, bd_len, bd, ae_bd);
   double result0[32];
   int result0_len = o.Gen_Diff(bf_ce_len, bf_ce, af_cd_len, af_cd, result0);
   double result[48];
   int result_len = o.Gen_Sum(result0_len, result0, ae_bd_len, ae_bd, result);

   double return_value = result[result_len - 1];

 if (return_value > 0) return IP_Sign::POSITIVE;
 if (return_value < 0) return IP_Sign::NEGATIVE;
 if (return_value == 0) return IP_Sign::ZERO;
 return IP_Sign::UNDEFINED;
}

int diff_det3_one(double p0, double p1, double p2, double q0, double q1, double q2, double r0, double r1, double r2)
{
   int ret;
   ret = diff_det3_one_filtered(p0, p1, p2, q0, q1, q2, r0, r1, r2);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;
   ret = diff_det3_one_interval(p0, p1, p2, q0, q1, q2, r0, r1, r2);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;
   return diff_det3_one_exact(p0, p1, p2, q0, q1, q2, r0, r1, r2);
}

}
