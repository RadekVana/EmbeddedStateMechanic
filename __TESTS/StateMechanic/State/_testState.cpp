#include "_testState.hpp"

//#include "UnityAddin.h"
//#define UNITY_INCLUDE_SETUP_STUBS
//#define UNITY_WEAK_ATTRIBUTE
#include "unity.h"
#include "MockFullEvent.hpp"
#include "EventTemplate.hpp"
#include "MockStateWithMachineRef.hpp"
#include "MockStateMachine.hpp"
#include "State.hpp"
#include "MockEvHandler.hpp"
#include "MockInfo.hpp"
#include "StateMechanic.hpp"


/******************************************************************************/
//IState is untesteable - to simple, nothing to test
//but i can test IStateWithMachineRef via MockStateM

void IStateTest(){
  UnityBegin(__FILE__);
  
 
  //test machine
  MockStateMachine testMachine;
  
  //test state
  MockStateM st(testMachine);

  //here I can test machine reference (address)
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&testMachine), reinterpret_cast<uint32_t>(&(st.GetParentStateMachine())));

  
}


/******************************************************************************/
//test of handlers, tested methods are primitive and they are "binded"
//just tests auto_ptrs to entry and exit handlers 

//tests:
//  void SinkEntryHandler(auto_ptr<EvHandler> eh); 
//  void SinkExitHandler(auto_ptr<EvHandler> eh); 
//  
//  void FireEntry(auto_ptr<Iinfo> info) const;
//  void FireExit(auto_ptr<Iinfo> info) const;  

//also tests constructor with both handlers supplyed
//  State(IStateMachineWithEventFireRequest& sm, 
//        auto_ptr<EvHandler> entry = auto_ptr<EvHandler>(new DummyEvHandler()), 
//        auto_ptr<EvHandler> exit = auto_ptr<EvHandler>(new DummyEvHandler()));



void StateHandlerTest(){
  UnityBegin(__FILE__);
  
  //test counts
  size_t cntEntry = 0;
  size_t cntExit = 0;
  size_t cntEntry2 = 0;
  size_t cntExit2 = 0;
  
  //handlers
  auto_ptr<EvHandler> entry(new EvHandlerCountingCalls(cntEntry)); 
  auto_ptr<EvHandler> exit(new EvHandlerCountingCalls(cntExit)); 
  auto_ptr<EvHandler> entry2(new EvHandlerCountingCalls(cntEntry2)); 
  auto_ptr<EvHandler> exit2(new EvHandlerCountingCalls(cntExit2)); 
  
  //test machine - needed for state constructor
  MockStateMachine testMachine;  
  
  //create state
  State state(testMachine,entry,exit);
  //test counts
  TEST_ASSERT_EQUAL_UINT32(0,cntEntry);
  TEST_ASSERT_EQUAL_UINT32(0,cntExit);
  TEST_ASSERT_EQUAL_UINT32(0,cntEntry2);
  TEST_ASSERT_EQUAL_UINT32(0,cntExit2);  
    
  state.FireEntry(auto_ptr<Iinfo>(new MockInfo()));
  //test counts
  TEST_ASSERT_EQUAL_UINT32(1,cntEntry);
  TEST_ASSERT_EQUAL_UINT32(0,cntExit);
  TEST_ASSERT_EQUAL_UINT32(0,cntEntry2);
  TEST_ASSERT_EQUAL_UINT32(0,cntExit2); 
  
  state.FireExit(auto_ptr<Iinfo>(new MockInfo()));
  //test counts
  TEST_ASSERT_EQUAL_UINT32(1,cntEntry);
  TEST_ASSERT_EQUAL_UINT32(1,cntExit);
  TEST_ASSERT_EQUAL_UINT32(0,cntEntry2);
  TEST_ASSERT_EQUAL_UINT32(0,cntExit2); 
  
  //change handlers
  state.SinkEntryHandler(entry2);
  state.SinkExitHandler(exit2);
  //test counts did not change
  TEST_ASSERT_EQUAL_UINT32(1,cntEntry);
  TEST_ASSERT_EQUAL_UINT32(1,cntExit);
  TEST_ASSERT_EQUAL_UINT32(0,cntEntry2);
  TEST_ASSERT_EQUAL_UINT32(0,cntExit2); 
  
  state.FireEntry(auto_ptr<Iinfo>(new MockInfo()));
  //test counts
  TEST_ASSERT_EQUAL_UINT32(1,cntEntry);
  TEST_ASSERT_EQUAL_UINT32(1,cntExit);
  TEST_ASSERT_EQUAL_UINT32(1,cntEntry2);
  TEST_ASSERT_EQUAL_UINT32(0,cntExit2); 
  
  state.FireExit(auto_ptr<Iinfo>(new MockInfo()));
  //test counts
  TEST_ASSERT_EQUAL_UINT32(1,cntEntry);
  TEST_ASSERT_EQUAL_UINT32(1,cntExit);
  TEST_ASSERT_EQUAL_UINT32(1,cntEntry2);
  TEST_ASSERT_EQUAL_UINT32(1,cntExit2); 
  
}


//test is Current
void StateIsCurrentTest(){
  UnityBegin(__FILE__); 
  
  // create a state machine. 
  // mock machine is to simple for this, creating "full" version
  StateMachine stateMachine;

  // Whenever we create a state machine, we need to give it an initial state. This
  // is the state which the state machine starts in.
  const State* st1 = stateMachine.CreateInitialState();
  const State* st2 = stateMachine.CreateState();
  
  //st1 is current
  TEST_ASSERT_TRUE(st1->IsCurrent());
  //st2 is not current
  TEST_ASSERT_FALSE(st2->IsCurrent());
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
//Tests of Transitions are complicated
//need "full" Event + be able to access its inner data

//3 methods are tested at once
//I am not sure if it is still unint test, 
//but I am sure I do not want to write same init part 3 times
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


//Transitiont tests:
//  bool TransitionOn(Event& ev) const;  
//  bool TransitionOnTo(Event& ev, const State& to) const; 
//  bool InnerSelfTransitionOn(Event& ev) const;
void State_TransitionTest(){
  UnityBegin(__FILE__); 
  
  
  //test machine - needed for state constructor
  MockStateMachine testMachine;  
  
  //create states
  State st1(testMachine);
  State st2(testMachine);
  
  //state uses Event not IEvent
  MockFullEvent event;
  
  /******************************************************************************/
  //Transition On Event  
  TEST_ASSERT_TRUE(st1.TransitionOn(event));

  
  TEST_ASSERT_EQUAL_PTR(&st1, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st1, event._to); 
  //dummy evh and grd were generated
  TEST_ASSERT_TRUE(NULL != event._evh.get()); 
  TEST_ASSERT_TRUE(NULL != event._grd.get());  
  TEST_ASSERT_FALSE(event._wasInnerTR);
  
  /******************************************************************************/
  //Transition On Event, To State
  TEST_ASSERT_TRUE(st1.TransitionOnTo(event, st2));

  
  TEST_ASSERT_EQUAL_PTR(&st1, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st2, event._to); 
  //dummy evh and grd were generated
  TEST_ASSERT_TRUE(NULL != event._evh.get()); 
  TEST_ASSERT_TRUE(NULL != event._grd.get());
  TEST_ASSERT_FALSE(event._wasInnerTR);
  
  
  /******************************************************************************/
  //InnerSelfTransition On Event 
  TEST_ASSERT_TRUE(st2.InnerSelfTransitionOn(event));

  
  TEST_ASSERT_EQUAL_PTR(&st2, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st2, event._to); 
  //dummy evh and grd were generated
  TEST_ASSERT_TRUE(NULL != event._evh.get()); 
  TEST_ASSERT_TRUE(NULL != event._grd.get());
  TEST_ASSERT_TRUE(event._wasInnerTR); 
}


//TransitionWithHandler tests:
//  bool TransitionOnWith(Event& ev, auto_ptr<EvHandler> evh) const;  
//  bool TransitionOnToWith(Event& ev, const State& to, auto_ptr<EvHandler> evh) const; 
//  bool InnerSelfTransitionOnWith(Event& ev, auto_ptr<EvHandler> evh) const;
void State_TransitionWithHandlerTest(){
  UnityBegin(__FILE__); 
  
  
  //test machine - needed for state constructor
  MockStateMachine testMachine;  
  
  //create states
  State st1(testMachine);
  State st2(testMachine);
  
  //state uses Event not IEvent
  MockFullEvent event;


  auto_ptr<EvHandler> evh;
  EvHandler* evHndlrPtr2bechecked = NULL;  
  /******************************************************************************/
  //Transition On Event, with handler
  evh.reset(new DummyEvHandler());
  evHndlrPtr2bechecked = evh.get();
  
  TEST_ASSERT_TRUE(st1.TransitionOnWith(event, evh));

  
  TEST_ASSERT_EQUAL_PTR(&st1, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st1, event._to); 
  TEST_ASSERT_EQUAL_PTR(evHndlrPtr2bechecked, event._evh.get()); 
  //dummy grd was generated
  TEST_ASSERT_TRUE(NULL != event._grd.get());
  TEST_ASSERT_FALSE(event._wasInnerTR);
  
  /******************************************************************************/
  //Transition On Event, To State, with handler
  evh.reset(new DummyEvHandler());
  evHndlrPtr2bechecked = evh.get();
  
  TEST_ASSERT_TRUE(st1.TransitionOnToWith(event, st2, evh));

  
  TEST_ASSERT_EQUAL_PTR(&st1, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st2, event._to); 
  TEST_ASSERT_EQUAL_PTR(evHndlrPtr2bechecked, event._evh.get()); 
  //dummy grd was generated
  TEST_ASSERT_TRUE(NULL != event._grd.get());
  TEST_ASSERT_FALSE(event._wasInnerTR);
  
  
  /******************************************************************************/
  //InnerSelfTransition On Event, with handler
  evh.reset(new DummyEvHandler());
  evHndlrPtr2bechecked = evh.get();
  
  TEST_ASSERT_TRUE(st2.InnerSelfTransitionOnWith(event, evh));

  
  TEST_ASSERT_EQUAL_PTR(&st2, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st2, event._to); 
  TEST_ASSERT_EQUAL_PTR(evHndlrPtr2bechecked, event._evh.get()); 
  //dummy grd was generated
  TEST_ASSERT_TRUE(NULL != event._grd.get());
  TEST_ASSERT_TRUE(event._wasInnerTR); 
}


//TransitionOnWithGuard tests:
//  bool TransitionOnWithGuard(Event& ev, auto_ptr<TransitionGuard> grd) const; 
//  bool TransitionOnToWithGuard(Event& ev, const State& to, auto_ptr<TransitionGuard> grd) const;
//  bool InnerSelfTransitionOnWithGuard(Event& ev,  auto_ptr<TransitionGuard> grd) const;
void State_TransitionWithGuardTest(){
  UnityBegin(__FILE__); 
  
  
  //test machine - needed for state constructor
  MockStateMachine testMachine;  
  
  //create states
  State st1(testMachine);
  State st2(testMachine);
  
  //state uses Event not IEvent
  MockFullEvent event;
  
  
  auto_ptr<TransitionGuard> grd;
  TransitionGuard* trGrdPtr2bechecked = NULL;  
  /******************************************************************************/
  //Transition On Event, with guard
  grd.reset(new DummyTransitionGuard());
  trGrdPtr2bechecked = grd.get();
  
  TEST_ASSERT_TRUE(st1.TransitionOnWithGuard(event, grd));

  
  TEST_ASSERT_EQUAL_PTR(&st1, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st1, event._to); 
  //dummy evh was generated
  TEST_ASSERT_TRUE(NULL != event._evh.get()); 
  TEST_ASSERT_EQUAL_PTR(trGrdPtr2bechecked, event._grd.get()); 
  TEST_ASSERT_FALSE(event._wasInnerTR);
  
  /******************************************************************************/
  //Transition On Event, To State, with guard
  grd.reset(new DummyTransitionGuard());
  trGrdPtr2bechecked = grd.get();
    
  TEST_ASSERT_TRUE(st1.TransitionOnToWithGuard(event, st2,grd));

  
  TEST_ASSERT_EQUAL_PTR(&st1, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st2, event._to); 
  //dummy evh was generated
  TEST_ASSERT_TRUE(NULL != event._evh.get()); 
  TEST_ASSERT_EQUAL_PTR(trGrdPtr2bechecked, event._grd.get()); 
  TEST_ASSERT_FALSE(event._wasInnerTR);
  
  
  /******************************************************************************/
  //InnerSelfTransition On Event, with guard
  grd.reset(new DummyTransitionGuard());
  trGrdPtr2bechecked = grd.get();
  
  TEST_ASSERT_TRUE(st2.InnerSelfTransitionOnWithGuard(event,grd));

  
  TEST_ASSERT_EQUAL_PTR(&st2, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st2, event._to); 
  //dummy evh was generated
  TEST_ASSERT_TRUE(NULL != event._evh.get()); 
  TEST_ASSERT_EQUAL_PTR(trGrdPtr2bechecked, event._grd.get()); 
  TEST_ASSERT_TRUE(event._wasInnerTR); 
}



//TransitionWithGuardAndHandler tests:
//  bool TransitionOnWithGuardAndHandler(Event& ev,auto_ptr<TransitionGuard> grd, 
//                                       auto_ptr<EvHandler> evh) const; 
//  bool TransitionOnToWithGuardAndHandler(Event& ev, const State& to, 
//                                         auto_ptr<TransitionGuard> grd, auto_ptr<EvHandler> evh) const; 
//  bool InnerSelfTransitionOnWithGuardAndHandler(Event& ev, auto_ptr<TransitionGuard> grd, 
//                                                auto_ptr<EvHandler> evh) const; 
void State_TransitionWithGuardAndHandlerTest(){
  UnityBegin(__FILE__); 
  
  
  //test machine - needed for state constructor
  MockStateMachine testMachine;  
  
  //create states
  State st1(testMachine);
  State st2(testMachine);
  
  //state uses Event not IEvent
  MockFullEvent event;
  
  
  auto_ptr<TransitionGuard> grd;
  TransitionGuard* trGrdPtr2bechecked = NULL;  
  auto_ptr<EvHandler> evh;
  EvHandler* evHndlrPtr2bechecked = NULL;  
  /******************************************************************************/
  //Transition On Event, with guard, with handler
  grd.reset(new DummyTransitionGuard());
  trGrdPtr2bechecked = grd.get();
  evh.reset(new DummyEvHandler());
  evHndlrPtr2bechecked = evh.get();
  
  TEST_ASSERT_TRUE(st1.TransitionOnWithGuardAndHandler(event, grd,evh));

  
  TEST_ASSERT_EQUAL_PTR(&st1, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st1, event._to); 
  TEST_ASSERT_EQUAL_PTR(evHndlrPtr2bechecked, event._evh.get()); 
  TEST_ASSERT_EQUAL_PTR(trGrdPtr2bechecked, event._grd.get()); 
  TEST_ASSERT_FALSE(event._wasInnerTR);
  
  /******************************************************************************/
  //Transition On Event, To State, with guard, with handler
  grd.reset(new DummyTransitionGuard());
  trGrdPtr2bechecked = grd.get();
  evh.reset(new DummyEvHandler());
  evHndlrPtr2bechecked = evh.get();
  
  TEST_ASSERT_TRUE(st1.TransitionOnToWithGuardAndHandler(event, st2,grd,evh));

  
  TEST_ASSERT_EQUAL_PTR(&st1, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st2, event._to); 
  TEST_ASSERT_EQUAL_PTR(evHndlrPtr2bechecked, event._evh.get()); 
  TEST_ASSERT_EQUAL_PTR(trGrdPtr2bechecked, event._grd.get()); 
  TEST_ASSERT_FALSE(event._wasInnerTR);
  
  
  /******************************************************************************/
  //InnerSelfTransition On Event, with guard, with handler
  grd.reset(new DummyTransitionGuard());
  trGrdPtr2bechecked = grd.get();
  evh.reset(new DummyEvHandler());
  evHndlrPtr2bechecked = evh.get();
  
  TEST_ASSERT_TRUE(st2.InnerSelfTransitionOnWithGuardAndHandler(event,grd,evh));

  
  TEST_ASSERT_EQUAL_PTR(&st2, event._from); 
  TEST_ASSERT_EQUAL_PTR(&st2, event._to); 
  TEST_ASSERT_EQUAL_PTR(evHndlrPtr2bechecked, event._evh.get()); 
  TEST_ASSERT_EQUAL_PTR(trGrdPtr2bechecked, event._grd.get()); 
  TEST_ASSERT_TRUE(event._wasInnerTR); 
}
