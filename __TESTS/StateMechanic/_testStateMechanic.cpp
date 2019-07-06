#include "_testStateMechanic.hpp"
#include "Event.hpp"
#include "EventTemplate.hpp"
//#include "UnityAddin.h"
//#define UNITY_INCLUDE_SETUP_STUBS
//#define UNITY_WEAK_ATTRIBUTE
#include "unity.h"

#include "StateMechanic.hpp"
#include "MockTransitionGuards.hpp"
#include "_testEventHandlers.hpp"





/******************************************************************************/
//Here's a quick introduction to the basics. We'll create a state machine to 
//represent a drinks dispenser.
void StateMechanic_QuickStart(){
  UnityBegin(__FILE__); 
  
  // First off, create a state machine. 
  StateMachine stateMachine;

  // Whenever we create a state machine, we need to give it an initial state. This
  // is the state which the state machine starts in.
  const State* awaitingMoney = stateMachine.CreateInitialState();

  // We then add the other states in the staate machine.
  const State* awaitingSelection = stateMachine.CreateState();
  const State* dispensing = stateMachine.CreateState();

  // Next, we'll create the events.
  Event moneyReceived;
  Event selectionReceived;
  Event dispenseComplete;

  // Finally, we create transitions between our states based on these events.
  // in my implementation transmitions are registred into events

  TEST_ASSERT_TRUE(awaitingMoney->TransitionOnTo(moneyReceived, *awaitingSelection));
  TEST_ASSERT_TRUE(awaitingSelection->TransitionOnTo(selectionReceived, *dispensing));
  TEST_ASSERT_TRUE(dispensing->TransitionOnTo(dispenseComplete,*awaitingMoney));

  // See that the state machine starts in the initial state
  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(awaitingMoney), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
  TEST_ASSERT_TRUE(awaitingMoney->IsCurrent());


  // You can try and fire the event - this won't throw on failure,
  // but will return a bool indicating whether it succeeded.
  TEST_ASSERT_TRUE(moneyReceived.TryFire());

  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(awaitingSelection), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
}




  

//A state is allowed to transition to itself. This is a useful way of running 
//some code when an event is fired, but only if the state machine is in a 
//particular state. By default, both the exit and entry handlers will also be 
//invoked in this case. If you don't want this, then create an inner self 
//transition instead.
void StateMechanic_InnerSelfTransitions(){
  UnityBegin(__FILE__); 
  
  // First off, create a state machine. 
  StateMachine stateMachine;

  // Whenever we create a state machine, we need to give it an initial state. This
  // is the state which the state machine starts in.
  const State* state = stateMachine.CreateInitialState(auto_ptr<EvHandler>(new TestEvHandler),auto_ptr<EvHandler>(new TestEvHandler));


  // Next, we'll create the events.
  Event innerSelfEvent;
  Event event;


  // Finally, we create transitions between our states based on these events.
  // in my implementation transmitions are registred into events

  TEST_ASSERT_TRUE(state->TransitionOn(event));
  TEST_ASSERT_TRUE(state->InnerSelfTransitionOn(innerSelfEvent));


  // See that the state machine starts in the initial state
  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(state), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
  TEST_ASSERT_TRUE(state->IsCurrent());


  TEST_ASSERT_EQUAL_UINT32(0,TestEvHandler::static_call_count );
  TEST_ASSERT_TRUE(innerSelfEvent.TryFire());
  TEST_ASSERT_EQUAL_UINT32(0, TestEvHandler::static_call_count);
  TEST_ASSERT_TRUE(event.TryFire());
  TEST_ASSERT_EQUAL_UINT32(2, TestEvHandler::static_call_count);

  // See that the state machine state did not change
  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(state), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
}

//You can associate data with particular events. When you fire the event, you 
//also provide the data.

void StateMechanic_EventData(){
  UnityBegin(__FILE__); 
  
  // create a state machine. 
  StateMachine stateMachine;

  // initial state
  const State* state = stateMachine.CreateInitialState();


  // an event with int data
  EventWithData<int> event;
  EventWithData<int> innerSelfEvent;

  // create transitions
  TEST_ASSERT_TRUE(state->DataTransitionOnToWith(event,*state, auto_ptr<EvHandlerWithData<int> >(new TestIntEvHandler)));
  TEST_ASSERT_TRUE(state->InnerSelfDataTransitionOnWith(innerSelfEvent, auto_ptr<EvHandlerWithData<int> >(new TestIntEvHandler)));


  // See that the state machine starts in the initial state
  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(state), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
  TEST_ASSERT_TRUE(state->IsCurrent());


  TEST_ASSERT_EQUAL_INT32(0, TestIntEvHandler::static_int);
  TEST_ASSERT_TRUE(innerSelfEvent.TryFire(3));
  TEST_ASSERT_EQUAL_INT32(3, TestIntEvHandler::static_int);
  TEST_ASSERT_TRUE(event.TryFire(5));
  TEST_ASSERT_EQUAL_INT32(5, TestIntEvHandler::static_int);

  // See that the state machine state did not change
  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(state), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
}


//Sometimes life isn't as simple as always transitioning from state A to state B 
//on an event. Sometimes when event E is fired you might transition from A to B 
//in some cases, but from A to C in others.
//
//One way of achieving this is with transition guards. A transition guard is a 
//delegate which is controls whether a particular transition can take place. If 
//it can't, then any other transitions from the current state on that event are tried.
//
//Note that the order in which transitions are added to a state is important here. 
//Transitions are tried in the order that they were added, until either a transition 
//succeeds or we run out of transitions (in which case the event fire will fail).

void StateMechanic_TransitionGuards(){
  UnityBegin(__FILE__); 
  
  bool allowTransitionToStateB = false;
  {
    // create a state machine. 
    StateMachine stateMachine;

    // initial state
    const State* StateA = stateMachine.CreateInitialState();
    const State* StateB = stateMachine.CreateState();
    const State* StateC = stateMachine.CreateState();
    // an event 
    Event eventE;


    // create transitions 
    //with guard to B
    TEST_ASSERT_TRUE(StateA->TransitionOnToWithGuard(eventE,*StateB, auto_ptr<TransitionGuard>(new BoolGuard(allowTransitionToStateB))));
    //with no guard to C
    TEST_ASSERT_TRUE(StateA->TransitionOnTo(eventE,*StateC));


    // See that the state machine starts in the initial state
    TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateA), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
    TEST_ASSERT_TRUE(StateA->IsCurrent());


    TEST_ASSERT_TRUE(eventE.TryFire());

    //Guard was false, StateC should be active
    TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateC), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
  }
  {
    allowTransitionToStateB = true;
    // create a state machine. 
    StateMachine stateMachine;

    // initial state
    const State* StateA = stateMachine.CreateInitialState();
    const State* StateB = stateMachine.CreateState();
    const State* StateC = stateMachine.CreateState();
    // an event 
    Event eventE;


    // create transitions 
    //with guard to B
    TEST_ASSERT_TRUE(StateA->TransitionOnToWithGuard(eventE,*StateB, auto_ptr<TransitionGuard>(new BoolGuard(allowTransitionToStateB))));
    //with no guard to C
    TEST_ASSERT_TRUE(StateA->TransitionOnTo(eventE,*StateC));


    // See that the state machine starts in the initial state
    TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateA), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
    TEST_ASSERT_TRUE(StateA->IsCurrent());


    TEST_ASSERT_TRUE(eventE.TryFire());

    //Guard was true, StateB should be active
    TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateB), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
  }  
 }

void StateMechanic_TransitionGuardsWithData(){
  UnityBegin(__FILE__); 

  {
    // create a state machine. 
    StateMachine stateMachine;

    // initial state
    const State* StateA = stateMachine.CreateInitialState();
    const State* StateB = stateMachine.CreateState();
    const State* StateC = stateMachine.CreateState();
    // an event 
    EventWithData<bool> eventE;


    // create transitions 
    //with guard to B
    TEST_ASSERT_TRUE(StateA->DataTransitionOnToWithGuard(eventE,*StateB, auto_ptr<TransitionGuardWithData<bool> >(new EnableBoolGuard())));
    //with no guard to C
    TEST_ASSERT_TRUE(StateA->DataTransitionOnTo(eventE,*StateC));


    // See that the state machine starts in the initial state
    TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateA), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
    TEST_ASSERT_TRUE(StateA->IsCurrent());


    TEST_ASSERT_TRUE(eventE.TryFire(false));

    //Guard was false, StateC should be active
    TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateC), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
  }
  {
    // create a state machine. 
    StateMachine stateMachine;

    // initial state
    const State* StateA = stateMachine.CreateInitialState();
    const State* StateB = stateMachine.CreateState();
    const State* StateC = stateMachine.CreateState();
    // an event 
    EventWithData<bool> eventE;


    // create transitions 
    //with guard to B
    TEST_ASSERT_TRUE(StateA->DataTransitionOnToWithGuard(eventE,*StateB, auto_ptr<TransitionGuardWithData<bool> >(new EnableBoolGuard())));
    //with no guard to C
    TEST_ASSERT_TRUE(StateA->DataTransitionOnTo(eventE,*StateC));


    // See that the state machine starts in the initial state
    TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateA), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
    TEST_ASSERT_TRUE(StateA->IsCurrent());


    TEST_ASSERT_TRUE(eventE.TryFire(true));


    //Guard was true, StateB should be active
    TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateB), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
  }  
 }


void StateMechanic_RecursiveTransition(){
  UnityBegin(__FILE__); 
 
  //logging vectors
  vector<TestData>      DataFromTests;
  vector<int>           Calls;
  
  // create a state machine. 
  StateMachine stateMachine;
  // initial state
  State* StateA = stateMachine.CreateInitialState();
  // other states
  State* StateB = stateMachine.CreateState();
  State* StateC = stateMachine.CreateState();
  State* StateD = stateMachine.CreateState();
  State* StateE = stateMachine.CreateState();
  // events
  Event eventA;
  Event eventB;
  Event eventC;
  Event eventD;
  
  auto_ptr<EvHandler> toC (new TestEvHandlerFireingAnEv (eventB,0,Calls));
  auto_ptr<EvHandler> toD (new TestEvHandlerFireingAnEv (eventC,1,Calls));
  auto_ptr<EvHandler> toE (new TestEvHandlerFireingAnEv (eventD,2,Calls));
  
  auto_ptr<EvHandler> trEv (new LoggingEvHandler ("transition",DataFromTests));
  auto_ptr<EvHandler> erEv (new LoggingEvHandler ("transition not found",DataFromTests));
  stateMachine.SinkTransitionEv(trEv);
  stateMachine.SinkTransitionNotFoundEv(erEv);
  
  //toB is fired down
  StateA->SinkExitHandler(toC);//to C
  StateB->SinkEntryHandler(toD); //to D
  //toE fired from transition
  
  // create simple transitions 
  TEST_ASSERT_TRUE(StateA->TransitionOnTo(eventA,*StateB));
  TEST_ASSERT_TRUE(StateB->TransitionOnToWith(eventB,*StateC,toE));
  TEST_ASSERT_TRUE(StateC->TransitionOnTo(eventC,*StateD));
  TEST_ASSERT_TRUE(StateD->TransitionOnTo(eventD,*StateE));



  // See that the state machine starts in the initial state
  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateA), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
  TEST_ASSERT_TRUE(StateA->IsCurrent());


  TEST_ASSERT_TRUE(eventA.TryFire());

  //Machine should be in StateE
  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateE), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));

  //3 handlers were used
  //toC toD and toE
  TEST_ASSERT_EQUAL_UINT32(3,Calls.size());
  for (size_t i = 0; i < Calls.size(); ++i)
    TEST_ASSERT_EQUAL_UINT32(i,Calls[i]);
  
  //4 transitions in total
  TEST_ASSERT_EQUAL_UINT32(4,DataFromTests.size());
  for (size_t i = 0; i < DataFromTests.size(); ++i){
    //name must be transition
    TEST_ASSERT_EQUAL_STRING("transition",DataFromTests[i].HandlerName.c_str());
  }  
  
  //from StateA to StateB over eventA  
  size_t pos = 0;
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateA),  DataFromTests[pos].AddrFrom);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateB),  DataFromTests[pos].AddrTo);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&eventA), DataFromTests[pos].AddrEv);
  
  //from StateB to StateC over eventB  
  ++pos;
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateB),  DataFromTests[pos].AddrFrom);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateC),  DataFromTests[pos].AddrTo);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&eventB), DataFromTests[pos].AddrEv);

  //from StateC to StateD over eventC 
  ++pos;
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateC),  DataFromTests[pos].AddrFrom);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateD),  DataFromTests[pos].AddrTo);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&eventC), DataFromTests[pos].AddrEv);

  //from StateD to StateE over eventD  
  ++pos;
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateD),  DataFromTests[pos].AddrFrom);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateE),  DataFromTests[pos].AddrTo);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&eventD), DataFromTests[pos].AddrEv);  
}

void StateMechanic_RecursiveTransition_allButFirstFiredAtOnce(){
  UnityBegin(__FILE__); 
  
  //logging vectors
  vector<TestData> DataFromTests;
  
  // create a state machine. 
  StateMachine stateMachine;
  // initial state
  State* StateA = stateMachine.CreateInitialState();
  // other states
  State* StateB = stateMachine.CreateState();
  State* StateC = stateMachine.CreateState();
  State* StateD = stateMachine.CreateState();
  State* StateE = stateMachine.CreateState();
  // events
  Event eventA;
  Event eventB;
  Event eventC;
  Event eventD;
  
  //this will fire eventB, eventC and eventD at once
  //need pointer to be able to inicialize this handler
  TestEvHandlerFireingVectorOfEv *ptrToInit = new TestEvHandlerFireingVectorOfEv();
  ptrToInit->AddEv(eventB);
  ptrToInit->AddEv(eventC);
  ptrToInit->AddEv(eventD);
  auto_ptr<EvHandler> FireAllHandler (ptrToInit);
  
  auto_ptr<EvHandler> trEv (new LoggingEvHandler ("transition",DataFromTests));
  auto_ptr<EvHandler> erEv (new LoggingEvHandler ("transition not found",DataFromTests));
  stateMachine.SinkTransitionEv(trEv);
  stateMachine.SinkTransitionNotFoundEv(erEv);
  
  
  // create simple transitions 
  TEST_ASSERT_TRUE(StateA->TransitionOnToWith(eventA,*StateB,FireAllHandler));
  TEST_ASSERT_TRUE(StateB->TransitionOnTo(eventB,*StateC));
  TEST_ASSERT_TRUE(StateC->TransitionOnTo(eventC,*StateD));
  TEST_ASSERT_TRUE(StateD->TransitionOnTo(eventD,*StateE));



  // See that the state machine starts in the initial state
  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateA), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));
  TEST_ASSERT_TRUE(StateA->IsCurrent());


  TEST_ASSERT_TRUE(eventA.TryFire());

  //Machine should be in StateE
  TEST_ASSERT_EQUAL_PTR(reinterpret_cast<const int*>(StateE), reinterpret_cast<const int*>(&(stateMachine.GetCurrentState())));

  
  //4 transitions in total
  TEST_ASSERT_EQUAL_UINT32(4,DataFromTests.size());
  for (size_t i = 0; i < DataFromTests.size(); ++i){
    //name must be transition
    TEST_ASSERT_EQUAL_STRING("transition",DataFromTests[i].HandlerName.c_str());
  }  
  
  //from StateA to StateB over eventA  
  size_t pos = 0;
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateA),  DataFromTests[pos].AddrFrom);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateB),  DataFromTests[pos].AddrTo);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&eventA), DataFromTests[pos].AddrEv);
  
  //from StateB to StateC over eventB  
  ++pos;
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateB),  DataFromTests[pos].AddrFrom);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateC),  DataFromTests[pos].AddrTo);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&eventB), DataFromTests[pos].AddrEv);

  //from StateC to StateD over eventC 
  ++pos;
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateC),  DataFromTests[pos].AddrFrom);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateD),  DataFromTests[pos].AddrTo);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&eventC), DataFromTests[pos].AddrEv);

  //from StateD to StateE over eventD  
  ++pos;
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateD),  DataFromTests[pos].AddrFrom);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(StateE),  DataFromTests[pos].AddrTo);
  TEST_ASSERT_EQUAL_UINT32(reinterpret_cast<uint32_t>(&eventD), DataFromTests[pos].AddrEv);  
}