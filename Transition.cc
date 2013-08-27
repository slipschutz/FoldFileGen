#include "Transition.hh"

Transition::Transition(){
  ;;
}
Transition::~Transition(){
  
  theTransitions.clear();
  theProtonShells.clear();
  theNeutronShells.clear();

}


vector <Shell> Transition::GetFirstShells (){
  
  if (theTransitions.size() == 0 ){
    ErrorManager::BoxPrint("Attempting to get shells without any transitions specified in theTransiions");
    throw "crap";
  }

  vector<Shell> ret;  
  
  for (int i=0;i<theTransitions.size();i++){
    if (! Find(ret,theTransitions[i].first) ){
      ret.push_back(theTransitions[i].first);
    }
  }
  return ret;
}

vector <Shell> Transition::GetSecondShells (){
  
  if (theTransitions.size() == 0 ){
    ErrorManager::BoxPrint("Attempting to get shells without any transitions specified in theTransiions");
    throw "crap";
  }

  vector<Shell> ret;  
  
  for (int i=0;i<theTransitions.size();i++){
    if (! Find(ret,theTransitions[i].second) ){
      ret.push_back(theTransitions[i].second);
    }
  }
  return ret;
}



bool Transition::Find(vector <Shell> v,  Shell s){
  bool isThere =false;
  for (int i=0;i<v.size();i++){
    if (v[i].GetName() == s.GetName()){
      isThere=true;
    }
  }
  return isThere;
}


void Transition::Print(){
  
  for (int i=0;i<theTransitions.size();i++){
    cout<<"First is "<<theTransitions[i].first.GetName();
    cout<<" Second is "<<theTransitions[i].second.GetName()<<endl;

  }


}
