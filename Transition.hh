
#ifndef __TRANSITION_HH
#define __TRANSITION_HH


#include <vector>
#include "ErrorManager.hh"
#include "Nucleus.hh"

class Transition {
public:
  vector < pair<Shell,Shell> > theTransitions;
  
  vector <Shell> GetFirstShells();
  vector <Shell> GetSecondShells();
  void Print();
  
  Transition();
  ~Transition();
private:
  vector < Shell > theProtonShells;
  vector < Shell > theNeutronShells;
  bool Find(vector <Shell>, Shell);
};



#endif
