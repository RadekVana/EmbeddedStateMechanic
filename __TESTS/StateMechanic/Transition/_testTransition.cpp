#include "_testTransition.hpp"

//#include "UnityAddin.h"
//#define UNITY_INCLUDE_SETUP_STUBS
//#define UNITY_WEAK_ATTRIBUTE
#include "unity.h"
#include "MockTransition.hpp"
#include "MockInfo.hpp"
#include "MockEvHandler.hpp"
#include "TransitionGuard.hpp"//DummyTransitionGuard
#include "MockTransitionGuards.hpp"


/******************************************************************************/
//AbstractTransition should be testet,
//but mock object for AbstractTransition would look like exactly like mock object for InnerTransition
//so tests for AbstractTransition are run on MockInnerTransition

//test of constructor of Transition
void TransitionCtorTest(){
  UnityBegin(__FILE__);
  
  //ctor needs info handler and guard
  auto_ptr<Iinfo> inf (new MockInfo());
  auto_ptr<IEvHandler> evh (new DummyEvHandler());
  auto_ptr<ITransitionGuard> grd (new DummyTransitionGuard());
  
  //save pointers of info handler and guard
  Iinfo* p_inf = inf.get();
  IEvHandler* p_evh = evh.get();
  ITransitionGuard* p_grd = grd.get();
  
  //create transition
  MockTransition transition(inf, evh, grd);
  
  //test of internal data
  TEST_ASSERT_EQUAL_PTR(p_inf, &transition.GetInfo());
  TEST_ASSERT_EQUAL_PTR(p_evh, &transition.GetHndlr());
  TEST_ASSERT_EQUAL_PTR(p_grd, &transition.GetGrd());
}

//test of constructor of InnerTransition
void InnerTransitionCtorTest(){
  UnityBegin(__FILE__);
  
  //ctor needs info handler and guard
  auto_ptr<Iinfo> inf (new MockInfo());
  auto_ptr<IEvHandler> evh (new DummyEvHandler());
  auto_ptr<ITransitionGuard> grd (new DummyTransitionGuard());
  
  //save pointers of info, handler and guard
  Iinfo* p_inf = inf.get();
  IEvHandler* p_evh = evh.get();
  ITransitionGuard* p_grd = grd.get();
  
  //create transition
  MockInnerTransition transition(inf, evh, grd);
  
  //test of internal data
  TEST_ASSERT_EQUAL_PTR(p_inf, &transition.GetInfo());
  TEST_ASSERT_EQUAL_PTR(p_evh, &transition.GetHndlr());
  TEST_ASSERT_EQUAL_PTR(p_grd, &transition.GetGrd());
}

//test of
//virtual auto_ptr<Iinfo> SourceInfo() const;
void TransitionSourceInfoTest(){
  UnityBegin(__FILE__);
  
  //ctor needs info handler and guard
  auto_ptr<Iinfo> inf (new MockInfo());
  
  //save references to dummy data of inf 
  const IState& rFrom = inf->GetFrom();
  const IState& rTo = inf->GetTo();
  const IEvent& rEv = inf->GetEv();
  

  
  //create transition
  MockInnerTransition transition(inf, 
                                 auto_ptr<IEvHandler> (new DummyEvHandler()), 
                                 auto_ptr<ITransitionGuard> (new DummyTransitionGuard()));
  
  //test of internal data
  auto_ptr<Iinfo> sourcedInfo(transition.SourceInfo());
  
  //test if cloned info refers to same states and event
  TEST_ASSERT_EQUAL_PTR(&rFrom, &sourcedInfo->GetFrom());
  TEST_ASSERT_EQUAL_PTR(&rTo, &sourcedInfo->GetTo());
  TEST_ASSERT_EQUAL_PTR(&rEv, &sourcedInfo->GetEv());
}

//test od asigment operator
//asigment operatoris using copy constructor
//copy constructor is using swap
//swap does all work, rest is trivial -> test od asigment operator is sufficient
void TransitionAsigmentTest(){
  UnityBegin(__FILE__);
  
  int someInt = 123;

  //create transition
  MockInnerTransition transition(auto_ptr<Iinfo> (new MockInfo()), 
                                 auto_ptr<IEvHandler> (new EvHandlerWithPInt(&someInt)), 
                                 auto_ptr<ITransitionGuard> (new GuardWithPInt(&someInt)));
  MockInnerTransition copyOfTransition = transition;
  
  //test if copied object contains same internal data
  //info
  TEST_ASSERT_EQUAL_PTR(&transition.GetInfo().GetFrom(), &copyOfTransition.GetInfo().GetFrom());
  TEST_ASSERT_EQUAL_PTR(&transition.GetInfo().GetTo()  , &copyOfTransition.GetInfo().GetTo());
  TEST_ASSERT_EQUAL_PTR(&transition.GetInfo().GetEv()  , &copyOfTransition.GetInfo().GetEv());
  //handler
  TEST_ASSERT_EQUAL_PTR(&someInt, (reinterpret_cast<EvHandlerWithPInt&>(transition.GetHndlr())).PInt);
  TEST_ASSERT_EQUAL_PTR(&someInt, (reinterpret_cast<EvHandlerWithPInt&>(copyOfTransition.GetHndlr())).PInt);
  //guard
  TEST_ASSERT_EQUAL_PTR(&someInt, (reinterpret_cast<GuardWithPInt&>(transition.GetGrd())).PInt);
  TEST_ASSERT_EQUAL_PTR(&someInt, (reinterpret_cast<GuardWithPInt&>(copyOfTransition.GetGrd())).PInt);
 
}