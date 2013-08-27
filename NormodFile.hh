

#ifndef __NORMODFILE_HH
#define __NORMODFILE_HH

#include "FormatedFile.hh"
#include "Nucleus.hh"
#include "ReactionManager.hh"
class NormodFile : public FormatedFile{

public:
  NormodFile();
  
  Nucleus * InitialNucleus;
  Nucleus * FinalNucleus;

  void SetTransitions (Transition);

private:
  void CalcOccupancies(Transition aTran);
  Line MakeShellLine(Shell theShell,int pFlag);
  int waveFunctionCount;
  int LengthFloat;

};

#endif
