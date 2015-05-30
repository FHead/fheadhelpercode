#include <deque>
#include <iostream>
using namespace std;

int main()
{
   int CollatzSteps[1000000] = {0};
   CollatzSteps[1] = 1;

   deque<int> ToBeProcessed;
   ToBeProcessed.push_back(1);

   while(ToBeProcessed.size() > 0)
   {
      int N = ToBeProcessed[0];
      ToBeProcessed.pop_front();

      if(N * 2 < 1000000)
      {
         if(CollatzSteps[N*2] == 0)
         {
            CollatzSteps[N*2] = CollatzSteps[N] + 1;
            ToBeProcessed.push_back(N * 2);
         }
      }
      if(N - 1 % 3 == 0 && N > 1 && (N - 1) / 3 % 2 == 1)
      {
         if(CollatzSteps[(N-1)/3] == 0)
         {
            CollatzSteps[(N-1)/3] = CollatzSteps[N] + 1;
            ToBeProcessed.push_back((N - 1) / 3);
         }
      }
   }

   cout << "Done blood fill" << endl;

   for(int i = 1; i < 1000000; i++)
   {
      if(CollatzSteps[i] == 0)
      {
         long long N = i;
         int StepCount = 0;

         bool Good = false;
         while(Good == false)
         {
            if(N % 2 == 0)
               N = N / 2;
            else
               N = 3 * N + 1;
            StepCount = StepCount + 1;

            if(N < 1000000 && CollatzSteps[N] != 0)
            {
               Good = true;
               CollatzSteps[i] = CollatzSteps[N] + StepCount;
            }
         }
      }
   }

   int MaxIndex = 0;
   for(int i = 1; i < 1000000; i++)
   {
      if(CollatzSteps[i] > CollatzSteps[MaxIndex])
         MaxIndex = i;
   }

   cout << MaxIndex << endl;

   return 0;
}




