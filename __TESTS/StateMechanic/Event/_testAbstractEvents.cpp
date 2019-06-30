#include "_testAbstractEvents.hpp"

//#include "UnityAddin.h"
//#define UNITY_INCLUDE_SETUP_STUBS
//#define UNITY_WEAK_ATTRIBUTE
#include "unity.h"
#include "MockEvent.hpp"
#include "MockState.hpp"


/******************************************************************************/
//test of public method
//auto_ptr<Iinfo> CreateBaseIinfo(const IState& from, const IState& to) const;

void AbstractEventTest(){
  UnityBegin(__FILE__);
  
  //test event
  MockEvent testEv;
  
  //test states
  const MockState from;
  const MockState to;
  const MockState fromto;
  
  //2 states test
  auto_ptr<Iinfo> inf = testEv.CreateBaseIinfo(from, to);
  //test if from and to addreses match  
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&from), reinterpret_cast<uint32_t>(&(inf->GetFrom())));
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&to),   reinterpret_cast<uint32_t>(&(inf->GetTo())));
  //test event addres
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&testEv),reinterpret_cast<uint32_t>(&(inf->GetEv())));
  

  //single state test
  auto_ptr<Iinfo> inf2 = testEv.CreateBaseIinfo(fromto, fromto);
  //test if fromto address match
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&fromto), reinterpret_cast<uint32_t>(&(inf2->GetFrom())));  
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&fromto), reinterpret_cast<uint32_t>(&(inf2->GetTo())));
  //test event addres
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&testEv),reinterpret_cast<uint32_t>(&(inf2->GetEv())));  

}