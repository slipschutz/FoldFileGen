
#include "NormodFile.hh"




NormodFile::NormodFile(){
  
  waveFunctionCount=0;
  LengthFloat=4;
  //Card 1 is always just 0
  Line Card1;
  Card1.AddField(3,0);
  PushLine(Card1);

  InitialNucleus = ReactionManager::GetInstance()->GetInitialNucleus();
  FinalNucleus = ReactionManager::GetInstance()->GetFinalNucleus();
  
  
}

void NormodFile::SetTransitions (Transition aTran){
  aTran.Print();
  CalcOccupancies(aTran);//Calculate the occupancies of the active shells
  int size = aTran.theTransitions.size();
  if ( ReactionManager::GetInstance()->isPNType ){
    //For (p,n) type reactions first in transtion object
    //is the neutron shells
    //so holes are first then particles ssecond
    //Normal modes wants the particle sates first
    vector <Shell> Particles= aTran.GetSecondShells();

    int numParticleShells = Particles.size();
    Line Card2;
    Card2.AddField(3,numParticleShells);
    PushLine(Card2);
      
    for (int i=0;i<numParticleShells;i++){
      Line l = MakeShellLine(Particles[i],1);
      PushLine( l );

    }
  }
}


Line NormodFile::MakeShellLine(Shell theShell,int pFlag){
  //pFLag 0 for neutron 1 for proton
  Line theLine;
  theLine.AddField(LengthFloat,theShell.Getn()-1);
  theLine.AddField(LengthFloat,theShell.Getl());
  theLine.AddField(LengthFloat,2*theShell.GetJ());
  theLine.AddField(LengthFloat,theShell.GetNormOccupancy());
  theLine.AddField(LengthFloat,pFlag);
  theLine.AddField(LengthFloat,theShell.GetN());
  theLine.AddField(LengthFloat,waveFunctionCount);
  waveFunctionCount++;
  return theLine;
}

void NormodFile::CalcOccupancies(Transition aTran){

  int NumShells = aTran.theTransitions.size();
  Shell *thisShell;
  for (int i=0;i<NumShells;i++){
    
    thisShell= &(aTran.theTransitions[i].first);
    thisShell->SetNormOccupancy((double)thisShell->GetOccupancy()/thisShell->GetMaxOccupancy());

    thisShell= &(aTran.theTransitions[i].second);
    thisShell->SetNormOccupancy((double)thisShell->GetOccupancy()/thisShell->GetMaxOccupancy());
  }

}
