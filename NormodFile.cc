
#include "NormodFile.hh"




NormodFile::NormodFile(){

  //Card 1 is always just 0
  Line Card1;
  Card1.AddField(3,0);
  PushLine(Card1);

  InitialNucleus = ReactionManager::GetInstance()->GetInitialNucleus();
  FinalNucleus = ReactionManager::GetInstance()->GetFinalNucleus();
  
  
}


