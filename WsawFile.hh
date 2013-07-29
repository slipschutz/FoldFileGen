

#include "FormatedFile.hh"
#include <string>
#include <vector>
#include "Nucleus.hh"
#include <fstream>
#include <cmath>
using namespace std;
class WsawFile : public FormatedFile {
public:
  WsawFile();
  
  ~WsawFile();
  
  void AddCard3(double TMC,double TIZC,
		double V0=60, double A=0.65,
		double R0=1.25, double RC=1.25,
		double VSO=7.0);
  
  void AddCard4(double EBIND,double TMP,
		double TL, double TNODE,
		double TIZP, double XJ,
		double XS);
  
  void CalcCard34();
  
  void SetBindingEnergyFile(string s);

  void BuildFields();
private:

  double RMesh;
  double RMax;
  int NPunch;
  int NBPunch;
  int IDBug;
  
  string FileName;
  
  Nucleus theInitialNucleus;
  Nucleus theFinalNucleus;


  ifstream BindingEnergyFile;
  map <string, double > BindingEnergyMapInitial;
  map <string, double > BindingEnergyMapFinal;
  
  bool isPNType;
  bool isNPType;

  vector <Line> Card3s;
  vector <Line> Card4s;

private:
  
  int LengthInt;
  int LengthFloat;
  int LengthString;

};
