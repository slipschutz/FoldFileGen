

#ifndef __FOLDFILE_HH
#define __FOLDFILE_HH


#include "FormatedFile.hh"
#include "Nucleus.hh"
#include "ReactionManager.hh"
#include <string>
#include <sstream>
#include <map>
#include <fstream>
class FoldFile : public FormatedFile{

public: 
  
  FoldFile();
  ~FoldFile();

  void DefineWaveFunctionIDs();

  Nucleus * InitialNucleus;
  Nucleus * FinalNucleus;

  void Build();

  void SetNormodFile(string );

private:
  void BuildLine3or4(Nucleus*,Nucleus*);
  void BuildCard5();
  double ELab;

  string fileName;
  int floatLength;
  int intLength;
  int stringLength;
  map <string,int> WaveFunctionIDs;
  
};


#endif
