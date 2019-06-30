/*******************************************************************************
CREATED: 29.05.2019, by Vana Radek

DESCRIPTION:
Inspired by https://github.com/canton7/StateMechanic
But much lighter version unlike original I do not use names in constreuctor - need to save RAM  
targetted for IAR compilled V850 Extended Embedded c++ 
  == no namespaces no exceptions and c++03 and some other limitations


FILE: StateMechanic.h
*******************************************************************************/

#ifndef __STATEMECHANIC__
#define __STATEMECHANIC__


#include "IEvent.hpp"
#include "State.hpp"
#include "IStateMachineWithEventFireRequest.hpp"
#include "IInfo.hpp"
#include <queue>




/******************************************************************************/
//StateMachine 
//has a few useful events:
//
//Transition will be raised whenever a transition occurs 

//(either one this state machine or on one of its children). - to be implemented

//This is very useful for logging: you can track exactly what your application 
//is doing, for free, with this log output. TransitionNotFound will be raised 
//whenever an Event.Fire() or an Event. TryFire() fails. In the case of recursive 
//transitions and Event.TryFire(), this is the only way to know that the transition 
//failed. Again, useful for logging. Faulted is raised whenever the state machine 
//faults, i.e. an exception is raised by a transition or state entry/exit handler.

//Event is an outer influence, so state machine does not need to know it
class StateMachine: public IStateMachineWithEventFireRequest{
  //EventFireLocker forces eventfire to go to the queue if an event is being fired
  // used in recursive transmissions
  //when an instance is created it locks the lock
  //when the instance is destroyed, lock is released
  //bool would be fine for 1 instance, uint32_t just to ba able have multiple instances
  uint32_t AnEventIsBeingFired;
  bool IsAnEventBeingFired(){return AnEventIsBeingFired;}
  queue<EventFireData> evQueue;
  bool enque(EventFireData efd);
  bool deque();
  
  class EventFireLocker{
    StateMachine& _machine;
  public:
    EventFireLocker(StateMachine& machine):_machine(machine){++_machine.AnEventIsBeingFired;}
    ~EventFireLocker(){--_machine.AnEventIsBeingFired;}
  };
  
  //state is not copyable, i need pointers
  vector<State*>::iterator currentState;
  
  //do not have unique_ptr
  vector<State*> states;
  vector<State*> DefaultStates;
  vector<vector<State*>::iterator> DefaultStatesTransitions;
  //DS_TRANSITION_NOT_FOUNT - state machine will stay in its state
  typedef enum {
    DS_UNINICIALIZED = 0, DS_FAULTED, DS_COUNT
  } DEFAULT_STATES;
  
  
  State* __createState(
          auto_ptr<EvHandler> entry = auto_ptr<EvHandler>(new DummyEvHandler()), 
          auto_ptr<EvHandler> exit = auto_ptr<EvHandler>(new DummyEvHandler()));
  
  auto_ptr<EvHandler> transitionEv;//any nondefault transmission fires it
  auto_ptr<EvHandler> defaultTransitionEv;//any default transmission fires it
  auto_ptr<EvHandler> transitionNotFoundEv;
  auto_ptr<EvHandler> faultedEv;
  
  //void setDefState(DEFAULT_STATES s);
  bool isDefaultState(vector<State*>::iterator state);
  void defaultTransition(vector<State*>::iterator itActualState, 
                         vector<State*>::iterator itNextState, IEvent& ev);
  DEFAULT_STATES getDefaultId(vector<State*>::iterator state);
  
  //first fires exit state, than event, than enter, than transition
  void _changeState_FireEvents(const ITransition& transition, IEvHandler& transmEv,
                               vector<State*>::iterator to, auto_ptr<IFiredData> firedData);
  
  virtual bool RequestEventFireFromEvent(EventFireData efd);
  bool __requestEventFireFromEvent(EventFireData efd);
public:
  StateMachine();
  
  //const State* == NULL == erorr
  State* CreateInitialState(
          auto_ptr<EvHandler> entry = auto_ptr<EvHandler>(new DummyEvHandler()), 
          auto_ptr<EvHandler> exit = auto_ptr<EvHandler>(new DummyEvHandler()));
  State* CreateState(
          auto_ptr<EvHandler> entry = auto_ptr<EvHandler>(new DummyEvHandler()), 
          auto_ptr<EvHandler> exit = auto_ptr<EvHandler>(new DummyEvHandler()));
  virtual State* GetInitialState() const;  
  virtual State& GetCurrentState() const;//Machine is allways in some state

  
  void Reset();
  void SinkTransitionEv(auto_ptr<EvHandler> eh);//raised on any transition
  void SinkTransitionNotFoundEv(auto_ptr<EvHandler> eh); 
  void SinkFaultedEv(auto_ptr<EvHandler> eh); 

  
  virtual ~StateMachine();
};

#endif