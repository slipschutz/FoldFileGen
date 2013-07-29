

#ifndef __FIELD__hh
#define __FIELD__hh


template <class T> class Field  {

public:

  Field(int n, T v);
  Field();
  ~Field();

  T Value;
  int NumCharacters;
};

template <class T> Field<T>::Field(int n, T v) : Value(v),NumCharacters(n){
  ;;
}



template <class T> Field<T>::~Field(){
  NumCharacters = -1;
  

}
#endif
