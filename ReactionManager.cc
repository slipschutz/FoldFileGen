

#include "ReactionManager.hh"
#include "ErrorManager.hh"
ReactionManager::ReactionManager() : InitialNucleus(NULL),FinalNucleus(NULL){
  //blah
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
  ErrorManager E;
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
    E.BoxPrint(ss.str());
    throw "crap";
  }

}

ifstream* ReactionManager::GetBindingEnergyFile(){
  return &BE_File;
}

