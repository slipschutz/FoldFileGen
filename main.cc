




#include <iostream>
#include <iomanip>

#include "WsawFile.hh"
//#include "Line.hh"
using namespace std;



int main(){


  WsawFile aFile;


  aFile.OpenFile("test.wsaw");
  aFile.SetBindingEnergyFile("Binding_Energies");
  aFile.BuildFields();
  aFile.Write();



  return 0;
}
