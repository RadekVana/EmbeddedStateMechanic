#include "_testFiredData.hpp"

//#include "UnityAddin.h"
//#define UNITY_INCLUDE_SETUP_STUBS
//#define UNITY_WEAK_ATTRIBUTE
#include "unity.h"
#include "string2string.h"
#include "FiredData.hpp"
#include "MockState.hpp"
#include "MockEvent.hpp"
#include "MockStruct.hpp"
/******************************************************************************/
//test of Dummy FiredDatas - method Clone

void FiredDataCloneTest(){
  UnityBegin(__FILE__);
  
  IFiredData fd;
  auto_ptr<IFiredData> cln(fd.Clone());
  
  TEST_ASSERT_NOT_NULL(cln.get());
}

template <class T>
static void FiredDataCloneTestT(T val){
  UnityBegin(__FILE__);
  
  FiredData<T> fd(val);
  auto_ptr<IFiredData> cln(fd.Clone());
  
  TEST_ASSERT_NOT_NULL(cln.get());
  
  FiredData<T> *ptr =  reinterpret_cast<FiredData<T>* >(cln.get());
  TEST_ASSERT_TRUE(fd.Get() == ptr->Get());
}

//wrap template
void FiredDataCloneTestInt(){
  FiredDataCloneTestT<int>(0);
}

void FiredDataCloneTestBool(){
  FiredDataCloneTestT<bool>(true);
}

void FiredDataCloneTestDouble(){
  FiredDataCloneTestT<double>(6.6);
}

void FiredDataCloneTestString(){
  FiredDataCloneTestT<string>("xxx");
}

void FiredDataCloneTestStringPtr(){
  string s;
  FiredDataCloneTestT<string*>(&s);
}

void FiredDataCloneTestStruct(){
  mockStruct ms;
  FiredDataCloneTestT<mockStruct>(ms);
}


/******************************************************************************/
//test of virtual void operator()(auto_ptr<Iinfo> info)
template <typename T, size_t size>
void FiredData_DataTest(const T (&tstVals)[size]){
  UnityBegin(__FILE__);
  
  TEST_ASSERT_GREATER_THAN_UINT32_MESSAGE(2,size,"Test used incorrectly, sizeo fo array must be 2 or greater");
  
  size_t i = 0;  
  
//constructor  
  FiredData<T>  fd(tstVals[i]);
  TEST_ASSERT_TRUE_MESSAGE(fd.Get() == tstVals[i], ("Failed index " + to_string(i) +" failed value " + to_string(tstVals[i])).c_str());
   
  for (i = 1; i != size; ++i){
    fd.Set(tstVals[i]);
    TEST_ASSERT_TRUE_MESSAGE(fd.Get() == tstVals[i], ("Failed index " + to_string(i) +" failed value " + to_string(tstVals[i])).c_str());
  }
  
}


void FiredData_DataTestInt(){
  int arr[] = {0,5,8,8,6,5,-4,5,-4};
  FiredData_DataTest(arr);
}

void FiredData_DataTestDouble(){
  double arr[] = {0,3.3,-2,-2,-5.2,999/*,NAN*/};// NAN would fail because NAN != NAN
  FiredData_DataTest(arr);
}

void FiredData_DataTestBool(){
  bool arr[] = {false, true, true, false};
  FiredData_DataTest(arr);
}

void FiredData_DataTestString(){
  string arr[] = {"S", "", "", "SSS"};
  FiredData_DataTest(arr);
}

void FiredData_DataTestStruct(){
  //cannot do mockStruct sArr[] = {{10.0,false},{5.0,true}}; etc
  mockStruct arr[] = {mockStruct(10.0,false),mockStruct(5.0,true),mockStruct(3,0)};
  FiredData_DataTest(arr);

}