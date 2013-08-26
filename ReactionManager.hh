//
// Manager class for holding general information about the reaction to be 
// calcualted
// 
// Is implemented as a static singleton classs 
//

#ifndef __REACTIONMANAGER_HH
#define  __REACTIONMANAGER_HH

#include "Nucleus.hh"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "FormatedFile.hh"
#include "Transition.hh"
using namespace std;

class ReactionManager{

public:
  void SetInitialNucleusAZ(int,int);
  void SetFinalNucleusAZ(int,int);

  Nucleus * InitialNucleus;
  Nucleus *  FinalNucleus;

  Nucleus * GetInitialNucleus();
  Nucleus * GetFinalNucleus();
  
  void SetInitialNucleus(Nucleus*);
  void SetFinalNucleus(Nucleus*);

  //The Static access method for manager
  static  ReactionManager *GetInstance();


  void RegisterFile(FormatedFile *aFile);
  void BuildFiles();//appply the virtual methods in each file type to load it self

  Transition FindGTTransitions();
  
  void SetBindingEnergyFile(string);
  ifstream* GetBindingEnergyFile();

  bool isPNType;
  bool isNPType;
  map <string, double> BindingEnergyMapInitial;
  map <string, double> BindingEnergyMapFinal;


private:
  //Constructor deconstructor is private for singleton
  ReactionManager();
  ~ReactionManager();
  vector <FormatedFile*> theFiles;

  
  
  ifstream BE_File;
};
#endif
