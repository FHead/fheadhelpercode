#include <iostream>
#include <vector>
#include <map>
using namespace std;

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

void Backtrack(vector<int> A, vector<int> B, int **C, int i, int j, vector<pair<int, int> > &Result)
{
   if(i < 0 || j < 0)
      return;
   if(C[i][j] == 0)
      return;

   if(A[i] == B[j])
   {
      Backtrack(A, B, C, i - 1, j - 1, Result);
      Result.push_back(pair<int, int>(i, j));
      return;
   }

   if(C[i][j-1] < C[i-1][j])
      Backtrack(A, B, C, i - 1, j, Result);
   else if(C[i][j-1] > C[i-1][j])
      Backtrack(A, B, C, i, j - 1, Result);
   else
   {
      Backtrack(A, B, C, i, j - 1, Result);
      /*
      cout << "! " << i << " " << j << " " << Result.size() << endl;
      if(rand() % 2 == 0)
         Backtrack(A, B, C, i - 1, j, Result);
      else
         Backtrack(A, B, C, i, j - 1, Result);
      */
   }
}

void Backtrack2(vector<int> A, vector<int> B, int **C, vector<pair<int, int> > &Result)
{
   int i = 9999, j = 9999;

   while(Result.size() < C[9999][9999])
   {
      if(i < 0 || j < 0)
         break;

      if(A[i] == B[j])
      {
         Result.push_back(pair<int, int>(i, j));
         i--;
         j--;
      }
      else if(i == 0)
         j--;
      else if(j == 0)
         i--;
      else if(C[i][j-1] < C[i-1][j])
         i--;
      else if(C[i][j-1] > C[i-1][j])
         j--;
      else
      {
         if(rand() % 2 == 0)
            i--;
         else
            j--;
      }
   }

   reverse(Result.begin(), Result.end());
}

vector<pair<int, int> > LongestCommonSequence(vector<int> A, vector<int> B, int **C)
{
   for(int i = 1; i < 10000; i++)
   {
      for(int j = 1; j < 10000; j++)
      {
         if(A[i] == B[j])
            C[i][j] = C[i-1][j-1] + 1;
         else
            C[i][j] = max(C[i][j-1], C[i-1][j]);
      }
   }

   // cout << "LCS size = " << C[9999][9999] << endl;

   vector<pair<int, int> > Result;
   Backtrack2(A, B, C, Result);

   return Result;
}

pair<pair<int, int>, string> PairIt(int i, int j, string k)
{
   return pair<pair<int, int>, string>(pair<int, int>(i, j), k);
}

vector<int> SmallestSuperSequence(vector<int> &A, vector<int> &B, int **C)
{
   map<int, vector<pair<int, int> > > Diagonals;

   if(C[0][0] == 1)
      Diagonals[C[0][0]].push_back(pair<int, int>(0, 0));
   for(int i = 1; i < 9999; i++)
      if(C[i][0] > C[i-1][0])
         Diagonals[C[i][0]].push_back(pair<int, int>(i, 0));
   for(int j = 1; j < 9999; j++)
      if(C[0][j] > C[0][j])
         Diagonals[C[0][j]].push_back(pair<int, int>(0, j));
   for(int i = 1; i < 9999; i++)
      if(C[i][0] > C[i-1][0])
         Diagonals[C[i][0]].push_back(pair<int, int>(i, 0));
   for(int i = 1; i < 9999; i++)
      for(int j = 1; j < 9999; j++)
         if(C[i][j] > C[i-1][j-1] && C[i][j] > C[i-1][j] && C[i][j] > C[i][j-1])
            Diagonals[C[i][j]].push_back(pair<int, int>(i, j));

   vector<pair<pair<int, int>, string> > CurrentBests;
   CurrentBests.push_back(PairIt(-1, -1, ""));

   for(map<int, vector<pair<int, int> > >::iterator iter = Diagonals.begin(); iter != Diagonals.end(); iter++)
   {
      int Count = iter->second.size();
      for(int i = 0; i < Count; i++)
      {
         for(int j = 0; j < (int)CurrentBests.size(); j++)
         {
            int AL = CurrentBests[j].first.first + 1;
            int BL = CurrentBests[j].first.second + 1;
            int AR = iter->second[i].first;
            int BR = iter->second[i].second;

            if(AR > 0 && BR > 0)
            {
               cout << "C " << C[AR][BR] << " " << C[AR-1][BR] << " " << C[AR][BR-1] << " " << C[AR-1][BR-1] << endl;
               for(int j = AL; j <= AR; j++)
                  cout << " " << A[j];
               cout << endl;
               for(int j = BL; j <= BR; j++)
                  cout << " " << B[j];
               cout << endl;
            }

            if(AL > AR || BL > BR)
               continue;

            string Joined = "";
            while(AL < AR || BL < BR)
            {
               cerr << "...." << AL << " " << AR << " " << BL << " " << BR
                  << " " << A[AL] << " " << A[AR] << " " << B[BL] << " " << B[BR] << endl;
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
            Joined += char('0' + A[AR]);
         }
      }
   }

   return vector<int>();
}

int main()
{
   srand(time(NULL));

   int S = 10000;

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

   // Let's try greedy approach
   // int A = 0, B = 0;
   // int DigitCount = 0;
   // while(A < 10000 || B < 10000)
   // {
   //    if(A == 10000)
   //    {
   //       cout << Composites[B];
   //       B++;
   //    }
   //    else if(B == 10000)
   //    {
   //       cout << Primes[A];
   //       A++;
   //    }
   //    else if(Primes[A] == Composites[B])
   //    {
   //       cout << Primes[A];
   //       A++;
   //       B++;
   //    }
   //    else if(Primes[A] < Composites[B])
   //    {
   //       cout << Primes[A];
   //       A++;
   //    }
   //    else
   //    {
   //       cout << Composites[B];
   //       B++;
   //    }
   // 
   //    DigitCount++;
   // }
   // cout << endl;
   // cout << DigitCount << endl;
   // 
   // return 0;

   int **C = new int *[10000];
   for(int i = 0; i < 10000; i++)
      C[i] = new int[10000];
   for(int i = 0; i < 10000; i++)
      for(int j = 0; j < 10000; j++)
         C[i][j] = 0;

   vector<pair<int, int> > LCS = LongestCommonSequence(Primes, Composites, C);
   vector<int> Result = SmallestSuperSequence(Primes, Composites, C);

   // cout << "LCS size = " << LCS.size() << endl;
   // cout << "LCS[last] = (" << LCS[LCS.size()-1].first << ", " << LCS[LCS.size()-1].second << ")" << endl;

   // LCS.insert(LCS.begin(), pair<int, int>(-1, -1));

   // vector<int> Final;
   // for(int i = 1; i < (int)LCS.size(); i++)
   // {
   //    int A = LCS[i-1].first + 1;
   //    int B = LCS[i-1].second + 1;

   //    int AEnd = LCS[i].first;
   //    int BEnd = LCS[i].second;

   //    while(A < AEnd || B < BEnd)
   //    {
   //       if(A == AEnd && B < BEnd)
   //       {
   //          Final.push_back(Composites[B]);
   //          B++;
   //       }
   //       else if(A < AEnd && B == BEnd)
   //       {
   //          Final.push_back(Primes[A]);
   //          A++;
   //       }
   //       else
   //       {
   //          if(Primes[A] < Composites[B])
   //          {
   //             Final.push_back(Primes[A]);
   //             A++;
   //          }
   //          else if(Primes[A] > Composites[B])
   //          {
   //             Final.push_back(Composites[B]);
   //             B++;
   //          }
   //          else
   //             cerr << "ERROR" << endl;
   //       }
   //    }

   //    Final.push_back(Primes[AEnd]);
   // }

   // if(LCS[LCS.size()-1].second == 9999)
   //    Final.insert(Final.end(), Primes.begin() + LCS[LCS.size()-1].first + 1, Primes.begin() + 9999 + 1);
   // else if(LCS[LCS.size()-1].second == 9999)
   //    Final.insert(Final.end(), Composites.begin() + LCS[LCS.size()-1].second + 1, Composites.begin() + 9999 + 1);
   // else
   //    cerr << "MEOW!" << endl;

   // for(int i = 0; i < (int)Final.size(); i++)
   //    cout << Final[i];
   // cout << endl;

   for(int i = 0; i < 10000; i++)
      delete[] C[i];
   delete[] C;

   return 0;
}






