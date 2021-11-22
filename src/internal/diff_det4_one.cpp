#include <implicit_point.h>

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
//#define CHECK_FOR_XYZERFLOWS

namespace implicit_predicates::internal {

int diff_det4_one_filtered(double p0, double p1, double p2, double p3, double q0, double q1, double q2, double q3, double r0, double r1, double r2, double r3, double s0, double s1, double s2, double s3)
{
   double a_ = q0 - p0;
   double b_ = q1 - p1;
   double c_ = q2 - p2;
   double d_ = q3 - p3;
   double e_ = r0 - p0;
   double f_ = r1 - p1;
   double g_ = r2 - p2;
   double h_ = r3 - p3;
   double i_ = s0 - p0;
   double j_ = s1 - p1;
   double k_ = s2 - p2;
   double l_ = s3 - p3;
   double af = a_ * f_;
   double be = b_ * e_;
   double ce = c_ * e_;
   double ag = a_ * g_;
   double ah = a_ * h_;
   double de = d_ * e_;
   double bg = b_ * g_;
   double cf = c_ * f_;
   double df = d_ * f_;
   double bh = b_ * h_;
   double ch = c_ * h_;
   double dg = d_ * g_;
   double d1 = af - be;
   double d2 = k_ - l_;
   double d3 = ce - ag;
   double d4 = j_ - l_;
   double d5 = ah - de;
   double d6 = j_ - k_;
   double d7 = bg - cf;
   double d8 = i_ - l_;
   double d9 = df - bh;
   double d10 = i_ - k_;
   double d11 = ch - dg;
   double d12 = i_ - j_;
   double term1 = d1 * d2;
   double term2 = d3 * d4;
   double term3 = d5 * d6;
   double term4 = d7 * d8;
   double term5 = d9 * d10;
   double term6 = d11 * d12;
   double r12 = term1 + term2;
   double r34 = term3 + term4;
   double r56 = term5 + term6;
   double r1234 = r12 + r34;
   double r123456 = r1234 + r56;

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
   if ((_tmp_fabs = fabs(j_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(k_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(l_)) > max_var) max_var = _tmp_fabs;
   double epsilon = max_var;
   epsilon *= epsilon;
   epsilon *= max_var;
   epsilon *= 2.486899575160352e-14;
   if (r123456 > epsilon) return IP_Sign::POSITIVE;
   if (-r123456 > epsilon) return IP_Sign::NEGATIVE;
   return Filtered_Sign::UNCERTAIN;
}

int diff_det4_one_interval(interval_number p0, interval_number p1, interval_number p2, interval_number p3, interval_number q0, interval_number q1, interval_number q2, interval_number q3, interval_number r0, interval_number r1, interval_number r2, interval_number r3, interval_number s0, interval_number s1, interval_number s2, interval_number s3)
{
   setFPUModeToRoundUP();
   interval_number a_(q0 - p0);
   interval_number b_(q1 - p1);
   interval_number c_(q2 - p2);
   interval_number d_(q3 - p3);
   interval_number e_(r0 - p0);
   interval_number f_(r1 - p1);
   interval_number g_(r2 - p2);
   interval_number h_(r3 - p3);
   interval_number i_(s0 - p0);
   interval_number j_(s1 - p1);
   interval_number k_(s2 - p2);
   interval_number l_(s3 - p3);
   interval_number af(a_ * f_);
   interval_number be(b_ * e_);
   interval_number ce(c_ * e_);
   interval_number ag(a_ * g_);
   interval_number ah(a_ * h_);
   interval_number de(d_ * e_);
   interval_number bg(b_ * g_);
   interval_number cf(c_ * f_);
   interval_number df(d_ * f_);
   interval_number bh(b_ * h_);
   interval_number ch(c_ * h_);
   interval_number dg(d_ * g_);
   interval_number d1(af - be);
   interval_number d2(k_ - l_);
   interval_number d3(ce - ag);
   interval_number d4(j_ - l_);
   interval_number d5(ah - de);
   interval_number d6(j_ - k_);
   interval_number d7(bg - cf);
   interval_number d8(i_ - l_);
   interval_number d9(df - bh);
   interval_number d10(i_ - k_);
   interval_number d11(ch - dg);
   interval_number d12(i_ - j_);
   interval_number term1(d1 * d2);
   interval_number term2(d3 * d4);
   interval_number term3(d5 * d6);
   interval_number term4(d7 * d8);
   interval_number term5(d9 * d10);
   interval_number term6(d11 * d12);
   interval_number r12(term1 + term2);
   interval_number r34(term3 + term4);
   interval_number r56(term5 + term6);
   interval_number r1234(r12 + r34);
   interval_number r123456(r1234 + r56);
   setFPUModeToRoundNEAR();

   if (!r123456.signIsReliable()) return Filtered_Sign::UNCERTAIN;
   return r123456.sign();
}

int diff_det4_one_exact(double p0, double p1, double p2, double p3, double q0, double q1, double q2, double q3, double r0, double r1, double r2, double r3, double s0, double s1, double s2, double s3)
{
   expansionObject o;
   double a_[2];
   o.two_Diff(q0, p0, a_);
   double b_[2];
   o.two_Diff(q1, p1, b_);
   double c_[2];
   o.two_Diff(q2, p2, c_);
   double d_[2];
   o.two_Diff(q3, p3, d_);
   double e_[2];
   o.two_Diff(r0, p0, e_);
   double f_[2];
   o.two_Diff(r1, p1, f_);
   double g_[2];
   o.two_Diff(r2, p2, g_);
   double h_[2];
   o.two_Diff(r3, p3, h_);
   double i_[2];
   o.two_Diff(s0, p0, i_);
   double j_[2];
   o.two_Diff(s1, p1, j_);
   double k_[2];
   o.two_Diff(s2, p2, k_);
   double l_[2];
   o.two_Diff(s3, p3, l_);
   double af[8];
   int af_len = o.Gen_Product(2, a_, 2, f_, af);
   double be[8];
   int be_len = o.Gen_Product(2, b_, 2, e_, be);
   double ce[8];
   int ce_len = o.Gen_Product(2, c_, 2, e_, ce);
   double ag[8];
   int ag_len = o.Gen_Product(2, a_, 2, g_, ag);
   double ah[8];
   int ah_len = o.Gen_Product(2, a_, 2, h_, ah);
   double de[8];
   int de_len = o.Gen_Product(2, d_, 2, e_, de);
   double bg[8];
   int bg_len = o.Gen_Product(2, b_, 2, g_, bg);
   double cf[8];
   int cf_len = o.Gen_Product(2, c_, 2, f_, cf);
   double df[8];
   int df_len = o.Gen_Product(2, d_, 2, f_, df);
   double bh[8];
   int bh_len = o.Gen_Product(2, b_, 2, h_, bh);
   double ch[8];
   int ch_len = o.Gen_Product(2, c_, 2, h_, ch);
   double dg[8];
   int dg_len = o.Gen_Product(2, d_, 2, g_, dg);
   double d1[16];
   int d1_len = o.Gen_Diff(af_len, af, be_len, be, d1);
   double d2[4];
   o.Two_Two_Diff(k_, l_, d2);
   double d3[16];
   int d3_len = o.Gen_Diff(ce_len, ce, ag_len, ag, d3);
   double d4[4];
   o.Two_Two_Diff(j_, l_, d4);
   double d5[16];
   int d5_len = o.Gen_Diff(ah_len, ah, de_len, de, d5);
   double d6[4];
   o.Two_Two_Diff(j_, k_, d6);
   double d7[16];
   int d7_len = o.Gen_Diff(bg_len, bg, cf_len, cf, d7);
   double d8[4];
   o.Two_Two_Diff(i_, l_, d8);
   double d9[16];
   int d9_len = o.Gen_Diff(df_len, df, bh_len, bh, d9);
   double d10[4];
   o.Two_Two_Diff(i_, k_, d10);
   double d11[16];
   int d11_len = o.Gen_Diff(ch_len, ch, dg_len, dg, d11);
   double d12[4];
   o.Two_Two_Diff(i_, j_, d12);
   double term1[128];
   int term1_len = o.Gen_Product(d1_len, d1, 4, d2, term1);
   double term2[128];
   int term2_len = o.Gen_Product(d3_len, d3, 4, d4, term2);
   double term3[128];
   int term3_len = o.Gen_Product(d5_len, d5, 4, d6, term3);
   double term4[128];
   int term4_len = o.Gen_Product(d7_len, d7, 4, d8, term4);
   double term5[128];
   int term5_len = o.Gen_Product(d9_len, d9, 4, d10, term5);
   double term6[128];
   int term6_len = o.Gen_Product(d11_len, d11, 4, d12, term6);
   double r12_p[128], *r12 = r12_p;
   int r12_len = o.Gen_Sum_With_PreAlloc(term1_len, term1, term2_len, term2, &r12, 128);
   double r34_p[128], *r34 = r34_p;
   int r34_len = o.Gen_Sum_With_PreAlloc(term3_len, term3, term4_len, term4, &r34, 128);
   double r56_p[128], *r56 = r56_p;
   int r56_len = o.Gen_Sum_With_PreAlloc(term5_len, term5, term6_len, term6, &r56, 128);
   double r1234_p[128], *r1234 = r1234_p;
   int r1234_len = o.Gen_Sum_With_PreAlloc(r12_len, r12, r34_len, r34, &r1234, 128);
   double r123456_p[128], *r123456 = r123456_p;
   int r123456_len = o.Gen_Sum_With_PreAlloc(r1234_len, r1234, r56_len, r56, &r123456, 128);

   double return_value = r123456[r123456_len - 1];
   if (r123456_p != r123456) free(r123456);
   if (r1234_p != r1234) free(r1234);
   if (r56_p != r56) free(r56);
   if (r34_p != r34) free(r34);
   if (r12_p != r12) free(r12);

 if (return_value > 0) return IP_Sign::POSITIVE;
 if (return_value < 0) return IP_Sign::NEGATIVE;
 if (return_value == 0) return IP_Sign::ZERO;
 return IP_Sign::UNDEFINED;
}

int diff_det4_one(double p0, double p1, double p2, double p3, double q0, double q1, double q2, double q3, double r0, double r1, double r2, double r3, double s0, double s1, double s2, double s3)
{
   int ret;
   ret = diff_det4_one_filtered(p0, p1, p2, p3, q0, q1, q2, q3, r0, r1, r2, r3, s0, s1, s2, s3);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;
   ret = diff_det4_one_interval(p0, p1, p2, p3, q0, q1, q2, q3, r0, r1, r2, r3, s0, s1, s2, s3);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;
   return diff_det4_one_exact(p0, p1, p2, p3, q0, q1, q2, q3, r0, r1, r2, r3, s0, s1, s2, s3);
}

}
