

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
  


private:




};

#endif
