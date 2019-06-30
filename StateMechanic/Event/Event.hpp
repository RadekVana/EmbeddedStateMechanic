/*******************************************************************************
CREATED: 29.05.2019, by Vana Radek

DESCRIPTION:
Behavior of events is inspired by events from StateMechanic
https://github.com/canton7/StateMechanic 
Unlike original Events are not named to save RAM in embedded system.
Also there is no Fire method (only try Fire), due compiller limitations (no exceptions).

Events represent outside influence on the state machine.
One event per "thing" which can happen should be created, rather than one event 
for each type of change.

TryFire() will return false if no transition (whose guard returned true) could 
be found on that event from the current state.

Event is not ment to be created from a factory method on StateMachine. 
However, it is still associated with a state machine (and becomes associated with it 
the first time a transition involving that event is defined).
So an event cannot be used with multiple state machines, and it cannot be fired 
until it has been used to define at least one transition.  

AddTransition and AddInnerTransition is ment to be called from State.

FILE: Event.hpp
*******************************************************************************/

#ifndef __EVENT__
#define __EVENT__
#include "AbstractEvents.hpp"
#include "IStateMachineWithEventFireRequest.hpp"
#include "Transition.hpp"
#include "IStateWithMachineRef.hpp"
#include "TransitionGuard.hpp"
/******************************************************************************/

class Event: public IEventNoData{
protected:
  virtual auto_ptr<Iinfo> CreateIinfo(const IState& from, const IState& to, auto_ptr<IFiredData> firedData) const;
public:
  virtual bool TryFire();
  
  //EvHandler ensure data match .. there cannot be IEvHandler
  bool AddTransition(const IStateWithMachineRef& from, const IStateWithMachineRef& to, 
                     auto_ptr<EvHandler> evh, auto_ptr<TransitionGuard> grd);  
  bool AddInnerTransition(const IStateWithMachineRef& from_to, auto_ptr<EvHandler> evh,
                          auto_ptr<TransitionGuard> grd);  
};




#endif