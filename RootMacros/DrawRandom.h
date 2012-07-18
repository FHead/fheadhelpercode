//----------------------------------------------------------------------------
#ifndef DrawRandom_H_AJGRKJVCGTZRHISCGGARHWGCA
#define DrawRandom_H_AJGRKJVCGTZRHISCGGARHWGCA
//----------------------------------------------------------------------------
// Custom sampling functions
// Author: Yi Chen
//----------------------------------------------------------------------------
#include <cmath>
#include <cstdlib>
//----------------------------------------------------------------------------
#define PI 3.14159265358979323846264338327950288479716939937510
//----------------------------------------------------------------------------
double DrawRandom();
double DrawRandom(double max);
double DrawRandom(double min, double max);
double DrawSine(double min, double max);
double DrawLorentzian(double center, double gamma);
double DrawGaussian(double center, double sigma);
double DrawGaussian(double sigma);
double DrawGaussian();
double DrawCruijff(double center, double sigmal, double sigmar, double alphal, double alphar);
double DrawExponential(double exponent, double left, double right);
double DrawExponential(double exponent, double side);
double DrawPoisson(double mean);
double DrawPoissonDouble(double mean);
double DrawDoubleSidedCBShape(double Mean, double Sigma, double AlphaL, double AlphaR, double NL, double NR);
double DrawDoubleSidedCBShape(double AlphaL, double AlphaR, double NL, double NR);
//----------------------------------------------------------------------------
double DrawRandom()
{
   double Value1 = double(rand() % 100000) / 100000;
   double Value2 = double(rand() % 100000) / 100000;
   return Value1 + Value2 / 100000;
}
//----------------------------------------------------------------------------
double DrawRandom(double max)
{
   return max * DrawRandom();
}
//----------------------------------------------------------------------------
double DrawRandom(double min, double max)
{
   return min + (max - min) * DrawRandom();
}
//----------------------------------------------------------------------------
double DrawSine(double min, double max)
{
   bool OK = false;
   double answer = 0;

   while(OK == false)
   {
      answer = DrawRandom(min, max);
      double check = DrawRandom();

      if(check < sin(answer))
         OK = true;
   }

   return answer;
}
//----------------------------------------------------------------------------
double DrawLorentzian(double center, double gamma)
{
   if(gamma <= 0)
      return center;

   bool OK = false;
   double displacement = 0;

   double DistributionMax = 4 / gamma / gamma;

   // functional form:
   //    const / (dx^2 + (gamma^2 / 4))
   //    const is (gamma / 2 / PI), for reference

   while(OK == false)
   {
      displacement = DrawRandom(-gamma * 20, gamma * 20);
      double check = DrawRandom(DistributionMax);

      if(check < 1 / (displacement * displacement + gamma * gamma / 4))
         OK = true;
   }

   return center + displacement;
}
//----------------------------------------------------------------------------
double DrawGaussian(double center, double sigma)
{
   return center + DrawGaussian(sigma);
}
//----------------------------------------------------------------------------
double DrawGaussian(double sigma)
{
   if(sigma <= 0)
      return 0;

   bool OK = false;
   double value = 0;

   // form: exp(-x^2/(2 sigma^2))
   while(OK == false)
   {
      value = DrawRandom(-sigma * 15, sigma * 15);
      double check = DrawRandom();

      if(check < exp(-value * value / 2 / sigma / sigma))
         OK = true;
   }

   return value;
}
//----------------------------------------------------------------------------
double DrawGaussianBoxMuller()
{
   double x1 = DrawRandom();
   double x2 = DrawRandom();

   return sqrt(-2 * log(x1)) * cos(2 * PI * x2);
}
//----------------------------------------------------------------------------
double DrawCruijff(double center, double sigmal, double sigmar, double alphal, double alphar)
{
   if(sigmal <= 0 || sigmar <= 0 || alphal <= 0 || alphar <= 0)
      return 0;

   bool OK = false;
   double value = 0;

   while(OK == false)
   {
      value = DrawRandom(-sigmal * 40, sigmar * 40);
      double check = DrawRandom();

      double functionvalue = 0;
      if(value > 0)
         functionvalue = exp(-value * value / (2 * sigmar * sigmar + alphar * alphar * value * value));
      else
         functionvalue = exp(-value * value / (2 * sigmal * sigmal + alphal * alphal * value * value));

      if(check < functionvalue)
         OK = true;
   }

   return value + center;
}
//----------------------------------------------------------------------------
double DrawCruijff(double center, double sigmal, double sigmar, double alphal, double alphar, double left, double right)
{
   if(sigmal <= 0 || sigmar <= 0 || alphal <= 0 || alphar <= 0)
      return 0;

   bool OK = false;
   double value = 0;

   while(OK == false)
   {
      value = DrawRandom(left - center, right - center);
      double check = DrawRandom();

      double functionvalue = 0;
      if(value > 0)
         functionvalue = exp(-value * value / (2 * sigmar * sigmar + alphar * alphar * value * value));
      else
         functionvalue = exp(-value * value / (2 * sigmal * sigmal + alphal * alphal * value * value));

      if(check < functionvalue)
         OK = true;
   }

   return value + center;
}
//----------------------------------------------------------------------------
double DrawExponential(double exponent, double left, double right)
{
   if(exponent > 0)
   {
      double result = DrawExponential(-exponent, left, right);
      result = left + right - result;
      return result;
   }

   if(right < left)
      std::swap(left, right);

   double value = 0;
   bool OK = false;

   while(OK == false)
   {
      value = DrawRandom(right - left);
      double check = DrawRandom();

      if(check < exp(value * exponent))
         OK = true;
   }

   return value + left;
}
//----------------------------------------------------------------------------
double DrawExponential(double exponent, double side)
{
   if(exponent == 0)
      return side;

   if(exponent > 0)
   {
      double Distance = DrawExponential(-exponent, 0);
      return side - Distance;
   }

   double Distance = 0;

   bool OK = false;
   while(OK == false)
   {
      double value = DrawRandom(0, 1);
      if(value < exp(-1))   // not within this decay length
         Distance = Distance + 1 / fabs(exponent);
      else   // within this decay length
         OK = true;
   }

   OK = false;
   while(OK == false)
   {
      double value = DrawRandom(0, 1);   // determine exactly where in this range
      double check = DrawRandom(0, 1);

      if(check < exp(-value))
      {
         Distance = Distance + value / fabs(exponent);
         OK = true;
      }
   }

   return Distance + side;
}
//----------------------------------------------------------------------------
double DrawPoisson(double mean)
{
   if(mean <= 0)
      return 0;

   if(mean > 20)
      return DrawGaussian(mean, sqrt(mean));

   int value = 0;
   bool OK = false;

   while(OK == false)
   {
      value = (int)DrawRandom(mean * 1.5 + 10);
      double check = DrawRandom();

      double functionvalue = 1;
      for(int i = 0; i < value; i++)
         functionvalue = functionvalue * mean / (value - i);
      functionvalue = functionvalue * exp(-mean);

      if(check < functionvalue)
         OK = true;
   }

   return value;
}
//----------------------------------------------------------------------------
double DrawDoubleSidedCBShape(double Mean, double Sigma, double AlphaL, double AlphaR, double NL, double NR)
{
   return Mean + DrawDoubleSidedCBShape(AlphaL, AlphaR, NL, NR) * Sigma;
}
//----------------------------------------------------------------------------
double DrawDoubleSidedCBShape(double AlphaL, double AlphaR, double NL, double NR)
{
   double LeftTailIntegral = exp(-0.5 * AlphaL * AlphaL) * NL / AlphaL / (NL - 1);
   double GaussianIntegral = sqrt(PI / 2) * (erf(AlphaR / sqrt(2)) + erf(AlphaL / sqrt(2)));
   double RightTailIntegral = exp(-0.5 * AlphaR * AlphaR) * NR / AlphaR / (NR - 1);
   double TotalIntegral = LeftTailIntegral + GaussianIntegral + RightTailIntegral;

   double RandomNumber = DrawRandom(TotalIntegral);
   
   if(RandomNumber < LeftTailIntegral)
   {
      RandomNumber = DrawRandom();
      return -(NL / AlphaL * pow(1 - RandomNumber, 1.0 / (1 - NL)) - NL / AlphaL + AlphaL);
   }
   else if(RandomNumber < LeftTailIntegral + GaussianIntegral)
   {
      RandomNumber = DrawGaussianBoxMuller();
      while(RandomNumber < -AlphaL || RandomNumber > AlphaR)
         RandomNumber = DrawGaussianBoxMuller();
      return RandomNumber;
   }
   else
   {
      RandomNumber = DrawRandom();
      return NR / AlphaR * pow(1 - RandomNumber, 1.0 / (1 - NR)) - NR / AlphaR + AlphaR;
   }

   return 0;
}
//----------------------------------------------------------------------------
#endif

