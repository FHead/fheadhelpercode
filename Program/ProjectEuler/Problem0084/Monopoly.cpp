#include <algorithm>
#include <iostream>
#include <deque>
#include <map>
using namespace std;

int main()
{
   int DiceFace = 4;

   double Chance[40] = {0};

   int Location = 0;
   int DoubleCounter = 0;

   deque<int> CCCard, CHCard;
   for(int i = 1; i <= 16; i++)
   {
      CCCard.push_back(i);
      CHCard.push_back(i);
   }
   random_shuffle(CCCard.begin(), CCCard.end());
   random_shuffle(CHCard.begin(), CHCard.end());

   long long Total = 100000000LL;
   for(long long i = 0; i < Total; i++)
   {
      if(i % 10000 == 1)
         cout << i << " " << Chance[10] / i << " " << Chance[24] / i << " " << Chance[0] / i << endl;

      if(i % 10000 == 0)
      {
         random_shuffle(CCCard.begin(), CCCard.end());
         random_shuffle(CHCard.begin(), CHCard.end());
      }

      int Dice1 = rand() % DiceFace + 1;
      int Dice2 = rand() % DiceFace + 1;

      Location = (Location + Dice1 + Dice2) % 40;
      
      if(Dice1 == Dice2)
         DoubleCounter = DoubleCounter + 1;
      else
         DoubleCounter = 0;
      if(DoubleCounter >= 3)
      {
         DoubleCounter = 0;
         Location = 10;
      }

      bool Change = true;
      while(Change == true)
      {
         int Original = Location;
         Change = false;

         if(Location == 2 || Location == 17 || Location == 33)
         {
            int Card = CCCard[0];
            CCCard.pop_front();
            CCCard.push_back(Card);
            if(Card == 1)
               Location = 0;
            if(Card == 2)
               Location = 10;
         }
         if(Location == 7 || Location == 22 || Location == 36)
         {
            int Card = CHCard[0];
            CHCard.pop_front();
            CHCard.push_back(Card);
            if(Card == 1)
               Location = 0;
            if(Card == 2)
               Location = 10;
            if(Card == 3)
               Location = 11;
            if(Card == 4)
               Location = 24;
            if(Card == 5)
               Location = 39;
            if(Card == 6)
               Location = 5;
            if(Card == 7 || Card == 8)
            {
               if(Location == 7)    Location = 15;
               if(Location == 22)   Location = 25;
               if(Location == 36)   Location = 5;
            }
            if(Card == 9)
            {
               if(Location == 7)    Location = 12;
               if(Location == 22)   Location = 28;
               if(Location == 36)   Location = 12;
            }
            if(Card == 10)
               Location = (Location + 37) % 40;
         }
         if(Location == 30)
            Location = 10;

         if(Location != Original)
            Change = true;
      }

      Chance[Location] = Chance[Location] + 1;
   }

   map<double, int, greater<double> > Sorter;
   for(int i = 0; i < 40; i++)
      Sorter.insert(pair<double, int>(Chance[i] + i * 0.01, i));

   map<double, int>::iterator iter = Sorter.begin();
   cout << iter->second << " " << Chance[iter->second] / Total << endl;
   iter++;
   cout << iter->second << " " << Chance[iter->second] / Total << endl;
   iter++;
   cout << iter->second << " " << Chance[iter->second] / Total << endl;
   iter++;

   return 0;
}






