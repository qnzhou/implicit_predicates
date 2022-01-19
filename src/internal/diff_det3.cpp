#include <implicit_point.h>
#include "stage_stats.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
//#define CHECK_FOR_XYZERFLOWS

namespace implicit_predicates::internal {

int diff_det3_filtered(double p0, double p1, double p2, double q0, double q1, double q2, double r0, double r1, double r2, double s0, double s1, double s2)
{
   double a_ = q0 - p0;
   double b_ = q1 - p1;
   double c_ = q2 - p2;
   double d_ = r0 - p0;
   double e_ = r1 - p1;
   double f_ = r2 - p2;
   double g_ = s0 - p0;
   double h_ = s1 - p1;
   double i_ = s2 - p2;
   double ei = e_ * i_;
   double fh = f_ * h_;
   double di = d_ * i_;
   double gf = g_ * f_;
   double dh = d_ * h_;
   double eg = e_ * g_;
   double ei_fh = ei - fh;
   double di_gf = di - gf;
   double dh_eg = dh - eg;
   double a__ei_fh = a_ * ei_fh;
   double b__di_gf = b_ * di_gf;
   double c__dh_eg = c_ * dh_eg;
   double result0 = a__ei_fh - b__di_gf;
   double result = result0 + c__dh_eg;

   double _tmp_fabs;

   double max_var = 0.0;
   if ((_tmp_fabs = fabs(a_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(b_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(c_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(d_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(e_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(f_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(g_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(h_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(i_)) > max_var) max_var = _tmp_fabs;
   double epsilon = max_var;
   epsilon *= epsilon;
   epsilon *= max_var;
   epsilon *= 4.884981308350689e-15;
   if (result > epsilon) return IP_Sign::POSITIVE;
   if (-result > epsilon) return IP_Sign::NEGATIVE;
   return Filtered_Sign::UNCERTAIN;
}

int diff_det3_interval(interval_number p0, interval_number p1, interval_number p2, interval_number q0, interval_number q1, interval_number q2, interval_number r0, interval_number r1, interval_number r2, interval_number s0, interval_number s1, interval_number s2)
{
   setFPUModeToRoundUP();
   interval_number a_(q0 - p0);
   interval_number b_(q1 - p1);
   interval_number c_(q2 - p2);
   interval_number d_(r0 - p0);
   interval_number e_(r1 - p1);
   interval_number f_(r2 - p2);
   interval_number g_(s0 - p0);
   interval_number h_(s1 - p1);
   interval_number i_(s2 - p2);
   interval_number ei(e_ * i_);
   interval_number fh(f_ * h_);
   interval_number di(d_ * i_);
   interval_number gf(g_ * f_);
   interval_number dh(d_ * h_);
   interval_number eg(e_ * g_);
   interval_number ei_fh(ei - fh);
   interval_number di_gf(di - gf);
   interval_number dh_eg(dh - eg);
   interval_number a__ei_fh(a_ * ei_fh);
   interval_number b__di_gf(b_ * di_gf);
   interval_number c__dh_eg(c_ * dh_eg);
   interval_number result0(a__ei_fh - b__di_gf);
   interval_number result(result0 + c__dh_eg);
   setFPUModeToRoundNEAR();

   if (!result.signIsReliable()) return Filtered_Sign::UNCERTAIN;
   return result.sign();
}

int diff_det3_exact(double p0, double p1, double p2, double q0, double q1, double q2, double r0, double r1, double r2, double s0, double s1, double s2)
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
   double g_[2];
   o.two_Diff(s0, p0, g_);
   double h_[2];
   o.two_Diff(s1, p1, h_);
   double i_[2];
   o.two_Diff(s2, p2, i_);
   double ei[8];
   int ei_len = o.Gen_Product(2, e_, 2, i_, ei);
   double fh[8];
   int fh_len = o.Gen_Product(2, f_, 2, h_, fh);
   double di[8];
   int di_len = o.Gen_Product(2, d_, 2, i_, di);
   double gf[8];
   int gf_len = o.Gen_Product(2, g_, 2, f_, gf);
   double dh[8];
   int dh_len = o.Gen_Product(2, d_, 2, h_, dh);
   double eg[8];
   int eg_len = o.Gen_Product(2, e_, 2, g_, eg);
   double ei_fh[16];
   int ei_fh_len = o.Gen_Diff(ei_len, ei, fh_len, fh, ei_fh);
   double di_gf[16];
   int di_gf_len = o.Gen_Diff(di_len, di, gf_len, gf, di_gf);
   double dh_eg[16];
   int dh_eg_len = o.Gen_Diff(dh_len, dh, eg_len, eg, dh_eg);
   double a__ei_fh[64];
   int a__ei_fh_len = o.Gen_Product(2, a_, ei_fh_len, ei_fh, a__ei_fh);
   double b__di_gf[64];
   int b__di_gf_len = o.Gen_Product(2, b_, di_gf_len, di_gf, b__di_gf);
   double c__dh_eg[64];
   int c__dh_eg_len = o.Gen_Product(2, c_, dh_eg_len, dh_eg, c__dh_eg);
   double result0[128];
   int result0_len = o.Gen_Diff(a__ei_fh_len, a__ei_fh, b__di_gf_len, b__di_gf, result0);
   double result_p[128], *result = result_p;
   int result_len = o.Gen_Sum_With_PreAlloc(result0_len, result0, c__dh_eg_len, c__dh_eg, &result, 128);

   double return_value = result[result_len - 1];
   if (result_p != result) free(result);

 if (return_value > 0) return IP_Sign::POSITIVE;
 if (return_value < 0) return IP_Sign::NEGATIVE;
 if (return_value == 0) return IP_Sign::ZERO;
 return IP_Sign::UNDEFINED;
}

int diff_det3(double p0, double p1, double p2, double q0, double q1, double q2, double r0, double r1, double r2, double s0, double s1, double s2)
{
   int ret;
#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   semi_static_filter_stage++;
#endif
   ret = diff_det3_filtered(p0, p1, p2, q0, q1, q2, r0, r1, r2, s0, s1, s2);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;

#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   interval_arithmetic_stage++;
#endif
   ret = diff_det3_interval(p0, p1, p2, q0, q1, q2, r0, r1, r2, s0, s1, s2);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;

#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   exact_computation_stage++;
#endif
   return diff_det3_exact(p0, p1, p2, q0, q1, q2, r0, r1, r2, s0, s1, s2);
}

}
