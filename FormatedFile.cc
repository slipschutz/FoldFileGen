

#include "FormatedFile.hh"




FormatedFile::FormatedFile(){
  
  if (theOutputFile.is_open()){
    theOutputFile.close();
  }


}


FormatedFile::~FormatedFile(){

  if (theOutputFile.is_open()){
    theOutputFile.close();
  }
  theLines.clear();
  

}

void FormatedFile::PushLine(Line &l){
  theLines.push_back(l);



}


void FormatedFile::OpenFile(string FileName){


  theOutputFile.open(FileName.c_str(),std::ofstream::out);
  
  if (! theOutputFile.is_open()){
    cout<<"Warning: Cound not open file "<<FileName<<endl;
  }
}

void FormatedFile::Write(){
  if (  theOutputFile.is_open()) {
    for (int i=0;i<(int)theLines.size();i++){
      
      theLines[i].Write(theOutputFile);
      theOutputFile<<endl;
      
      
    }
  } else {

    cout<<"No output file open"<<endl;

  }

  
}
