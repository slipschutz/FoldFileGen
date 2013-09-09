
#include "NormodFile.hh"




NormodFile::NormodFile(){
  
  waveFunctionCount=0;
  LengthFloat=5;
  //Card 1 is always just 0
  Line Card1;
  Card1.AddField(3,0);
  PushLine(Card1);

  InitialNucleus = ReactionManager::GetInstance()->GetInitialNucleus();
  FinalNucleus = ReactionManager::GetInstance()->GetFinalNucleus();
  
  
}

void NormodFile::SetTransitions (Transition aTran){
  aTran.Print();

  int size = aTran.theTransitions.size();
  vector <Shell> Particles;
  vector <Shell> Holes;
  int ParticleBit=-1;//The type of particle for the holes
  int HoleBit=-1; //the type of particle for the particles
  //0 for neutrons and 1 for protons as defined in normal mode
  if ( ReactionManager::GetInstance()->isPNType ){
    //For (p,n) type reactions first in transtion object
    //is the neutron shells
    //so holes are first then particles ssecond
    ParticleBit=1;
    HoleBit=0;
  } else { //(n,p) type reaction
    //the first entry in the transition should be protons
    //the protons are holes and the neutrons are particles
    ParticleBit=0;
    HoleBit=1;
  }
  Particles= aTran.GetSecondShells();
  Holes = aTran.GetFirstShells();
  //Normal modes wants the particle states first

    int numParticleShells = Particles.size();
    Line Card2;
    Card2.AddField(3,numParticleShells);
    PushLine(Card2);
      
    for (int i=0;i<numParticleShells;i++){
      Line l = MakeShellLine(Particles[i],ParticleBit,true);
      PushLine( l );
    }

    int numHoleShells = Holes.size();
    Line Card4;
    Card4.AddField(3,numHoleShells);
    PushLine(Card4);

    for (int i=0;i<numHoleShells;i++){
      Line l = MakeShellLine(Holes[i],HoleBit,false);
      PushLine( l );
    }
    //Now make the last line
    //for GT transition
    
    // M JTran Parity MassTarget 1 1 for PN 1 -1 NP min N max N
    Line Card6;
    Card6.AddField(LengthFloat,0); //it is a GT transition
    Card6.AddField(LengthFloat,1); //it is a GT Transition so deltaJ=1
    Card6.AddField(LengthFloat,1); //No paritry change for GT
    Card6.AddField(LengthFloat,InitialNucleus->GetA());
    if (ReactionManager::GetInstance()->isPNType){
      Card6.AddField(LengthFloat,1);
      Card6.AddField(LengthFloat,1);
    }else {
      Card6.AddField(LengthFloat,1);
      Card6.AddField(LengthFloat,-1);
    }
    Card6.AddField(LengthFloat,0);
    Card6.AddField(LengthFloat,0);
    
    PushLine(Card6);//add the line to the list;

}


Line NormodFile::MakeShellLine(Shell theShell,int pFlag,bool isParticle){
  //pFLag 0 for neutron 1 for proton
  Line theLine;
  theLine.AddField(LengthFloat,(int)theShell.Getn()-1);
  theLine.AddField(LengthFloat,(int)theShell.Getl());
  theLine.AddField(LengthFloat,(int)(2*theShell.GetJ()));
  if (isParticle){
    theLine.AddField(LengthFloat,theShell.GetEmptiness());
  } else {
    theLine.AddField(LengthFloat,theShell.GetFullness());
  }
  theLine.AddField(LengthFloat,(int)pFlag);
  theLine.AddField(LengthFloat,(int)theShell.GetN());
  theLine.AddField(LengthFloat,(int)waveFunctionCount);
  waveFunctionCount++;
  return theLine;
}
