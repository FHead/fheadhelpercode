#ifndef ParticleMasses_H_7262_JEIKRGJHWIKGIJSKDFHNRGHFERAGH
#define ParticleMasses_H_7262_JEIKRGJHWIKGIJSKDFHNRGHFERAGH

#include <map>
#include <string>
#include <ostream>

struct SingleParticleInformation;
class ParticleInformation;

struct SingleParticleInformation
{
public:
   double Mass;
   double Charge;
   std::string Name;
   std::string AntiName;
   int PDGID;
public:
   SingleParticleInformation()
   {
      Mass = -1;
      Charge = 0;
      Name = "Undefined";
      AntiName = "Undefined-bar";
      PDGID = 0;
   }
};

class ParticleInformation
{
private:
   std::map<int, SingleParticleInformation> ParticleInfo;
   std::map<std::string, int> NameToPDGID;
public:
   ParticleInformation();
   ~ParticleInformation();
   const SingleParticleInformation operator [](int PDGID);
   const SingleParticleInformation operator [](std::string Name);
   void PrintAvailableParticlesToStream(std::ostream &out);
private:
   void Initialize();
};
   
ParticleInformation::ParticleInformation()
{
   Initialize();
}

ParticleInformation::~ParticleInformation()
{
   ParticleInfo.clear();
   NameToPDGID.clear();
}

const SingleParticleInformation ParticleInformation::operator [](int PDGID)
{
   if(ParticleInfo.find(abs(PDGID)) == ParticleInfo.end())
      return SingleParticleInformation();

   SingleParticleInformation Result = ParticleInfo[abs(PDGID)];

   if(PDGID < 0 && Result.AntiName == "")
      return SingleParticleInformation();

   if(PDGID < 0)   // anti-particle -- swap charges and PDGID
   {
      Result.Charge = -Result.Charge;
      swap(Result.Name, Result.AntiName);
      Result.PDGID = -Result.PDGID;
   }

   return Result;
}

const SingleParticleInformation ParticleInformation::operator [](std::string Name)
{
   if(NameToPDGID.find(Name) == NameToPDGID.end())
      return SingleParticleInformation();

   return (*this)[NameToPDGID[Name]];
}

void ParticleInformation::PrintAvailableParticlesToStream(std::ostream &out)
{
   out << "Available particles:" << endl;
   for(std::map<int, SingleParticleInformation>::iterator iter = ParticleInfo.begin(); iter != ParticleInfo.end(); iter++)
      out << "   \"" << iter->second.Name << "\" (" << iter->second.PDGID << "), " << iter->second.Mass << " GeV" << endl;
}

void ParticleInformation::Initialize()
{
   ParticleInfo.clear();
   NameToPDGID.clear();

   ParticleInfo[1].Mass = 0.005;
   ParticleInfo[1].Charge = -1.0 / 3.0;
   ParticleInfo[1].Name = "d";
   ParticleInfo[1].AntiName = "dbar";
   ParticleInfo[1].PDGID = 1;
   NameToPDGID["d"] = 1;
   NameToPDGID["dbar"] = -1;
   NameToPDGID["down"] = 1;
   NameToPDGID["downbar"] = -1;

   ParticleInfo[2].Mass = 0.0025;
   ParticleInfo[2].Charge = 2.0 / 3.0;
   ParticleInfo[2].Name = "u";
   ParticleInfo[2].AntiName = "ubar";
   ParticleInfo[2].PDGID = 2;
   NameToPDGID["u"] = 2;
   NameToPDGID["ubar"] = -2;
   NameToPDGID["up"] = 2;
   NameToPDGID["upbar"] = -2;

   ParticleInfo[3].Mass = 0.100;
   ParticleInfo[3].Charge = -1.0 / 3.0;
   ParticleInfo[3].Name = "s";
   ParticleInfo[3].AntiName = "sbar";
   ParticleInfo[3].PDGID = 3;
   NameToPDGID["s"] = 3;
   NameToPDGID["sbar"] = -3;
   NameToPDGID["strange"] = 3;
   NameToPDGID["strangebar"] = -3;

   ParticleInfo[4].Mass = 1.29;
   ParticleInfo[4].Charge = 2.0 / 3.0;
   ParticleInfo[4].Name = "c";
   ParticleInfo[4].AntiName = "cbar";
   ParticleInfo[4].PDGID = 4;
   NameToPDGID["c"] = 4;
   NameToPDGID["cbar"] = -4;
   NameToPDGID["charm"] = 4;
   NameToPDGID["charmbar"] = -4;

   ParticleInfo[5].Mass = 4.19;
   ParticleInfo[5].Charge = -1.0 / 3.0;
   ParticleInfo[5].Name = "b";
   ParticleInfo[5].AntiName = "bbar";
   ParticleInfo[5].PDGID = 5;
   NameToPDGID["b"] = 5;
   NameToPDGID["bbar"] = -5;
   NameToPDGID["bottom"] = 5;
   NameToPDGID["bottombar"] = -5;

   ParticleInfo[6].Mass = 172.9;
   ParticleInfo[6].Charge = 2.0 / 3.0;
   ParticleInfo[6].Name = "t";
   ParticleInfo[6].AntiName = "tbar";
   ParticleInfo[6].PDGID = 6;
   NameToPDGID["t"] = 6;
   NameToPDGID["tbar"] = -6;
   NameToPDGID["top"] = 6;
   NameToPDGID["topbar"] = -6;

   ParticleInfo[111].Mass = 0.1349766;
   ParticleInfo[111].Charge = 0;
   ParticleInfo[111].Name = "pi0";
   ParticleInfo[111].AntiName = "";
   ParticleInfo[111].PDGID = 111;
   NameToPDGID["pi0"] = 111;
   NameToPDGID["pizero"] = 111;

   ParticleInfo[211].Mass = 0.13957018;
   ParticleInfo[211].Charge = 1;
   ParticleInfo[211].Name = "pi+";
   ParticleInfo[211].AntiName = "pi-";
   ParticleInfo[211].PDGID = 211;
   NameToPDGID["pi+"] = 211;
   NameToPDGID["piplus"] = 211;
   NameToPDGID["pi-"] = -211;
   NameToPDGID["piminus"] = -211;

   ParticleInfo[113].Mass = 0.77549;   // ?????
   ParticleInfo[113].Charge = 0;
   ParticleInfo[113].Name = "rho0";
   ParticleInfo[113].AntiName = "";
   ParticleInfo[113].PDGID = 113;
   NameToPDGID["rho"] = 113;
   NameToPDGID["rho0"] = 113;
   NameToPDGID["rho(770)"] = 113;
   NameToPDGID["rho(770)0"] = 113;

   ParticleInfo[213].Mass = 0.77549;   // ?????
   ParticleInfo[213].Charge = 0;
   ParticleInfo[213].Name = "rho+";
   ParticleInfo[213].AntiName = "rho-";
   ParticleInfo[213].PDGID = 213;
   NameToPDGID["rho+"] = 213;
   NameToPDGID["rho(770)+"] = 213;
   NameToPDGID["rho-"] = -213;
   NameToPDGID["rho(770)-"] = -213;

   ParticleInfo[221].Mass = 0.547853;
   ParticleInfo[221].Charge = 0;
   ParticleInfo[221].Name = "eta";
   ParticleInfo[221].AntiName = "";
   ParticleInfo[221].PDGID = 221;
   NameToPDGID["eta"] = 221;

   ParticleInfo[331].Mass = 0.95778;
   ParticleInfo[331].Charge = 0;
   ParticleInfo[331].Name = "eta'";
   ParticleInfo[331].AntiName = "";
   ParticleInfo[331].PDGID = 331;
   NameToPDGID["eta'"] = 331;
   NameToPDGID["eta(958)"] = 331;
   NameToPDGID["eta'(958)"] = 331;
   NameToPDGID["etaprime"] = 331;

   ParticleInfo[311].Mass = 0.497614;
   ParticleInfo[311].Charge = 0;
   ParticleInfo[311].Name = "K0";
   ParticleInfo[311].AntiName = "K0bar";
   ParticleInfo[311].PDGID = 311;
   NameToPDGID["K0"] = 311;
   NameToPDGID["K0bar"] = -311;
   NameToPDGID["K0Bar"] = -311;

   ParticleInfo[310].Mass = 0.493677;
   ParticleInfo[310].Charge = 1;
   ParticleInfo[310].Name = "K+";
   ParticleInfo[310].AntiName = "K-";
   ParticleInfo[310].PDGID = 310;
   NameToPDGID["K+"] = 310;
   NameToPDGID["K-"] = -310;

   ParticleInfo[130].Mass = 0.497614;   // with asterisks
   ParticleInfo[130].Charge = 0;
   ParticleInfo[130].Name = "K0_L";
   ParticleInfo[130].AntiName = "";
   ParticleInfo[130].PDGID = 130;
   NameToPDGID["K0_L"] = 130;
   NameToPDGID["K0L"] = 130;
   NameToPDGID["Klong"] = 130;
   NameToPDGID["K0long"] = 130;

   ParticleInfo[310].Mass = 0.497614;   // with asterisks
   ParticleInfo[310].Charge = 0;
   ParticleInfo[310].Name = "K0_S";
   ParticleInfo[310].AntiName = "";
   ParticleInfo[310].PDGID = 310;
   NameToPDGID["K0_S"] = 310;
   NameToPDGID["K0S"] = 310;
   NameToPDGID["Kshort"] = 310;
   NameToPDGID["K0short"] = 310;

   ParticleInfo[223].Mass = 0.78265;
   ParticleInfo[223].Charge = 0;
   ParticleInfo[223].Name = "omega";
   ParticleInfo[223].AntiName = "";
   ParticleInfo[223].PDGID = 223;
   NameToPDGID["omega"] = 223;
   NameToPDGID["omega(782)"] = 223;

   ParticleInfo[333].Mass = 1.019455;
   ParticleInfo[333].Charge = 0;
   ParticleInfo[333].Name = "phi";
   ParticleInfo[333].AntiName = "";
   ParticleInfo[333].PDGID = 333;
   NameToPDGID["phi"] = 333;
   NameToPDGID["phi(1020)"] = 333;
   
   ParticleInfo[2212].Mass = 0.938272013;
   ParticleInfo[2212].Charge = 1;
   ParticleInfo[2212].Name = "p";
   ParticleInfo[2212].AntiName = "pbar";
   ParticleInfo[2212].PDGID = 2212;
   NameToPDGID["p"] = 2212;
   NameToPDGID["p+"] = 2212;
   NameToPDGID["pbar"] = -2212;
   NameToPDGID["p-"] = -2212;
   
   ParticleInfo[2112].Mass = 0.939565346;
   ParticleInfo[2112].Charge = 0;
   ParticleInfo[2112].Name = "n";
   ParticleInfo[2112].AntiName = "";
   ParticleInfo[2112].PDGID = 2112;
   NameToPDGID["n"] = 2112;
   NameToPDGID["n0"] = 2112;

   ParticleInfo[2224].Mass = 1.232;
   ParticleInfo[2224].Charge = 2;
   ParticleInfo[2224].Name = "Delta++";
   ParticleInfo[2224].AntiName = "Deltabar--";
   ParticleInfo[2224].PDGID = 2224;
   NameToPDGID["Delta++"] = 2224;
   NameToPDGID["Deltabar--"] = -2224;
   NameToPDGID["DeltaBar--"] = -2224;

   ParticleInfo[2214].Mass = 1.232;
   ParticleInfo[2214].Charge = 1;
   ParticleInfo[2214].Name = "Delta+";
   ParticleInfo[2214].AntiName = "Deltabar-";
   ParticleInfo[2214].PDGID = 2214;
   NameToPDGID["Delta+"] = 2214;
   NameToPDGID["Deltabar-"] = -2214;
   NameToPDGID["DeltaBar-"] = -2214;

   ParticleInfo[2114].Mass = 1.232;
   ParticleInfo[2114].Charge = 0;
   ParticleInfo[2114].Name = "Delta0";
   ParticleInfo[2114].AntiName = "Deltabar0";
   ParticleInfo[2114].PDGID = 2114;
   NameToPDGID["Delta0"] = 2114;
   NameToPDGID["Deltabar0"] = -2114;
   NameToPDGID["DeltaBar0"] = -2114;

   ParticleInfo[1114].Mass = 1.232;
   ParticleInfo[1114].Charge = -1;
   ParticleInfo[1114].Name = "Delta-";
   ParticleInfo[1114].AntiName = "Deltabar+";
   ParticleInfo[1114].PDGID = 1114;
   NameToPDGID["Delta-"] = 1114;
   NameToPDGID["Deltabar+"] = -1114;
   NameToPDGID["DeltaBar+"] = -1114;
   
   ParticleInfo[3122].Mass = 1.115683;
   ParticleInfo[3122].Charge = 0;
   ParticleInfo[3122].Name = "Lambda0";
   ParticleInfo[3122].AntiName = "Lambdabar0";
   ParticleInfo[3122].PDGID = 3122;
   NameToPDGID["Lambda"] = 3122;
   NameToPDGID["Lambda0"] = 3122;
   NameToPDGID["Lambdabar"] = -3122;
   NameToPDGID["Lambdabar0"] = -3122;
   NameToPDGID["LambdaBar"] = -3122;
   NameToPDGID["LambdaBar0"] = -3122;
}

#endif


