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

  Nucleus * Projectile;
  Nucleus * Ejectile;

  Nucleus * GetProjectile();
  Nucleus * GetEjectile();
  void PrintBEMaps();

  //The Static access method for manager
  static  ReactionManager *GetInstance();

  vector <double> GetJTran();
  vector <double> GetCoupledValues(double,double,int);
  vector <double> GetCoupledValues(double,double);
  void RegisterFile(FormatedFile *aFile);
  void BuildFiles();//appply the virtual methods in each file type to load it self

  Transition FindGTTransitions();
  
  void SetBindingEnergyFile(string);
  ifstream* GetBindingEnergyFile();

  bool isPNType;
  bool isNPType;
  map <string, double> BindingEnergyMapInitial;
  map <string, double> BindingEnergyMapFinal;

  string WsawFileName;
  string NormodFileName;
  string FoldFileName;

private:
  //Constructor deconstructor is private for singleton
  ReactionManager();
  ~ReactionManager();
  vector <FormatedFile*> theFiles;

  void BuildHE3T();
  
  ifstream BE_File;
};
#endif
