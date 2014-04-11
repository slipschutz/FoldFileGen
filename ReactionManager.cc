

#include "ReactionManager.hh"
#include "ErrorManager.hh"
ReactionManager::ReactionManager() : InitialNucleus(NULL),FinalNucleus(NULL),isPNType(false),
				     isNPType(false){
 
  
  WsawFileName="defualt";
  NormodFileName="defualt";
  FoldFileName="defualt";

    
  BindingEnergyMapInitial.clear();
  BindingEnergyMapFinal.clear();
  theFiles.clear();
  BuildHE3T();
}
ReactionManager::~ReactionManager(){
  if (InitialNucleus != NULL)
    delete InitialNucleus;
  
  if ( FinalNucleus != NULL)
    delete FinalNucleus;
}


ReactionManager * ReactionManager::GetInstance(){

  static ReactionManager * r = new ReactionManager();
  
  return r;
}


void ReactionManager::SetInitialNucleusAZ(int A, int Z){
  if (InitialNucleus != NULL ){
    delete InitialNucleus;
  }
  InitialNucleus = new Nucleus(A,Z);
  
}
void ReactionManager::SetFinalNucleusAZ(int A, int Z){
  if (FinalNucleus != NULL ){
    delete FinalNucleus;
  }
  FinalNucleus = new Nucleus(A,Z);
  

}
void ReactionManager::SetInitialNucleus(Nucleus *n){
  
  if (InitialNucleus != NULL){
    delete InitialNucleus;
  }
  InitialNucleus = n;
 
}

void ReactionManager::SetFinalNucleus(Nucleus *n){
  
  if (FinalNucleus != NULL){
    delete FinalNucleus;
  }
  FinalNucleus = n;
 
}

void ReactionManager::RegisterFile(FormatedFile *aFile){
  theFiles.push_back(aFile);

}
void ReactionManager::BuildFiles(){

  for (int i=0;i<(int)theFiles.size();i++){
    theFiles[i]->BuildYourself();
  }
}
void ReactionManager::SetBindingEnergyFile(string s ){
  if (BE_File.is_open()){
    BE_File.close();
  }
  try{
    BE_File.open(s.c_str());
    if (!BE_File.is_open()){
      throw 1;
    }
  } catch (int n){
    stringstream ss;
    ss<<"FILE "<<s<<" NOT FOUND"<<endl;
    ErrorManager::BoxPrint(ss.str());
    throw "crap";
  }

  string temp;
  double temp2;
  double temp3;
  vector <int> tempZ;
  vector <int> tempA;
  bool OnInitial =true;

  while (! BE_File.eof()) {
    BE_File>>temp>>temp2>>temp3;
    if (temp == "Final"){
      OnInitial=false;//once Final is reached in files switch
    } 
    if ( temp3 != -9 ){ // a line with either intial or final z
      tempZ.push_back(temp3);
      tempA.push_back(temp2);
    } else {// a line with binding energies on it
      if (OnInitial)
	BindingEnergyMapInitial[temp]=temp2;
      else
	BindingEnergyMapFinal[temp]=temp2;
    }
  }

  //Preform some checks to make sure file had good info
  try{
    if ( tempA.size() != 2 || tempZ.size()!= 2){
      //should only ever be initial and final states 
      ErrorManager::BoxPrint("Not two A,Z pairs found in",s);
      throw 1;
    } else if ( BindingEnergyMapInitial.size() == 0 || BindingEnergyMapFinal.size()==0){
      ErrorManager::BoxPrint("Missing Binding energy information in",s);
      throw 1;
    }
  } catch (int n){
    throw "crap";
  }
  
  SetInitialNucleusAZ(tempA[0],tempZ[0]); //make the Initial Nuclues obj
  SetFinalNucleusAZ(tempA[1],tempZ[1]); // make the Final Nucleus obj
  if ( FinalNucleus->GetIsoSpinZ()-InitialNucleus->GetIsoSpinZ() == 1){
    isPNType=false;
    isNPType=true;
  }else if(FinalNucleus->GetIsoSpinZ()-InitialNucleus->GetIsoSpinZ() == -1){
    isPNType=true;
    isNPType=false;
  }
 
  cout<<"PN TYPE "<<isPNType<<endl;
  cout<<"NP TYPE "<<isNPType<<endl;


  
}

ifstream* ReactionManager::GetBindingEnergyFile(){
  return &BE_File;
}

Nucleus * ReactionManager::GetInitialNucleus(){
  try{
    if (InitialNucleus != NULL){
      return InitialNucleus;
    } else {
      ErrorManager::BoxPrint("Trying to get initial nucleus from reaction manager before it was initialized");
      throw "crap";
    }
  } catch (int n){
    
  }
  return NULL;//should never make it to this line
}

Nucleus * ReactionManager::GetFinalNucleus(){
  try{
    if (FinalNucleus != NULL){
      return FinalNucleus;
    } else {
      ErrorManager::BoxPrint("Trying to get the final nucleus from reaction manager before it was initialized");
      throw "crap";
    }
  } catch (int n){
    
  }
  return NULL;//should never make it to this line
}
Nucleus * ReactionManager::GetProjectile(){
  return Projectile;
}
Nucleus * ReactionManager::GetEjectile(){
  return Ejectile;
}




Transition ReactionManager::FindGTTransitions(){

  //Calling get the nuclei so that it checks if they have been initialized
  Nucleus * trash;
  trash = GetInitialNucleus();
  trash = GetFinalNucleus();
  
  InitialNucleus->GetNShell("1h11/2")->SetFullness(0.42);  
  InitialNucleus->GetNShell("2d3/2")->SetFullness(0.59);  
  InitialNucleus->GetNShell("3s1/2")->SetFullness(0.69);  
  InitialNucleus->GetNShell("1g7/2")->SetFullness(0.7);  
  InitialNucleus->GetNShell("2d5/2")->SetFullness(0.94);  
  

  vector <Shell> theZShells = InitialNucleus->GetModelSpaceZShells();
  vector <Shell> theNShells = InitialNucleus->GetModelSpaceNShells();


  

  
  map <vector<pair<double,double> >,pair<Shell,Shell> > thePossibleTransitions;  
  if ( isPNType ){
    for (int i=0;i<(int)theNShells.size();i++){
      Shell thisNShell= theNShells[i];
      if (thisNShell.GetFullness() != 0 ){
	for (int j=0;j<(int)theZShells.size();j++){
	  if ( theZShells[j].GetFullness()!=1){
	    double deltaL = abs(thisNShell.Getl()-theZShells[j].Getl());
	    double deltan = abs(thisNShell.Getn()-theZShells[j].Getn());
	    double deltaJ = abs(thisNShell.GetJ()-theZShells[j].GetJ());
	    double deltaSG = thisNShell.GetShellGroup()-theZShells[j].GetShellGroup();
	    if ( deltaL==0 && deltan==0 && (deltaJ==1||deltaJ==0) &&deltaSG==0){//is a GT transition
	      
	      vector <pair<double,double> > temp;
	      
	      temp.push_back(make_pair(thisNShell.Getn(),theZShells[j].Getn()));
	      temp.push_back(make_pair(thisNShell.Getl(),theZShells[j].Getl()));
	      temp.push_back(make_pair(thisNShell.GetJ(),theZShells[j].GetJ()));
	      
	      
	      if (thePossibleTransitions.count(temp) == 0 ){//only if the trans is not there 
		thePossibleTransitions[temp]=make_pair(thisNShell,theZShells[j]);
	      } else {
		ErrorManager::BoxPrint("Hash issue");
		//	  throw "crap";
	      }
	    }
	  }
	}
      }
    }
  }
  cout<<"\n\n\n\n\n"<<endl;
  Transition theTrans;
  for (map<vector<pair<double,double> >,pair<Shell,Shell> >::iterator ii=thePossibleTransitions.begin();
       ii!=thePossibleTransitions.end();ii++){
    
    //cout<< ii->second.first.GetName()<<" "<<ii->second.second.GetName()<<endl;
    theTrans.theTransitions.push_back(make_pair(ii->second.first,ii->second.second));
    }

  return theTrans;
}

vector <double> ReactionManager::GetCoupledValues(double j1, double j2,int parityChange){


  vector <double> temp;
  if ( parityChange == 1 ){ //from + to + or - to -
    //only even values allowed
    
    int num = abs(j1+j2) - abs(j1-j2);
    
    for (int i=0;i<=num;i++){
      if( int(abs(j1-j2) + i) % 2 ==0 )
	temp.push_back(abs(j1-j2) +i);
    }
  } else if (parityChange == -1 ){
    //only odd values allowed
    
    int num = abs(j1+j2) - abs(j1-j2);
    
    for (int i=0;i<=num;i++){
      if( int(abs(j1-j2) + i) % 2 !=0 )
	temp.push_back(abs(j1-j2) +i);
    }
  }
  return temp;
    
}
vector <double> ReactionManager::GetCoupledValues(double j1,double j2){
  
  vector <double> temp;
  int num = abs(j1+j2) - abs(j1-j2);
  
  for (int i=0;i<=num;i++){
    temp.push_back(abs(j1-j2) +i);
  }

  return temp;

}


vector <double> ReactionManager::GetJTran(){

  

  
}
void ReactionManager::BuildHE3T(){

  Projectile = new Nucleus(3,2);
  Ejectile = new Nucleus(3,1);
  
  Projectile->SetJPi("1/2+");
  Ejectile->SetJPi("1/2+");

  (*Projectile->GetTheZCoefs())[make_pair("1s1/2","1s1/2")]=0.707;

  (*Ejectile->GetTheZCoefs())[make_pair("1s1/2","1s1/2")]=0.707;
  
}

void ReactionManager::PrintBEMaps(){
  cout<<"INITIAL"<<endl;
  for (map<string,double>::iterator ii = BindingEnergyMapInitial.begin();
       ii!=BindingEnergyMapInitial.end();ii++){
    cout<<ii->first<<"  "<<ii->second<<endl;

  }
  cout<<"FIANL"<<endl;
  for (map<string,double>::iterator ii = BindingEnergyMapFinal.begin();
       ii!=BindingEnergyMapFinal.end();ii++){
    cout<<ii->first<<"  "<<ii->second<<endl;

  }
}
