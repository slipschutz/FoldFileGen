//
// Manager class for holding general information about the reaction to be 
// calcualted
// 
// Is implemented as a static singleton classs 
//

#ifndef __REACTIONMANAGER_HH
#define  __REACTIONMANAGER_HH

#include "Nucleus.hh"
#include <string>
#include <iostream>
#include <fstream>
#include "FormatedFile.hh"
using namespace std;

class ReactionManager{

public:
  void SetIntialNucleusAZ(int,int);
  void SetFinalNucleusAZ(int,int);

  Nucleus * InitialNucleus;
  Nucleus *  FinalNucleus;

  inline Nucleus * GetInitialNucleus(){return InitialNucleus;}
  inline Nucleus * GetFinalNucleus(){return FinalNucleus;}
  
  void SetInitialNucleus(Nucleus*);
  void SetFinalNucleus(Nucleus*);

  //The Static access method for manager
  static  ReactionManager *GetInstance();

  void RegisterFile(FormatedFile *aFile);
  void BuildFiles();//appply the virtual methods in each file type to load it self
  
  void SetBindingEnergyFile(string);
  ifstream* GetBindingEnergyFile();

private:
  //Constructor deconstructor is private for singleton
  ReactionManager();
  ~ReactionManager();
  vector <FormatedFile*> theFiles;
  ifstream BE_File;
};
#endif
