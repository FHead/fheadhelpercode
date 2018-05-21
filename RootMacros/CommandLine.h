#include <map>
#include <vector>
#include <iostream>

class CommandLine
{
private:
   std::string Self;
   std::map<std::string, std::string> Arguments;
   std::vector<std::string> ExtraArguments;
public:
   CommandLine(int argc, char *argv[]);
   ~CommandLine();
   void Initialize(int argc, char *argv[]);
   std::string operator [](int Index);
   std::string operator [](std::string Key);
};

CommandLine::CommandLine(int argc, char *argv[])
{
   Initialize(argc, argv);
}

CommandLine::~CommandLine()
{
}

void CommandLine::Initialize(int argc, char *argv[])
{
   Self = "";
   Arguments.clear();
   ExtraArguments.clear();

   if(argc < 1)
      return;

   Self = argv[0];

   for(int i = 1; i < argc; i++)
   {
      if(argv[i][0] != '-')
         ExtraArguments.push_back(argv[i]);
      else
      {
         std::string Key = argv[i];
         while(Key.size() > 0 && Key[0] == '-')
            Key.erase(Key.begin());

         if(i + 1 >= argc || argv[i+1][0] == '-')
            Arguments.insert(std::pair<std::string, std::string>(Key, "1"));
         else
         {
            Arguments.insert(std::pair<std::string, std::string>(argv[i], Value));
            i = i + 1;
         }
      }
   }
}

std::string CommandLine::operator [](int Index)
{
   if(Index < 0 || Index >= ExtraArguments.size())
      throw("Exception: arguemnt index out of range");
   
   return ExtraArguments[Index];
}
   
std::string CommandLine::operator [](std::string Key)
{
   if(Arguments.find(Key) == Arguments.end())
      throw("Exception: Key \"" + Key + "\" not found in arguments");

   return Arguments[Key];
}


