#include "_testEvHandler.hpp"

//#include "UnityAddin.h"
//#define UNITY_INCLUDE_SETUP_STUBS
//#define UNITY_WEAK_ATTRIBUTE
#include "unity.h"
#include "string2string.h"

#include "EvHandler.hpp"
#include "MockState.hpp"
#include "MockEvent.hpp"
#include "MockStruct.hpp"
#include "MockEvHandler.hpp"
/******************************************************************************/
//test of Dummy EvHandlers - method Clone

void EvHandlerCloneTest(){
  UnityBegin(__FILE__);
  
  DummyEvHandler eh;
  auto_ptr<IEvHandler> cln(eh.Clone());
  
  TEST_ASSERT_NOT_NULL(cln.get());
}

template <class T>
static void EvHandlerCloneTestT(){
  UnityBegin(__FILE__);
  
  DummyEvHandlerWithData<T> eh;
  auto_ptr<IEvHandler> cln(eh.Clone());
  
  TEST_ASSERT_NOT_NULL(cln.get());
}

//wrap template
void EvHandlerCloneTestInt(){
  EvHandlerCloneTestT<int>();
}

void EvHandlerCloneTestBool(){
  EvHandlerCloneTestT<bool>();
}

void EvHandlerCloneTestDouble(){
  EvHandlerCloneTestT<double>();
}

void EvHandlerCloneTestString(){
  EvHandlerCloneTestT<string>();
}

void EvHandlerCloneTestStringPrt(){
  EvHandlerCloneTestT<string*>();
}

void EvHandlerCloneTestStruct(){
  EvHandlerCloneTestT<mockStruct>();
}


/******************************************************************************/
//test of virtual void operator()(auto_ptr<Iinfo> info)
template <typename T, size_t size>
void EvHandlerDataTest(const T (&tstVals)[size]){
  UnityBegin(__FILE__);
  
  MockState ms;
  MockEventWithData<T> me;
  
  T cmp;//handler changes this val
  
  //iterator is not used, index is needed
  for (size_t i = 0; i != size; ++i){
    auto_ptr<Iinfo > info(new Info<T> (ms,ms,me,tstVals[i]));
    
    EvHandlerSettingVar<T> hndlr(cmp);
    //directly setting hndl
    hndlr(info);
    TEST_ASSERT_TRUE_MESSAGE(cmp == tstVals[i], ("Failed index " + to_string(i) +" failed value " + to_string(tstVals[i])).c_str());
  }
  
}


void EvHandlerDataTestInt(){
  int arr[] = {0,5,8,8,6,5,-4,5,-4};
  EvHandlerDataTest(arr);
}

void EvHandlerDataTestDouble(){
  double arr[] = {0,3.3,-2,-2,-5.2,999/*,NAN*/};// NAN would fail because NAN != NAN
  EvHandlerDataTest(arr);
}

void EvHandlerDataTestBool(){
  bool arr[] = {false, true, true, false};
  EvHandlerDataTest(arr);
}

void EvHandlerDataTestString(){
  string arr[] = {"S", "", "", "SSS"};
 // EvHandlerDataTestSrting(arr);
  EvHandlerDataTest(arr);
}

void EvHandlerDataTestStruct(){
  //cannot do mockStruct sArr[] = {{10.0,false},{5.0,true}}; etc
  mockStruct arr[] = {mockStruct(10.0,false),mockStruct(5.0,true),mockStruct(3,0)};
  EvHandlerDataTest(arr);

}