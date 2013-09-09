




#include <iostream>
#include <iomanip>

#include "WsawFile.hh"
#include "NormodFile.hh"
#include "FoldFile.hh"
#include "ReactionManager.hh"
#include "ErrorManager.hh"
//#include "Line.hh"

using namespace std;



int main(int argc,char**argv){
  /*  if (argc != 3 )
    return 1;
  
  cout<<atoi(argv[0])<<endl;
  Nucleus aNuc(atoi(argv[1]),atoi(argv[2]));
  aNuc.Draw();
  vector<Shell> vec = aNuc.GetModelSpaceZShells();
  for (int i=0;i<vec.size();i++){
    cout<<vec[i].GetName()<<endl;
  }
  cout<<"SDGSAG"<<endl;

  cout<<aNuc.GetNextShellClosure(126)<<endl;
  return 0;
  */

  try {

    ReactionManager::GetInstance()->SetBindingEnergyFile("Binding_Energies");
    ReactionManager::GetInstance()->GetInitialNucleus()->SetJPi("0+");
    ReactionManager::GetInstance()->GetFinalNucleus()->SetJPi("1+");

    
    
    
    Transition t =ReactionManager::GetInstance()->FindGTTransitions();

    NormodFile n;
    n.OpenFile("test.normod");
    n.SetTransitions(t);
    n.Write();
    
    system("./NormodSetUp.sh test.normod");

    WsawFile aFile;
    aFile.CalcCard34();

    aFile.OpenFile("test.wsaw");
    
    aFile.BuildFields();
    
    aFile.Write();
    
    FoldFile aFold;
    aFold.SetNormodFile("test.normod_out");
    aFold.Build();
    aFold.OpenFile("test.fold");
    aFold.Write();
    
  } catch (...){

    ErrorManager::BoxPrint("Fatal Error.  Program exiting ...");
  
  }
  
  return 0;
}
