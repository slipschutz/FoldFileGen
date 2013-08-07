//
//
//  Manager for displaying erros and debug statements
//  
//
//
#ifndef __ERRORMANAGER_HH
#define __ERRORMANAGER_HH


#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class ErrorManager{
public:
  void BoxPrint(string);

private:
  vector<int> GetSpaces(string);
  int FindSpot(vector<int>,int);
  string GetRepeat(char c,int n);

};
#endif
