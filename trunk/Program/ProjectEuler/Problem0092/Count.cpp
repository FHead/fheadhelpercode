#include <iostream>
using namespace std;

int OneIteration(int Value);
bool WillStuckAt89(int Test);
int main();

int OneIteration(int Value)
{
   int Answer = 0;
   while(Value > 0)
   {
      Answer = Answer + (Value % 10) * (Value % 10);
      Value = Value / 10;
   }
   return Answer;
}

bool WillStuckAt89(int Test)
{
   static int Result[1000] = {0};   // -1 means no, +1 means yes, 0 is undetermined

   Result[1] = -1;
   Result[89] = 1;

   if(Test >= 1000)
      return WillStuckAt89(OneIteration(Test));

   // if(Test == 1)
   //    return false;
   // if(Test == 89)
   //    return true;

   if(Result[Test] == 1)
      return true;
   else if(Result[Test] == -1)
      return false;

   bool Answer = WillStuckAt89(OneIteration(Test));
   if(Answer == true)
      Result[Test] = 1;
   else
      Result[Test] = -1;

   return Answer;
}

int main()
{
   int Count = 0;
   for(int i = 2; i < 10000000; i++)
      if(WillStuckAt89(i) == true)
         Count = Count + 1;

   cout << Count << endl;

   return 0;
}






