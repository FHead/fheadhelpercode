#ifndef TauHelperFunctions_6564_AJSDKGIRIKANSVCGKISNCGIKNHKZSG
#define TauHelperFunctions_6564_AJSDKGIRIKANSVCGKISNCGIKNHKZSG

#include <vector>
#include <cmath>
using namespace std;

#include "GenparticleTree.h"

// Categories:
//    -1. not final tau (goes into tau gamma)
//    1. mu nu nu
//    2. e nu nu
//    3. nu pi-
//    4. nu pi0 pi-
//    5. nu pi0 pi0 pi-
//    6. nu pi+ pi- pi-
//    7. nu pi+ pi- pi- pi0
//    8. otherwise

#define PI 3.14159265358979323846264338327950288479716939937510

int FindCategory(GenParticleTree &Tree, int index);
double GetMass(const double P[4]);
double GetMass2(const double P[4]);
double GetP(const double P[4]);
double GetPT(const double P[4]);
double GetEta(const double P[4]);
double GetRapidity(const double P[4]);
double GetY(const double P[4]);
double GetPhi(const double P[4]);
double GetAngle(const double P1[4], const double P2[4]);
double GetDR(const double P1[4], const double P2[4]);
double GetDPhi(const double P1[4], const double P2[4]);
double GetMT(const double P1[4], const double P2[4]);
double GetMinRadius(const double P1[4], const double P2[4], const double P3[4]);   // in eta-phi space
double GetMinRadius(const double X1, const double Y1, const double X2, const double Y2, const double X3, const double Y3);
double GetMR(const double P1[4], const double P2[4]);
double GetMRT(const double P1[4], const double P2[4]);
double GetR(const double P1[4], const double P2[4]);
double GetBeta(const double P[4]);
double GetGamma(const double P[4]);

int FindCategory(GenParticleTree &Tree, int index)
{
   vector<int> Daughters = Tree[index].Daughters;

   int PiZeroCount = 0;
   int PiPlusCount = 0;
   int PiMinusCount = 0;

   for(int i = 0; i < (int)Daughters.size(); i++)
   {
      if(Tree[Daughters[i]].PDGID == 13 || Tree[Daughters[i]].PDGID == -13)   // detect muon
         return 1;
      if(Tree[Daughters[i]].PDGID == 11 || Tree[Daughters[i]].PDGID == -11)   // detect electron
         return 2;
      if(Tree[Daughters[i]].PDGID == 15 || Tree[Daughters[i]].PDGID == -15)   // detect tau
         return -1;

      if(Tree[Daughters[i]].PDGID == 111)   // pi0
         PiZeroCount = PiZeroCount + 1;
      if(Tree[Daughters[i]].PDGID == 211)   // pi+
         PiPlusCount = PiPlusCount + 1;
      if(Tree[Daughters[i]].PDGID == -211)   // pi-
         PiMinusCount = PiMinusCount + 1;

      // rho, omega => look at their decays
      if(Tree[Daughters[i]].PDGID == 223 || Tree[Daughters[i]].PDGID == 213
         || Tree[Daughters[i]].PDGID == 113 || Tree[Daughters[i]].PDGID == -213)
      {
         vector<int> DaughterList = Tree[Daughters[i]].Daughters;

         for(int j = 0; j < (int)DaughterList.size(); j++)
         {
            if(Tree[DaughterList[j]].PDGID == 111)   // pi0
               PiZeroCount = PiZeroCount + 1;
            if(Tree[DaughterList[j]].PDGID == 211)   // pi+
               PiPlusCount = PiPlusCount + 1;
            if(Tree[DaughterList[j]].PDGID == -211)   // pi-
               PiMinusCount = PiMinusCount + 1;
         }
      }
   }

   if(PiMinusCount == 1 && PiZeroCount == 0 && PiPlusCount == 0)
      return 3;
   if(PiMinusCount == 1 && PiZeroCount == 1 && PiPlusCount == 0)
      return 4;
   if(PiMinusCount == 1 && PiZeroCount == 2 && PiPlusCount == 0)
      return 5;
   if(PiMinusCount == 2 && PiZeroCount == 0 && PiPlusCount == 1)
      return 6;
   if(PiMinusCount == 2 && PiZeroCount == 1 && PiPlusCount == 1)
      return 7;
   
   if(PiMinusCount == 0 && PiZeroCount == 0 && PiPlusCount == 1)
      return 3;
   if(PiMinusCount == 0 && PiZeroCount == 1 && PiPlusCount == 1)
      return 4;
   if(PiMinusCount == 0 && PiZeroCount == 2 && PiPlusCount == 1)
      return 5;
   if(PiMinusCount == 1 && PiZeroCount == 0 && PiPlusCount == 2)
      return 6;
   if(PiMinusCount == 1 && PiZeroCount == 1 && PiPlusCount == 2)
      return 7;

   return 8;
}

double GetMass(const double P[4])
{
   return sqrt(P[0] * P[0] - P[1] * P[1] - P[2] * P[2] - P[3] * P[3]);
}

double GetMass2(const double P[4])
{
   return (P[0] * P[0] - P[1] * P[1] - P[2] * P[2] - P[3] * P[3]);
}

double GetP(const double P[4])
{
   return sqrt(P[1] * P[1] + P[2] * P[2] + P[3] * P[3]);
}

double GetPT(const double P[4])
{
   return sqrt(P[1] * P[1] + P[2] * P[2]);
}

double GetEta(const double P[4])
{
   double Momentum = GetP(P);

   return 0.5 * log((Momentum - P[3]) / (Momentum + P[3]));
}

double GetRapidity(const double P[4])
{
   return 0.5 * log((P[0] - P[3]) / (P[0] + P[3]));
}

double GetY(const double P[4])
{
   return GetRapidity(P);
}

double GetPhi(const double P[4])
{
   double PT = GetPT(P);

   double Angle = acos(P[1] / PT);
   if(P[2] < 0)
      Angle = -Angle;

   return Angle;
}

double GetAngle(const double P1[4], const double P2[4])
{
   return acos((P1[1] * P2[1] + P1[2] * P2[2] + P1[3] * P2[3]) / GetP(P1) / GetP(P2));
}

double GetDR(const double P1[4], const double P2[4])
{
   double DEta = GetEta(P1) - GetEta(P2);
   double DPhi = GetDPhi(P1, P2);

   return sqrt(DPhi * DPhi + DEta * DEta);
}

double GetDPhi(const double P1[4], const double P2[4])
{
   double DPhi = GetPhi(P1) - GetPhi(P2);

   if(DPhi > PI)
      DPhi = 2 * PI - DPhi;
   if(DPhi < -PI)
      DPhi = DPhi + 2 * PI;

   return DPhi;
}

double GetMT(const double P1[4], const double P2[4])
{
   double PT1 = GetPT(P1);
   double PT2 = GetPT(P2);

   // cout << "P1 = " << P1[0] << " " << P1[1] << " " << P1[2] << " " << P1[3] << endl;
   // cout << "P2 = " << P2[0] << " " << P2[1] << " " << P2[2] << " " << P2[3] << endl;
   // cout << "MT = " << 2 * (PT1 * PT2 - P1[1] * P2[1] - P1[2] * P2[2]) << endl;

   return sqrt(2 * (PT1 * PT2 - P1[1] * P2[1] - P1[2] * P2[2]));
}

double GetMinRadius(const double P1[4], const double P2[4], const double P3[4])   // in eta-phi space
{
   double Eta1 = GetEta(P1);
   double Phi1 = GetPhi(P1);
   double Eta2 = GetEta(P2);
   double Phi2 = GetPhi(P2);
   double Eta3 = GetEta(P3);
   double Phi3 = GetPhi(P3);

   double BestResidual2 = 9999999;
   double Best1 = 0;
   double Best2 = 0;
   double Best3 = 0;
   for(int i1 = 0; i1 <= 1; i1++)
   {
      for(int i2 = 0; i2 <= 1; i2++)
      {
         for(int i3 = 0; i3 <= 1; i3++)
         {
            double AveragePhi = (Phi1 + Phi2 + Phi3 + (i1 + i2 + i3) * 2 * PI) / 3;

            double Residual2 = (AveragePhi - Phi1 - i1 * 2 * PI) * (AveragePhi - Phi1 - i1 * 2 * PI)
               + (AveragePhi - Phi2 - i2 * 2 * PI) * (AveragePhi - Phi2 - i2 * 2 * PI)
               + (AveragePhi - Phi3 - i3 * 2 * PI) * (AveragePhi - Phi3 - i3 * 2 * PI);

            if(Residual2 < BestResidual2)
            {
               Best1 = i1;
               Best2 = i2;
               Best3 = i3;

               BestResidual2 = Residual2;
            }
         }
      }
   }

   return GetMinRadius(Eta1, Phi1 + Best1 * 2 * PI, Eta2, Phi2 + Best2 * 2 * PI, Eta3, Phi3 + Best3 * 2 * PI);
}

double GetMinRadius(const double X1, const double Y1, const double X2, const double Y2, const double X3, const double Y3)
{
   // compare two radii:
   //    - common circle radius
   //    - maximum of edge length (divided by two)
   // return the smaller of the two

   // calculate common circle radius
   double C1X0 = 2 * (X1 - X2);
   double C1Y0 = 2 * (Y1 - Y2);
   double C1 = X1 * X1 + Y1 * Y1 - X2 * X2 - Y2 * Y2;
   
   double C2X0 = 2 * (X1 - X3);
   double C2Y0 = 2 * (Y1 - Y3);
   double C2 = X1 * X1 + Y1 * Y1 - X3 * X3 - Y3 * Y3;

   double Distance2 = 99999999;

   if(fabs(C1X0 * C2Y0 - C2X0 * C1Y0) > 1e-8)   // otherwise three points too close to a straight line
   {
      double M = C1X0 * C2Y0 - C2X0 * C1Y0;
      double MX = C1 * C2Y0 - C2 * C1Y0;
      double MY = C1X0 * C2 - C2X0 * C1;

      double X0 = MX / M;
      double Y0 = MY / M;

      Distance2 = (X1 - X0) * (X1 - X0) + (Y1 - Y0) * (Y1 - Y0);
   }

   // calculate max of edge
   double MaxEdge2 = 0;
   if(MaxEdge2 < (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2))
      MaxEdge2 = (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2);
   if(MaxEdge2 < (X2 - X3) * (X2 - X3) + (Y2 - Y3) * (Y2 - Y3))
      MaxEdge2 = (X2 - X3) * (X2 - X3) + (Y2 - Y3) * (Y2 - Y3);
   if(MaxEdge2 < (X3 - X1) * (X3 - X1) + (Y3 - Y1) * (Y3 - Y1))
      MaxEdge2 = (X3 - X1) * (X3 - X1) + (Y3 - Y1) * (Y3 - Y1);
   MaxEdge2 = MaxEdge2 / 4;

   // minimum of the two
   return sqrt(min(MaxEdge2, Distance2));
}

double GetMR(const double P1[4], const double P2[4])
{
   double Temp1 = P1[0] * P2[3] - P1[3] * P2[0];
   double Temp2 = P1[3] - P2[3];
   double Temp3 = P1[0] - P2[0];
   return 2 * sqrt(Temp1 * Temp1 / (Temp2 * Temp2 - Temp3 * Temp3));
}

double GetMRT(const double P1[4], const double P2[4], const double ME[4])
{
   double Temp1 = GetPT(ME) * (GetPT(P1) + GetPT(P2));
   double Temp2 = ME[1] * (P1[1] + P2[1]) + ME[2] * (P1[2] + P2[2]);
   return sqrt((Temp1 - Temp2) / 2);
}

double GetR(const double P1[4], const double P2[4], const double ME[4])
{
   return GetMRT(P1, P2, ME) / GetMR(P1, P2);
}

double GetBeta(const double P[4])
{
   double Gamma = GetGamma(P);
   return sqrt(1 - 1 / (Gamma * Gamma));
}

double GetGamma(const double P[4])
{
   return P[0] / GetMass(P);
}

#endif



