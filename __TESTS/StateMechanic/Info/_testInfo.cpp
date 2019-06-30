#include "_testInfo.hpp"

//#include "UnityAddin.h"
//#define UNITY_INCLUDE_SETUP_STUBS
//#define UNITY_WEAK_ATTRIBUTE
#include "unity.h"

#include "string2string.h"

#include "Iinfo.hpp"
#include "InfoTemplate.hpp"
#include "IFiredData.hpp"
#include "FiredData.hpp"

#include "MockState.hpp"
#include "MockEvent.hpp"
#include "MockStruct.hpp"
/******************************************************************************/

void IinfoTest(){
  UnityBegin(__FILE__);
  
  //test event
  MockEvent ev;
  
  //test states
  const MockState from;
  const MockState to;
  
  //create info
  Iinfo inf(from,to,ev);
  
  
  //test validity of references
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&from),   reinterpret_cast<uint32_t>(&(inf.GetFrom())));
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&to),     reinterpret_cast<uint32_t>(&(inf.GetTo())));
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&ev),     reinterpret_cast<uint32_t>(&(inf.GetEv())));
};

template <class T>
void TInfoTest(T data, T data2){
  UnityBegin(__FILE__);
  
  //test event
  MockEventWithData<T> ev;
  
  //test states
  const MockState from;
  const MockState to;
  
  //create info
  Info<T> inf(from, to, ev, data);
  
  
  //test validity of references
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&from),   reinterpret_cast<uint32_t>(&(inf.GetFrom())));
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&to),     reinterpret_cast<uint32_t>(&(inf.GetTo())));
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&ev),     reinterpret_cast<uint32_t>(&(inf.GetEv())));
  
  //test validity of data
  TEST_ASSERT_TRUE_MESSAGE(data == inf.GetData(), ("Failed data are" + to_string(inf.GetData()) +
                                                   ", data should be" + to_string(data)).c_str());
  inf.SetData(data2);
  TEST_ASSERT_TRUE_MESSAGE(data2 == inf.GetData(), ("Failed data are" + to_string(inf.GetData()) +
                                                   ", data should be" + to_string(data2)).c_str());
};

void InfoTestInt(){
  TInfoTest<int>(0,10);
  TInfoTest<int>(0,0);
  TInfoTest<int>(-1,8);
  TInfoTest<int>(5,-1);
}

void InfoTestBool(){
  TInfoTest<bool>(true,false);
  TInfoTest<bool>(false,true);
  TInfoTest<bool>(true,true); 
  TInfoTest<bool>(false,false);
}

void InfoTestDouble(){
  TInfoTest<double>(0,10.2);
  TInfoTest<double>(0,0);
  TInfoTest<double>(-1.0,8.1);
  TInfoTest<double>(5.4,-1.4);  
}

void InfoTestString(){
  string empty;
  TInfoTest<string>("something","something else");
  TInfoTest<string>(empty,empty);
  TInfoTest<string>(empty,"something");
  TInfoTest<string>("something",empty);    
}


void InfoTestStruct(){
  mockStruct s1;
  mockStruct s2(2,false);
  TInfoTest<mockStruct>(s1,s1);
  TInfoTest<mockStruct>(s1,s2);
  TInfoTest<mockStruct>(s2,s1);
}