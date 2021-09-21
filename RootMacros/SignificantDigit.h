#include <iostream>

int FindFirstSignificantDigit(double X);
int CountDigit(double X, int D);
int CountDigitBelowPoint(double X, int D);
int CountDigitBelowPoint(int D);
double RoundToDigit(double X, int D);

int FindFirstSignificantDigit(double X)
{
   if(X < 0)
      X = -X;

   if(X == 0)
      return -999;
   if(X < 10 && X >= 1)
      return 0;

   if(X >= 1)
   {
      int Count = 0;
      while(X >= 10)
      {
         X = X / 10;
         Count = Count + 1;
      }

      return Count;
   }

   int Count = 0;
   while(X < 1)
   {
      X = X * 10;
      Count = Count - 1;
   }

   return Count;
}

int CountDigit(double X, int D)
{
   return FindFirstSignificantDigit(X) - D + 1;
}

int CountDigitBelowPoint(double X, int D)
{
   return CountDigitBelowPoint(D);
}

int CountDigitBelowPoint(int D)
{
   if(D >= 0)
      return 0;
   return -D;
}

double RoundToDigit(double X, int D)
{
   bool Negative = false;
   if(X < 0)
   {
      Negative = true;
      X = -X;
   }

   if(D >= 0)
   {
      for(int i = 0; i < D; i++)
         X = X / 10;

      int IntX = X;
      if(X - IntX >= 0.5)
         X = IntX + 1;
      else
         X = IntX;
      
      for(int i = 0; i < D; i++)
         X = X * 10;
   }
   else
   {
      for(int i = 0; i > D; i--)
         X = X * 10;

      int IntX = X;
      if(X - IntX >= 0.5)
         X = IntX + 1;
      else
         X = IntX;

      for(int i = 0; i > D; i--)
         X = X / 10;
   }

   if(Negative == true)
      X = -X;
   return X;
}




