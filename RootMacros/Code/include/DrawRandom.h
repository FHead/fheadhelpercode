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
#endif
