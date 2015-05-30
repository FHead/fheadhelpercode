#include <iostream>
#include <vector>
using namespace std;

int main()
{
   vector<int> Primes;
   Primes.push_back(2);
   Primes.push_back(3);
   Primes.push_back(5);
   Primes.push_back(7);
   for(int i = 11; i < 100000; i++)
   {
      bool Good = true;
      for(int j = 0; j < (int)Primes.size(); j++)
         if(i % Primes[j] == 0)
            Good = false;
      if(Good == true)
         Primes.push_back(i);
   }

   int Fours = 0;

   for(long long i = 10; i < 10000000; i++)
   {
      int Count = 0;
      long long Temp = i;
      for(int j = 0; j < (int)Primes.size() && Temp > 1; j++)
      {
         if(Temp % Primes[j] == 0)
         {
            Count = Count + 1;
            while(Temp % Primes[j] == 0)
               Temp = Temp / Primes[j];
         }
      }

      if(Count == 4)
      {
         Fours = Fours + 1;
         if(Fours >= 2)
            cout << Fours << " " << i << endl;
         if(Fours == 4)
            break;
      }
      else
         Fours = 0;
            
      cout << i << " " << Count << " " << Fours << endl;
   }

   return 0;
}




