//
// Line class.  Lines hold feilds
//


#include "Field.hh"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;
class Line {
  
public:
  Line();
  ~Line();
  
  
  void AddField(int length,double value);
  void AddField(int length,string value);
  void AddField(int length,int value);
  
  void Write(ofstream&);


private:

  vector <int> theOrder;
  
  vector <Field<double> > dFields;
  int dFieldsFlag;

  vector <Field<string> > sFields;
  int sFieldsFlag;
  vector <Field<int> > iFields; //Trade mark Apple inc. 2050
  int iFieldsFlag;
  
  bool CheckLength(int l,double v);
  bool CheckLength(int l,int v);
  
};
