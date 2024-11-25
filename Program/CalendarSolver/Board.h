#include <iostream>
#include <vector>

#define STATE_EMPTY -1
#define STATE_FORBIDDEN -2

#define SHAPESIZE 5
#define WIDTH 9
#define HEIGHT 6

class Shape;
class Board;
std::ostream &operator <<(std::ostream &out, Shape &S);
std::ostream &operator <<(std::ostream &out, Board &B);
Board Solve(Board Initial, std::vector<Shape> Shapes);

class Shape
{
public:
   int ID;
   vector<int> X;
   vector<int> Y;
   int RotatePeriod;
public:
   Shape()
   {
      ID = 0;
      X.resize(SHAPESIZE);
      Y.resize(SHAPESIZE);
      for(int i = 0; i < SHAPESIZE; i++)
      {
         X[i] = 0;
         Y[i] = 0;
      }
      RotatePeriod = 4;
   }
   Shape(int id, std::vector<int> x, std::vector<int> y, int p)
   {
      ID = id;

      X.resize(SHAPESIZE);
      Y.resize(SHAPESIZE);
      for(int i = 0; i < SHAPESIZE; i++)
      {
         X[i] = 0;
         Y[i] = 0;
      }

      for(int i = 0; i < SHAPESIZE && i < (int)x.size(); i++)
         X[i] = x[i];
      for(int i = 0; i < SHAPESIZE && i < (int)y.size(); i++)
         Y[i] = y[i];

      RotatePeriod = p;
   }
   Shape Rotate()
   {
      // Rotate counter-clockwise 90 degrees
      // The left-most one in the bottom row is always (0, 0)

      Shape NewShape(*this);

      for(int i = 0; i < SHAPESIZE; i++)
      {
         NewShape.X[i] = -Y[i];
         NewShape.Y[i] = X[i];
      }

      int XShift = 0, YShift = 0;
      for(int i = 0; i < SHAPESIZE; i++)
      {
         if(NewShape.Y[i] < YShift)
            YShift = NewShape.Y[i];
      }
      for(int i = 0; i < SHAPESIZE; i++)
      {
         if(NewShape.Y[i] == YShift && NewShape.X[i] < XShift)
            XShift = NewShape.X[i];
      }

      for(int i = 0; i < SHAPESIZE; i++)
      {
         NewShape.X[i] = NewShape.X[i] - XShift;
         NewShape.Y[i] = NewShape.Y[i] - YShift;
      }

      return NewShape;
   }
};

class Board
{
public:
   vector<vector<int>> State;
public:
   Board()
   {
      State.resize(WIDTH);
      for(int i = 0; i < WIDTH; i++)
         State[i].resize(HEIGHT);

      for(int i = 0; i < WIDTH; i++)
         for(int j = 0; j < HEIGHT; j++)
            State[i][j] = STATE_EMPTY;
      State[8][0] = STATE_FORBIDDEN;
   }
   bool Valid()
   {
      if(State[8][0] != STATE_FORBIDDEN)
         return false;

      int ForbiddenCount = 0;
      for(int i = 0; i < WIDTH; i++)
      {
         for(int j = 0; j < HEIGHT; j++)
         {
            if(State[i][j] == STATE_FORBIDDEN)
               ForbiddenCount = ForbiddenCount + 1;
         }
      }
      if(ForbiddenCount != 4)
         return false;

      return true;
   }
   bool Good()   // check if the board is still possible
   {
      // TODO
      return true;
   }
   bool IsSolution()
   {
      for(int i = 0; i < WIDTH; i++)
      {
         for(int j = 0; j < HEIGHT; j++)
         {
            if(State[i][j] == STATE_EMPTY)
               return false;
         }
      }
      return true;
   }
   void FindNext(int &XNext, int &YNext)
   {
      bool Found = false;
      XNext = -1, YNext = -1;
      for(int j = 0; j < HEIGHT && Found == false; j++)
      {
         for(int i = 0; i < WIDTH && Found == false; i++)
         {
            if(State[i][j] == STATE_EMPTY)
            {
               XNext = i;
               YNext = j;
               Found = true;
            }
         }
      }
   }
   bool CanPlace(Shape S)
   {
      int XNext = -1, YNext = -1;
      FindNext(XNext, YNext);
      if(XNext < 0 || YNext < 0)
         return false;

      for(int i = 0; i < SHAPESIZE; i++)
      {
         if(XNext + S.X[i] < 0 || XNext + S.X[i] >= WIDTH)   // out of bound in x
            return false;
         if(YNext + S.Y[i] < 0 || YNext + S.Y[i] >= HEIGHT)   // out of bound in Y
            return false;
         if(State[XNext+S.X[i]][YNext+S.Y[i]] != STATE_EMPTY)   // conflict!
            return false;
      }
      
      return true;
   }
   Board PlaceNext(Shape S)
   {
      Board NewBoard = *this;
   
      int XNext = -1, YNext = -1;
      FindNext(XNext, YNext);
      if(XNext < 0 || YNext < 0)
         return NewBoard;

      for(int i = 0; i < SHAPESIZE; i++)
      {
         if(XNext + S.X[i] < 0 || XNext + S.X[i] >= WIDTH)   // out of bound in x
            return NewBoard;
         if(YNext + S.Y[i] < 0 || YNext + S.Y[i] >= HEIGHT)   // out of bound in Y
            return NewBoard;
         if(State[XNext+S.X[i]][YNext+S.Y[i]] != STATE_EMPTY)   // conflict!
            return NewBoard;
      }

      for(int i = 0; i < SHAPESIZE; i++)
         NewBoard.State[XNext+S.X[i]][YNext+S.Y[i]] = S.ID;

      return NewBoard;
   }
};

std::ostream &operator <<(std::ostream &out, Shape &S)
{
   for(int j = 5 - 1; j >= -4; j--)
   {
      for(int i = -4; i < 5; i++)
      {
         bool Found = false;
         for(int k = 0; k < 5; k++)
         {
            if(S.X[k] == i && S.Y[k] == j)
               Found = true;
         }

         if(Found == true)
            out << "A";
         else
         {
            if(i == 0)
               out << "|";
            else if(j == 0)
               out << "-";
            else
               out << ".";
         }
      }
      out << endl;
   }

   return out;
}

std::ostream &operator <<(std::ostream &out, Board &B)
{
   out << "o";
   for(int i = 0; i < WIDTH; i++)
      out << "ooo";
   out << "o" << endl;

   for(int j = HEIGHT - 1; j >= 0; j--)
   {
      out << "o";
      for(int i = 0; i < WIDTH; i++)
      {
         if(B.State[i][j] == STATE_FORBIDDEN)
            out << "   ";
         else if(B.State[i][j] == STATE_EMPTY)
            out << " . ";
         else
            out << " " << (char)('A' + B.State[i][j]) << " ";
      }
      out << "o" << endl;
   }

   out << "o";
   for(int i = 0; i < WIDTH; i++)
      out << "ooo";
   out << "o" << endl;

   return out;
}

Board Solve(Board Current, std::vector<Shape> Shapes)
{
   for(int i = 0; i < Shapes.size(); i++)
   {
      Shape S = Shapes[i];
      int R = S.RotatePeriod;

      for(int r = 0; r < R; r++)
      {
         if(Current.CanPlace(S) == true)
         {
            Board NewBoard = Current.PlaceNext(S);

            std::vector<Shape> NewShapes = Shapes;
            NewShapes.erase(NewShapes.begin() + i);

            // cout << NewBoard << endl;

            NewBoard = Solve(NewBoard, NewShapes);

            if(NewBoard.IsSolution() == true)
               return NewBoard;
         }

         S = S.Rotate();
      }
   }

   return Current;
}





