#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define SIZE 8

vector<int> ListPrimes()
{
   vector<int> Result;
   Result.push_back(2);
   Result.push_back(3);
   Result.push_back(5);
   Result.push_back(7);
   Result.push_back(11);
   Result.push_back(13);

   for(int i = 17; i < 1000000; i = i + 2)
   {
      bool Good = true;
      for(int j = 0; j < (int)Result.size(); j++)
      {
         if(i % Result[j] == 0)
            Good = false;
         if(Result[j] * Result[j] > i)
            break;
      }

      if(Good == true)
         Result.push_back(i);
   }

   return Result;
}

void LongestCommonSequence(vector<int> A, vector<int> B, int **C)
{
   if(A[0] == B[0])
      C[0][0] = 1;
   for(int i = 1; i < SIZE; i++)
      if(A[i] == B[0] || C[i-1][0] == 1)
         C[i][0] = 1;
   for(int j = 1; j < SIZE; j++)
      if(A[0] == B[j] || C[0][j-1] == 1)
         C[0][j] = 1;

   for(int i = 1; i < SIZE; i++)
   {
      for(int j = 1; j < SIZE; j++)
      {
         if(A[i] == B[j])
            C[i][j] = C[i-1][j-1] + 1;
         else
            C[i][j] = max(C[i][j-1], C[i-1][j]);
      }
   }

   /*
   for(int y = 0; y < 50; y++)
   {
      for(int x = 0; x < 50; x++)
         cout << C[x][y] << " ";
      cout << endl;
   }
   cout << endl;

   for(int i = 0; i < 50; i++)
      cout << A[i] << " ";
   cout << endl;
   for(int i = 0; i < 50; i++)
      cout << B[i] << " ";
   cout << endl;
   */
}

pair<pair<int, int>, string> PairIt(int i, int j, string k)
{
   return pair<pair<int, int>, string>(pair<int, int>(i, j), k);
}

string SmallestSuperSequence(vector<int> &A, vector<int> &B, int **C)
{
   map<int, vector<pair<int, int> > > Diagonals;

   if(C[0][0] == 1)
      Diagonals[C[0][0]].push_back(pair<int, int>(0, 0));
   for(int i = 1; i < SIZE; i++)
      if(C[i][0] > C[i-1][0])
         Diagonals[C[i][0]].push_back(pair<int, int>(i, 0));
   for(int j = 1; j < SIZE; j++)
      if(C[0][j] > C[0][j])
         Diagonals[C[0][j]].push_back(pair<int, int>(0, j));
   for(int i = 1; i < SIZE; i++)
      for(int j = 1; j < SIZE; j++)
         if(C[i][j] > C[i-1][j-1] && C[i][j] > C[i-1][j] && C[i][j] > C[i][j-1])
            Diagonals[C[i][j]].push_back(pair<int, int>(i, j));
   Diagonals[C[SIZE-1][SIZE-1]+1].push_back(pair<int, int>(SIZE, SIZE));

   vector<pair<pair<int, int>, string> > CurrentBests;
   CurrentBests.push_back(PairIt(-1, -1, ""));

   for(map<int, vector<pair<int, int> > >::iterator iter = Diagonals.begin(); iter != Diagonals.end(); iter++)
   {
      vector<pair<pair<int, int>, string> > TempBests;
      
      int Count = iter->second.size();
      for(int i = 0; i < Count; i++)
      {
         // cout << "D " << iter->first << " " << iter->second[i].first << " " << iter->second[i].second << endl;

         vector<string> SubResults;

         for(int j = 0; j < (int)CurrentBests.size(); j++)
         {
            int AL = CurrentBests[j].first.first + 1;
            int BL = CurrentBests[j].first.second + 1;
            int AR = iter->second[i].first;
            int BR = iter->second[i].second;

            if(AL > AR || BL > BR)
               continue;

            string Joined = "";
            while(AL < AR || BL < BR)
            {
               if(AL == AR && BL < BR)
               {
                  Joined += char('0' + B[BL]);
                  BL++;
               }
               else if(BL == BR && AL < AR)
               {
                  Joined += char('0' + A[AL]);
                  AL++;
               }
               else if(A[AL] < B[BL])
               {
                  Joined += char('0' + A[AL]);
                  AL++;
               }
               else if(A[AL] > B[BL])
               {
                  Joined += char('0' + B[BL]);
                  BL++;
               }
               else if(AL == AR && BL == BR)
                  continue;
               else
                  cerr << "HMM? " << AL << " " << AR << " " << BL << " " << BR << endl;
            }
            if(AR < SIZE)
               Joined += char('0' + A[AR]);

            SubResults.push_back(CurrentBests[j].second + Joined);
         }

         if(SubResults.size() > 0)
         {
            sort(SubResults.begin(), SubResults.end());
            TempBests.push_back(PairIt(iter->second[i].first, iter->second[i].second, SubResults[0]));
         }
      }

      CurrentBests = TempBests;
   }

   cout << "Number of bests = " << CurrentBests.size() << endl;

   return CurrentBests[0].second;
}

int main()
{
   srand(time(NULL));

   int S = SIZE;

   vector<int> Primes = ListPrimes();
   vector<int> Composites;

   int PrimeIndex = 0;
   for(int i = 4; i < S * 2; i++)
   {
      while(i > Primes[PrimeIndex])
         PrimeIndex = PrimeIndex + 1;
      if(i < Primes[PrimeIndex])
         Composites.push_back(i);
   }

   Primes.erase(Primes.begin() + S, Primes.end());
   Composites.erase(Composites.begin() + S, Composites.end());

   for(int i = 0; i < S; i++)
   {
      Primes[i] = Primes[i] % 9;
      Composites[i] = Composites[i] % 9;

      if(Primes[i] == 0)
         Primes[i] = 9;
      if(Composites[i] == 0)
         Composites[i] = 9;
   }

   int **C = new int *[SIZE];
   for(int i = 0; i < SIZE; i++)
      C[i] = new int[SIZE];
   for(int i = 0; i < SIZE; i++)
      for(int j = 0; j < SIZE; j++)
         C[i][j] = 0;

   for(int i = 0; i < SIZE; i++)
      cout << Primes[i];
   cout << endl;
   for(int i = 0; i < SIZE; i++)
      cout << Composites[i];
   cout << endl;

   LongestCommonSequence(Primes, Composites, C);
   string Result = SmallestSuperSequence(Primes, Composites, C);

   cout << Result << endl;

   for(int i = 0; i < SIZE; i++)
      delete[] C[i];
   delete[] C;

   return 0;
}






