#include <iostream>
#include <cmath>
using namespace std;

class V2
{
public:
   double x0, y0;
public:
   V2(double x = 0, double y = 0) : x0(x), y0(y) {}
   ~V2() {}
   V2 operator +(const V2 &other) const {return V2(x0 + other.x0, y0 + other.y0);}
   V2 operator -(const V2 &other) const {return V2(x0 - other.x0, y0 - other.y0);}
   double operator *(const V2 &other) const {return x0 * other.x0 + y0 * other.y0;}
   V2 operator *(const double C) const {return V2(x0 * C, y0 * C);}
   V2 operator /(const double C) const {return V2(x0 / C, y0 / C);}
   V2 Rotate90() const {return V2(-y0, x0);}
   V2 Rotate180() const {return V2(-x0, -y0);}
   V2 Rotate360() const {return V2(y0, -x0);}
   double Size() const {return sqrt(*this * *this);}
   double Size2() const {return (*this * *this);}
   V2 Norm() const {return *this / Size();}
   V2 Project(const V2 &target) const {return target * (*this * target) / (target * target);}
};

int main()
{
   V2 X0(0.0, 10.1);
   V2 X1(1.4, -9.6);
   V2 D = X1 - X0;

   int Count = 0;

   bool In = true;
   while(In == true)
   {
      Count = Count + 1;
      V2 Tangent(X1.y0, -4 * X1.x0);
      V2 DProjected = D.Project(Tangent);
      V2 ReflectedD = DProjected - (D - DProjected);

      double A = 4 * ReflectedD.x0 * ReflectedD.x0 + ReflectedD.y0 * ReflectedD.y0;
      double B = 8 * X1.x0 * ReflectedD.x0 + 2 * X1.y0 * ReflectedD.y0;
      double C = 4 * X1.x0 * X1.x0 + X1.y0 * X1.y0 - 100;

      double K = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);

      V2 X2 = X1 + ReflectedD * K;

      X0 = X1;
      X1 = X2;
      D = ReflectedD;

      if(X1.y0 > 0 && X1.x0 <= 0.01 && X1.x0 >= -0.01)
         In = false;
   }

   cout << Count << endl;

   return 0;
}




