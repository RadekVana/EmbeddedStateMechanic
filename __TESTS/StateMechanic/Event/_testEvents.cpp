#include "_testEvents.hpp"

//#include "UnityAddin.h"
//#define UNITY_INCLUDE_SETUP_STUBS
//#define UNITY_WEAK_ATTRIBUTE
#include "unity.h"
#include "Event.hpp"
#include "EventTemplate.hpp"
#include "MockStateWithMachineRef.hpp"
#include "MockStruct.hpp"
#include "MockStateMachine.hpp"


/******************************************************************************/
//test of method CreateIinfo is handled by integration tests


/******************************************************************************/
//test of public method
//virtual bool TryFire();

void EventTest(){
  UnityBegin(__FILE__);
  
  //test event
  Event testEv;
  
  //fireing event with no transition must return false
  TEST_ASSERT_FALSE(testEv.TryFire());
  
  //test machine
  MockStateMachine testMachine0;
  MockStateMachine testMachine1;
  
  //test states
  const MockStateM st_0_mchn_0(testMachine0);
  const MockStateM st_1_mchn_0(testMachine0);
  const MockStateM st_0_mchn_1(testMachine1);

  //empty handler and guard
  auto_ptr<EvHandler> evh;
  auto_ptr<TransitionGuard> grd;
  
  //cannot ad transitions with different state machine
  TEST_ASSERT_FALSE(testEv.AddTransition(st_0_mchn_0, st_0_mchn_1, evh, grd));
  
  //first added transition
  TEST_ASSERT_TRUE(testEv.AddTransition(st_0_mchn_0, st_1_mchn_0, evh, grd)); 
  
  //first added transition has different machine - cannot be added
  TEST_ASSERT_FALSE(testEv.AddTransition(st_0_mchn_1, st_0_mchn_1, evh, grd));
  
   //first added transition has same state machine - can be added
  TEST_ASSERT_TRUE(testEv.AddInnerTransition(st_1_mchn_0, evh, grd)); 
  
  //first added transition has different machine - cannot be added
  TEST_ASSERT_FALSE(testEv.AddInnerTransition(st_0_mchn_1, evh, grd)); 
  
  //event with defined transition can be fired
  TEST_ASSERT_TRUE(testEv.TryFire());
  
}

/******************************************************************************/
//generic version
template <class T>
static void EventTestT(T val){
  UnityBegin(__FILE__);
  
  //test event
  EventWithData<T>    testEv;
  
  //fireing event with no transition must return false
  TEST_ASSERT_FALSE(testEv.TryFire(val));
  
  //test machine
  MockStateMachine testMachine0;
  MockStateMachine testMachine1;
  
  //test states
  const MockStateM st_0_mchn_0(testMachine0);
  const MockStateM st_1_mchn_0(testMachine0);
  const MockStateM st_0_mchn_1(testMachine1);

  //empty handler and guard
  auto_ptr<EvHandlerWithData<T> > evh;
  auto_ptr<TransitionGuardWithData<T> > grd;
  
  //cannot ad transitions with different state machine
  TEST_ASSERT_FALSE(testEv.AddTransition(st_0_mchn_0, st_0_mchn_1, evh, grd));
  
  //first added transition
  TEST_ASSERT_TRUE(testEv.AddTransition(st_0_mchn_0, st_1_mchn_0, evh, grd)); 
  
  //first added transition has different machine - cannot be added
  TEST_ASSERT_FALSE(testEv.AddTransition(st_0_mchn_1, st_0_mchn_1, evh, grd));
  
   //first added transition has same state machine - can be added
  TEST_ASSERT_TRUE(testEv.AddInnerTransition(st_1_mchn_0, evh, grd)); 
  
  //first added transition has different machine - cannot be added
  TEST_ASSERT_FALSE(testEv.AddInnerTransition(st_0_mchn_1, evh, grd)); 
  
  //event with defined transition can be fired
  TEST_ASSERT_TRUE(testEv.TryFire(val));
  
}

void EventTestInt(){
  EventTestT<int>(0);
  EventTestT<int>(-850);
  EventTestT<int>(1000);
}

void EventTestBool(){
  EventTestT<bool>(true);
  EventTestT<bool>(false);
}

void EventTestDouble(){
  EventTestT<double>(0);
  EventTestT<double>(-850.2);
  EventTestT<double>(1000.2);
}


void EventTestString(){
  EventTestT<string>("abc");
  EventTestT<string>("");
  string s;
  EventTestT<string>(s);
  s = "XXX";
  EventTestT<string>(s);  
}



void EventTestStruct(){
  EventTestT<mockStruct>(mockStruct());
  mockStruct t1;
  EventTestT<mockStruct>(t1);
  EventTestT<mockStruct*>(&t1);
}