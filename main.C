




#include <iostream>
#include <iomanip>

#include "WsawFile.hh"
#include "ReactionManager.hh"
#include "ErrorManager.hh"
//#include "Line.hh"
using namespace std;



int main(int argc,char**argv){
  
  

  try {
    //b.BoxPrint("this is a long message with lots of stuff in it.  I don't know what will happen");

    
    ReactionManager::GetInstance()->SetBindingEnergyFile("Binding_Energies");


    /*WsawFile aFile;
    
    
    aFile.OpenFile("test.wsaw");
    aFile.SetBindingEnergyFile("Binding_Energies");
    aFile.BuildFields();
    aFile.Write();
    */

  } catch (...){

    ErrorManager::BoxPrint("Fatal Error.  Program exiting...");
  
  }
  
  return 0;
}
