//
//  Base Class for fortan style input file generator
//  
//

#ifndef __FORMATEDFILE__hh
#define __FORMATEDFILE__hh

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

#include "Line.hh"

using namespace std; 

class FormatedFile {


public: 
  FormatedFile();
  ~FormatedFile();
  
  void PushLine(Line &);


  void OpenFile(string );

  void Write();


private:

  vector <Line> theLines; // The lines in the order to be printed
  
  ofstream theOutputFile;
  
  
};

#endif





