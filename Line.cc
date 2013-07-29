



#include "Line.hh"



Line::Line(){
  iFieldsFlag=0;
  dFieldsFlag=1;
  sFieldsFlag=2;
}


Line::~Line(){


}





void Line::AddField(int length,double value){
  Field<double> a(length,value);
  dFields.push_back(a);

  theOrder.push_back(dFieldsFlag);


}

void Line::AddField(int length,int value){
  Field<int> a(length,value) ;
  iFields.push_back(a);

  theOrder.push_back(iFieldsFlag);


}

void Line::AddField(int length,string value){
  Field<string>a(length,value);
  sFields.push_back(a);

  theOrder.push_back(sFieldsFlag);


}

bool Line::CheckLength(int l,double v){
  stringstream s;
  s<<v;
  if (s.str().size()>l){
    cout<<"***Value to big for character spacing: "<<v<<endl;
    return false;
  }else{
    return true;
  }
}
bool Line::CheckLength(int l,int v){
  stringstream s;
  s<<v;
  if (s.str().size() > l){
    cout<<"***Value to big for character spacing: "<<v<<endl;
    return false;
  }else{
    return true;
  }
}


void Line::Write(ofstream &file){
  
  for (int i=0;i<theOrder.size();i++){
    if (theOrder[i] == iFieldsFlag){//printing INTs
      int l=iFields.front().NumCharacters;
      int n=iFields.front().Value;

      if (CheckLength(l,n)){
	file<<left<<setprecision(l)<<setw(l)<<iFields.front().Value;
      } //still remove that field just don't print it.
      iFields.erase(iFields.begin());
    }else if (theOrder[i] == dFieldsFlag){//printing floats 
      int l = dFields.front().NumCharacters;
      double v=dFields.front().Value;
      if (int(v) == v&&CheckLength(l+1,v)){ // like 20 not 20.1
	stringstream s;s<<v<<".";
	file<<left<<setprecision(l)<<setw(l)<<s.str();
      } else if ( int(v)!=v&&CheckLength(l,v)){
	file<<left<<setprecision(l)<<setw(l)<<v;
      }
      //file<<setprecision(l-1)<<setw(l)<<v;
      dFields.erase(dFields.begin());
      
    }else if (theOrder[i] == sFieldsFlag){
      int l =sFields.front().NumCharacters;
      string s=sFields.front().Value;
      if (s.size()>l){
	cout<<"***Value to big for character spacing: "<<s<<endl;
      }else {
	file<<left<<setw(l)<<sFields.front().Value;
      }
      sFields.erase(sFields.begin());

    }    
  
  }

}
