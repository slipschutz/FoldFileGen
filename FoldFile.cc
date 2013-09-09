

#include "FoldFile.hh"



FoldFile::FoldFile(){

  //  Defualt values 
  fileName = "FOLDOUT";
  ELab=420;

  floatLength=10;
  intLength=5;
  stringLength=8;
    

  InitialNucleus = ReactionManager::GetInstance()->GetInitialNucleus();
  FinalNucleus = ReactionManager::GetInstance()->GetFinalNucleus();

  DefineWaveFunctionIDs();
}

FoldFile::~FoldFile(){



}

void FoldFile::Build(){


  Line Card1;
  Card1.AddField(intLength,1);
  Card1.AddField(intLength,1);
  Card1.AddField(stringLength,fileName);
  PushLine(Card1);

  Line Card2;
  //NR, H, ELAB, APROJ, IPRTR, IPRTQ, IPRTF
  Card2.AddField(intLength,600);
  Card2.AddField(floatLength,0.03);
  Card2.AddField(floatLength,ELab);
  Card2.AddField(floatLength,3.0);
  Card2.AddField(intLength,1);
  Card2.AddField(intLength,1);
  Card2.AddField(intLength,1);
  PushLine(Card2);

  BuildLine3or4(ReactionManager::GetInstance()->GetProjectile(),
		ReactionManager::GetInstance()->GetEjectile());
  //Card 3 is projecticle first
  Line n2;
  n2.AddField(8,"HE3H3");
  PushLine(n2);


  BuildLine3or4(InitialNucleus,FinalNucleus);


  Line n1;
  n1.AddField(8,ReactionManager::GetInstance()->WsawFileName);
  PushLine(n1);
  BuildCard5();
}


void FoldFile::BuildCard5(){
  double E_Beam=ELab;
  double Mass_target=InitialNucleus->GetA();
  double Mass_Projectile=ReactionManager::GetInstance()->GetProjectile()->GetA();
  double Mass_Proton=0.938783872*1000.0;

  double alpha=(E_Beam/Mass_Projectile)/(2*Mass_Proton);
  double beta=4*(alpha*Mass_target)/(pow(1+Mass_target,2));

  double ka2 = pow(Mass_Proton,2)*Mass_target*beta*((1+alpha)/(1+beta));

  double ka = sqrt(ka2)/197.273;

  double e02 = pow(Mass_Proton,2)*(1+alpha);
  double ep2 = pow(Mass_Proton,2)+ka2;
  double et2 = pow(Mass_Proton,2)+(ka2/pow(Mass_target,2));

  Line Card5;

  Card5.AddField(floatLength,e02/sqrt(ep2*et2));
  Card5.AddField(floatLength,ka);
  Card5.AddField(floatLength,1.0);
  Card5.AddField(floatLength,"love_140");
  

  PushLine(Card5);
}

void FoldFile::BuildLine3or4(Nucleus* initial,Nucleus* final){
  stringstream ss;
  Line a;
  ss<<final->GetJ()<<final->GetStringP();
  a.AddField(floatLength,ss.str());
  ss.str("");
  ss<<initial->GetJ()<<initial->GetStringP();
  a.AddField(floatLength,ss.str());


  PushLine(a);
  ss.str("");
  
  Line b;

  b.AddField(floatLength,final->GetIsoSpin());
  b.AddField(floatLength,final->GetStringIZ());

  b.AddField(floatLength,initial->GetIsoSpin());
  b.AddField(floatLength,initial->GetStringIZ());
  
  PushLine(b);

  Line c;
  c.AddField(intLength,3); //Charge Exchange type
  c.AddField(intLength,3);//Z[T] format
  c.AddField(floatLength,0);//Alpha

  PushLine(c);


  
  //The Z Coef information is the same for both the inita and Final Particles
  
  for (map<pair<string,string>,double>::iterator ii=initial->GetTheZCoefs()->begin();
       ii!=initial->GetTheZCoefs()->end();ii++){
    Line d;
    d.AddField(intLength,WaveFunctionIDs[ii->first.first]);
    d.AddField(intLength,WaveFunctionIDs[ii->first.second]);
    d.AddField(intLength,0);
    d.AddField(floatLength,0.0);
    d.AddField(floatLength,ii->second);


    PushLine(d);

  }
  Line e;
  e.AddField(intLength,-1);
  e.AddField(intLength,-1);
  PushLine(e);


  
}


void FoldFile::DefineWaveFunctionIDs(){
  //The key for folds definitions of wave
  //function except starting at n=1 instead of
  //n = 0

  WaveFunctionIDs["1s1/2"]=1;
  WaveFunctionIDs["1p1/2"]=2;
  WaveFunctionIDs["1p3/2"]=3;
  WaveFunctionIDs["2s1/2"]=4;
  WaveFunctionIDs["1d3/2"]=5;
  WaveFunctionIDs["1d5/2"]=6;
  WaveFunctionIDs["2p1/2"]=7;
  WaveFunctionIDs["2p3/2"]=8;
  WaveFunctionIDs["1f5/2"]=9;
  WaveFunctionIDs["1f7/2"]=10;
  WaveFunctionIDs["3s1/2"]=11;
  WaveFunctionIDs["2d3/2"]=12;
  WaveFunctionIDs["2d5/2"]=13;
  WaveFunctionIDs["1g7/2"]=14;
  WaveFunctionIDs["1g9/2"]=15;
  WaveFunctionIDs["3p1/2"]=16;
  WaveFunctionIDs["3p3/2"]=17;
  WaveFunctionIDs["2f5/2"]=18;
  WaveFunctionIDs["2f7/2"]=19;
  WaveFunctionIDs["1h9/2"]=20;
  WaveFunctionIDs["1h11/2"]=21;

}

void FoldFile::SetNormodFile(string name){
  
  
  ifstream inFile;
  inFile.open(name);
  if (!inFile.is_open() ){
    throw "Crap";
  }

  map <double,string> l2string;
  l2string[0]="s";
  l2string[1]="p";
  l2string[2]="d";
  l2string[3]="f";
  l2string[4]="g";
  l2string[5]="h";
  l2string[6]="i";
 
  stringstream ss1,ss2;
  double pn,pl,p2j,pt;
  double hn,hl,h2j,ht;
  double junk;
  double ZCoef;
  while (!inFile.eof()){
    ss1.str("");
    ss2.str("");
    inFile>>pn>>pl>>p2j>>pt>>hn>>hl>>h2j>>ht>>junk>>ZCoef>>junk>>junk;
    ss2<<hn+1<<l2string[hl]<<h2j<<"/2";
    ss1<<pn+1<<l2string[pl]<<p2j<<"/2";
    (*InitialNucleus->GetTheZCoefs())[make_pair(ss2.str(),ss1.str())]=ZCoef;
    (*FinalNucleus->GetTheZCoefs())[make_pair(ss2.str(),ss1.str())]=ZCoef;
  }
  //the information from normal modes is stored as hole first then particle to 
  //match the ordering in FOLD

}
