#include <implicit_point.h>
#include "stage_stats.h"

#pragma intrinsic(fabs)

// Uncomment the following to activate overflow/underflow checks
//#define CHECK_FOR_XYZERFLOWS

namespace implicit_predicates::internal {

int det4_filtered(double a_, double b_, double c_, double d_, double e_, double f_, double g_, double h_, double i_, double j_, double k_, double l_, double m_, double n_, double o_, double p_)
{
   double af = a_ * f_;
   double be = b_ * e_;
   double kp = k_ * p_;
   double lo = l_ * o_;
   double ce = c_ * e_;
   double ag = a_ * g_;
   double jp = j_ * p_;
   double ln = l_ * n_;
   double ah = a_ * h_;
   double de = d_ * e_;
   double jo = j_ * o_;
   double kn = k_ * n_;
   double bg = b_ * g_;
   double cf = c_ * f_;
   double ip = i_ * p_;
   double lm = l_ * m_;
   double df = d_ * f_;
   double bh = b_ * h_;
   double io = i_ * o_;
   double km = k_ * m_;
   double ch = c_ * h_;
   double dg = d_ * g_;
   double in = i_ * n_;
   double jm = j_ * m_;
   double d1 = af - be;
   double d2 = kp - lo;
   double d3 = ce - ag;
   double d4 = jp - ln;
   double d5 = ah - de;
   double d6 = jo - kn;
   double d7 = bg - cf;
   double d8 = ip - lm;
   double d9 = df - bh;
   double d10 = io - km;
   double d11 = ch - dg;
   double d12 = in - jm;
   double t1 = d1 * d2;
   double t2 = d3 * d4;
   double t3 = d5 * d6;
   double t4 = d7 * d8;
   double t5 = d9 * d10;
   double t6 = d11 * d12;
   double r12 = t1 + t2;
   double r34 = t3 + t4;
   double r56 = t5 + t6;
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
   if ((_tmp_fabs = fabs(m_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(n_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(o_)) > max_var) max_var = _tmp_fabs;
   if ((_tmp_fabs = fabs(p_)) > max_var) max_var = _tmp_fabs;
   double epsilon = max_var;
   epsilon *= epsilon;
   epsilon *= epsilon;
   epsilon *= 1.953992523340277e-14;
   if (r123456 > epsilon) return IP_Sign::POSITIVE;
   if (-r123456 > epsilon) return IP_Sign::NEGATIVE;
   return Filtered_Sign::UNCERTAIN;
}

int det4_interval(interval_number a_, interval_number b_, interval_number c_, interval_number d_, interval_number e_, interval_number f_, interval_number g_, interval_number h_, interval_number i_, interval_number j_, interval_number k_, interval_number l_, interval_number m_, interval_number n_, interval_number o_, interval_number p_)
{
   setFPUModeToRoundUP();
   interval_number af(a_ * f_);
   interval_number be(b_ * e_);
   interval_number kp(k_ * p_);
   interval_number lo(l_ * o_);
   interval_number ce(c_ * e_);
   interval_number ag(a_ * g_);
   interval_number jp(j_ * p_);
   interval_number ln(l_ * n_);
   interval_number ah(a_ * h_);
   interval_number de(d_ * e_);
   interval_number jo(j_ * o_);
   interval_number kn(k_ * n_);
   interval_number bg(b_ * g_);
   interval_number cf(c_ * f_);
   interval_number ip(i_ * p_);
   interval_number lm(l_ * m_);
   interval_number df(d_ * f_);
   interval_number bh(b_ * h_);
   interval_number io(i_ * o_);
   interval_number km(k_ * m_);
   interval_number ch(c_ * h_);
   interval_number dg(d_ * g_);
   interval_number in(i_ * n_);
   interval_number jm(j_ * m_);
   interval_number d1(af - be);
   interval_number d2(kp - lo);
   interval_number d3(ce - ag);
   interval_number d4(jp - ln);
   interval_number d5(ah - de);
   interval_number d6(jo - kn);
   interval_number d7(bg - cf);
   interval_number d8(ip - lm);
   interval_number d9(df - bh);
   interval_number d10(io - km);
   interval_number d11(ch - dg);
   interval_number d12(in - jm);
   interval_number t1(d1 * d2);
   interval_number t2(d3 * d4);
   interval_number t3(d5 * d6);
   interval_number t4(d7 * d8);
   interval_number t5(d9 * d10);
   interval_number t6(d11 * d12);
   interval_number r12(t1 + t2);
   interval_number r34(t3 + t4);
   interval_number r56(t5 + t6);
   interval_number r1234(r12 + r34);
   interval_number r123456(r1234 + r56);
   setFPUModeToRoundNEAR();

   if (!r123456.signIsReliable()) return Filtered_Sign::UNCERTAIN;
   return r123456.sign();
}

int det4_exact(double a_, double b_, double c_, double d_, double e_, double f_, double g_, double h_, double i_, double j_, double k_, double l_, double m_, double n_, double o_, double p_)
{
   expansionObject o;
   double af[2];
   o.Two_Prod(a_, f_, af);
   double be[2];
   o.Two_Prod(b_, e_, be);
   double kp[2];
   o.Two_Prod(k_, p_, kp);
   double lo[2];
   o.Two_Prod(l_, o_, lo);
   double ce[2];
   o.Two_Prod(c_, e_, ce);
   double ag[2];
   o.Two_Prod(a_, g_, ag);
   double jp[2];
   o.Two_Prod(j_, p_, jp);
   double ln[2];
   o.Two_Prod(l_, n_, ln);
   double ah[2];
   o.Two_Prod(a_, h_, ah);
   double de[2];
   o.Two_Prod(d_, e_, de);
   double jo[2];
   o.Two_Prod(j_, o_, jo);
   double kn[2];
   o.Two_Prod(k_, n_, kn);
   double bg[2];
   o.Two_Prod(b_, g_, bg);
   double cf[2];
   o.Two_Prod(c_, f_, cf);
   double ip[2];
   o.Two_Prod(i_, p_, ip);
   double lm[2];
   o.Two_Prod(l_, m_, lm);
   double df[2];
   o.Two_Prod(d_, f_, df);
   double bh[2];
   o.Two_Prod(b_, h_, bh);
   double io[2];
   o.Two_Prod(i_, o_, io);
   double km[2];
   o.Two_Prod(k_, m_, km);
   double ch[2];
   o.Two_Prod(c_, h_, ch);
   double dg[2];
   o.Two_Prod(d_, g_, dg);
   double in[2];
   o.Two_Prod(i_, n_, in);
   double jm[2];
   o.Two_Prod(j_, m_, jm);
   double d1[4];
   o.Two_Two_Diff(af, be, d1);
   double d2[4];
   o.Two_Two_Diff(kp, lo, d2);
   double d3[4];
   o.Two_Two_Diff(ce, ag, d3);
   double d4[4];
   o.Two_Two_Diff(jp, ln, d4);
   double d5[4];
   o.Two_Two_Diff(ah, de, d5);
   double d6[4];
   o.Two_Two_Diff(jo, kn, d6);
   double d7[4];
   o.Two_Two_Diff(bg, cf, d7);
   double d8[4];
   o.Two_Two_Diff(ip, lm, d8);
   double d9[4];
   o.Two_Two_Diff(df, bh, d9);
   double d10[4];
   o.Two_Two_Diff(io, km, d10);
   double d11[4];
   o.Two_Two_Diff(ch, dg, d11);
   double d12[4];
   o.Two_Two_Diff(in, jm, d12);
   double t1[32];
   int t1_len = o.Gen_Product(4, d1, 4, d2, t1);
   double t2[32];
   int t2_len = o.Gen_Product(4, d3, 4, d4, t2);
   double t3[32];
   int t3_len = o.Gen_Product(4, d5, 4, d6, t3);
   double t4[32];
   int t4_len = o.Gen_Product(4, d7, 4, d8, t4);
   double t5[32];
   int t5_len = o.Gen_Product(4, d9, 4, d10, t5);
   double t6[32];
   int t6_len = o.Gen_Product(4, d11, 4, d12, t6);
   double r12[64];
   int r12_len = o.Gen_Sum(t1_len, t1, t2_len, t2, r12);
   double r34[64];
   int r34_len = o.Gen_Sum(t3_len, t3, t4_len, t4, r34);
   double r56[64];
   int r56_len = o.Gen_Sum(t5_len, t5, t6_len, t6, r56);
   double r1234[128];
   int r1234_len = o.Gen_Sum(r12_len, r12, r34_len, r34, r1234);
   double r123456_p[128], *r123456 = r123456_p;
   int r123456_len = o.Gen_Sum_With_PreAlloc(r1234_len, r1234, r56_len, r56, &r123456, 128);

   double return_value = r123456[r123456_len - 1];
   if (r123456_p != r123456) free(r123456);

 if (return_value > 0) return IP_Sign::POSITIVE;
 if (return_value < 0) return IP_Sign::NEGATIVE;
 if (return_value == 0) return IP_Sign::ZERO;
 return IP_Sign::UNDEFINED;
}

int det4(double a_, double b_, double c_, double d_, double e_, double f_, double g_, double h_, double i_, double j_, double k_, double l_, double m_, double n_, double o_, double p_)
{
   int ret;
#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   semi_static_filter_stage++;
#endif
   ret = det4_filtered(a_, b_, c_, d_, e_, f_, g_, h_, i_, j_, k_, l_, m_, n_, o_, p_);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;

#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   interval_arithmetic_stage++;
#endif
   ret = det4_interval(a_, b_, c_, d_, e_, f_, g_, h_, i_, j_, k_, l_, m_, n_, o_, p_);
   if (ret != Filtered_Sign::UNCERTAIN) return ret;

#ifdef IMPLICIT_PREDICATES_STAGE_STATS
   exact_computation_stage++;
#endif
   return det4_exact(a_, b_, c_, d_, e_, f_, g_, h_, i_, j_, k_, l_, m_, n_, o_, p_);
}

}
