
#ifndef _MY_FUNCTIONOID_
#define _MY_FUNCTIONOID_

#include "stdint.h"
#include <vector>
//
////v sablone muze byt misto
////typename i class - nijak se to nelisi
//
//template<typename F>
//class base_functionoid;
//
//template<typename Return, typename Input>
//class base_functionoid<Return(Input)>
//{
//public:
//   virtual Return operator()(Input I)=0;// { return I; } 
//};
//
//template<typename Return>
//class base_functionoid<Return()>
//{
//public:
//   virtual Return operator()()=0;// { return I; } 
//};
//
////na rozdil od ukayatele na fci muye mit konstuktor a lze ho inlineovat


//slouzi k predavani dat
class fnc_void {
public:
  //volam jako fci
  virtual void operator()(){}
};

class fnc_u08 {
public:
  //volam jako fci
  virtual void operator()(uint8_t){}
};

class fnc_bool {
public:
  //volam jako fci
  virtual void operator()(bool){}
};

class fnc_i32 {
public:
  //volam jako fci
  virtual void operator()(int32_t){}//pouziji jako DUMMY
};

class fnc_vect_u08_ref {
public:
  //volam jako fci
  virtual void operator()(vector<uint8_t>&) = 0;
};

class bool_fnc_vect_u08_ref {
public:
  //volam jako fci
  virtual bool operator()(vector<uint8_t>&) = 0;
};
extern fnc_i32 DummyCallback;
#endif
