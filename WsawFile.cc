
#include "WsawFile.hh"


WsawFile::WsawFile() {

  ///Default values for parameters
  RMesh=0.1;
  RMax= 20.0;
  NPunch=1;
  NBPunch=150;
  IDBug=0;
  
  FileName="Wsaw";
  
  LengthString=8;
  LengthFloat=10;
  LengthInt=5;
}

WsawFile::~WsawFile(){
  Card3s.clear();
  Card4s.clear();
  RMesh=-1;
  RMax=-1;
  NPunch=-1;
  NBPunch=-1;
  IDBug=-1;
  FileName="-1";
  

}

void WsawFile::BuildFields(){

  if (Card3s.size() != Card4s.size()){
    cout<<"Cannot build input file different number of Card3s and Card4s"<<endl;
    cout<<Card3s.size()<<" vs "<<Card4s.size()<<endl;
    return;
  }


  //Inherited from FormatedFile PushLine(Line )
  Line LineOne;
  LineOne.AddField(LengthFloat,RMesh);
  LineOne.AddField(LengthFloat+4,double(RMax));

  LineOne.AddField(LengthInt-2,NPunch);
  LineOne.AddField(LengthInt+2,NBPunch);
  LineOne.AddField(LengthInt,IDBug);


  PushLine(LineOne);

  Line LineTwo;
  LineTwo.AddField(LengthString,FileName);
  PushLine(LineTwo);
    

  for (int i=0;i<(int)Card3s.size();i++){ // sizes of card 3 and 4 vectors must be the same
    PushLine(Card3s[i]);
    PushLine(Card4s[i]);
    
  }
  Line endFile;//the last line with just a -1
  endFile.AddField(LengthString,"-1");
  PushLine(endFile);

}


void WsawFile::AddCard3(double TMC,double TIZC,
			double V0, double A,
			double R0, double RC,
			double VSO){
  Line aLine;
  aLine.AddField(LengthFloat,TMC);
  aLine.AddField(LengthFloat,TIZC);
  aLine.AddField(LengthFloat,V0);
  aLine.AddField(LengthFloat,A);  
  aLine.AddField(LengthFloat,R0);  
  aLine.AddField(LengthFloat,RC);  
  aLine.AddField(LengthFloat,VSO);  
  
  Card3s.push_back(aLine);



}

void WsawFile::AddCard4(double EBIND,double TMP,
			double TL, double TNODE,
			double TIZP, double XJ,
			double XS){
  
  Line aLine;
  aLine.AddField(LengthFloat,EBIND);
  aLine.AddField(LengthFloat,TMP);
  aLine.AddField(LengthFloat,TL);
  aLine.AddField(LengthFloat,TNODE);  
  aLine.AddField(LengthFloat,TIZP);  
  aLine.AddField(LengthFloat,XJ);  
  aLine.AddField(LengthFloat,XS);  
  
  Card4s.push_back(aLine);

}

void WsawFile::CalcCard34(){
  
  if (isPNType){
    for (int i=0;i<(int)theInitialNucleus.GetProtonShells().size();i++){
      
      Shell thisShell = theInitialNucleus.GetProtonShells()[i];
      AddCard3(theInitialNucleus.GetA()-1,theInitialNucleus.GetZ());
      AddCard4(abs(BindingEnergyMapFinal[thisShell.GetName()])
	       ,1,thisShell.Getl(),thisShell.Getn()-1,1,
	       thisShell.GetJ(),0.5);
    }
  
    for (int i=0;i<(int)theInitialNucleus.GetNeutronShells().size();i++){
      
      Shell thisShell = theInitialNucleus.GetNeutronShells()[i];
      AddCard3(theInitialNucleus.GetA()-1,theInitialNucleus.GetZ());
      AddCard4(abs(BindingEnergyMapInitial[thisShell.GetName()]),
	       1,thisShell.Getl(),thisShell.Getn()-1,0,
	       thisShell.GetJ(),0.5);
    }
  } else if (isNPType){
   for (int i=0;i<(int)theInitialNucleus.GetProtonShells().size();i++){
      
      Shell thisShell = theInitialNucleus.GetProtonShells()[i];
      AddCard3(theInitialNucleus.GetA()-1,theInitialNucleus.GetZ());
      AddCard4(abs(BindingEnergyMapInitial[thisShell.GetName()])
	       ,1,thisShell.Getl(),thisShell.Getn()-1,1,
	       thisShell.GetJ(),0.5);
    }
  
    for (int i=0;i<(int)theInitialNucleus.GetNeutronShells().size();i++){
      
      Shell thisShell = theInitialNucleus.GetNeutronShells()[i];
      AddCard3(theInitialNucleus.GetA()-1,theInitialNucleus.GetZ()-1);
      AddCard4(abs(BindingEnergyMapFinal[thisShell.GetName()]),
	       1,thisShell.Getl(),thisShell.Getn()-1,0,
	       thisShell.GetJ(),0.5);
    }
 
  }


}

void WsawFile::SetBindingEnergyFile(string s){




  BindingEnergyFile.open(s.c_str());
  if ( ! BindingEnergyFile.is_open() ){
    cout<<"****Could not find file for binding energies "<<s<<endl;
    return;
  }

  string temp;
  double temp2;
  double temp3;
  vector <int> tempZ;
  vector <int> tempA;
  bool OnInitial =true;

  while (! BindingEnergyFile.eof()) {
    BindingEnergyFile>>temp>>temp2>>temp3;
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
  if ( tempA.size() != 2 && tempZ.size()!= 2){
    //should only ever be initial and final states 
    cout<<"***More than two A,Z pairs found in "<<s<<endl;
  } else if ( BindingEnergyMapInitial.size() == 0 || BindingEnergyMapFinal.size()==0){
    cout<<"****Missing Binding energy information in "<<s<<endl;
  }else {
    theInitialNucleus.SetAZ(tempA[0],tempZ[0]);
    theFinalNucleus.SetAZ(tempA[1],tempZ[1]);
    if ( theFinalNucleus.GetIsoSpinZ()-theInitialNucleus.GetIsoSpinZ() == 1){
      isPNType=false;
      isNPType=true;
    }else if(theFinalNucleus.GetIsoSpinZ()-theInitialNucleus.GetIsoSpinZ() == -1){
      isPNType=true;
      isNPType=false;
    }
      
    CalcCard34();
  }
  
  cout<<"temp z "<<tempZ[0]<<" "<<tempZ[1]<<endl; 
  cout<<theFinalNucleus.GetIsoSpinZ()<<" "<<-theInitialNucleus.GetIsoSpinZ()<<endl;

  cout<<"PN TYPE "<<isPNType<<endl;
  
}
