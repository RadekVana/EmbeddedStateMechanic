/*******************************************************************************
CREATED: 29.05.2019, by Vana Radek

DESCRIPTION:
State represent state of stat machine

Transitions:
transition from curret state on event to next state should be added in state
state just pass them to events == transitions are stored in events
state has template methods to ensure protection - right type of event, guard and
event handler must be matched
transitions can have data, guards and event handlers

Entry and Exit handlers:
state holds one entry and one exit handler, which are invoked (by state machine), 
when state is entred or left. 

Inner Self Transitions:
A state is allowed to transition to itself. This is a useful way of running some 
code when an event is fired, but only if the state machine is in a particular 
state. By default, both the exit and entry handlers will also be invoked in 
this case. If you don't want this, then create an inner self transition instead.

Thinks to be implemented:
Child state machine
state groups
get all transitions state is involved in
FILE: State.hpp
*******************************************************************************/

#ifndef __STATE__
#define __STATE__

#include "IStateWithMachineRef.hpp"
#include "IStateMachineWithEventFireRequest.hpp"
#include "EvHandler.hpp"
#include "Event.hpp"
#include "EventTemplate.hpp"
/******************************************************************************/

class State: public IStateWithMachineRef{
  //EvHandler .. with no extra data
  auto_ptr<EvHandler> entryHandler;
  auto_ptr<EvHandler> exitHandler;
public:
  State(IStateMachineWithEventFireRequest& sm, 
        auto_ptr<EvHandler> entry = auto_ptr<EvHandler>(new DummyEvHandler()), 
        auto_ptr<EvHandler> exit = auto_ptr<EvHandler>(new DummyEvHandler()));
  void SinkEntryHandler(auto_ptr<EvHandler> eh); 
  void SinkExitHandler(auto_ptr<EvHandler> eh); 
  
  //it would be more clear to create info inside - because one of states 
  //(from or to) is known, but info is already exists when state machine fires 
  //entry/exit and just use it is much faster
  void FireEntry(auto_ptr<Iinfo> info) const;
  void FireExit(auto_ptr<Iinfo> info) const;  

  bool IsCurrent() const;
  bool TransitionOn(Event& ev) const;  
  bool TransitionOnWith(Event& ev, auto_ptr<EvHandler> evh) const; 
  bool TransitionOnWithGuard(Event& ev, auto_ptr<TransitionGuard> grd) const; 
  bool TransitionOnWithGuardAndHandler(Event& ev,auto_ptr<TransitionGuard> grd, 
                                         auto_ptr<EvHandler> evh) const; 
   
  bool TransitionOnTo(Event& ev, const State& to) const;  
  bool TransitionOnToWith(Event& ev, const State& to, auto_ptr<EvHandler> evh) const; 
  bool TransitionOnToWithGuard(Event& ev, const State& to, auto_ptr<TransitionGuard> grd) const; 
  bool TransitionOnToWithGuardAndHandler(Event& ev, const State& to, 
                                         auto_ptr<TransitionGuard> grd, auto_ptr<EvHandler> evh) const; 
  
  bool InnerSelfTransitionOn(Event& ev) const;
  bool InnerSelfTransitionOnWith(Event& ev, auto_ptr<EvHandler> evh) const;   
  bool InnerSelfTransitionOnWithGuard(Event& ev,  auto_ptr<TransitionGuard> grd) const; 
  bool InnerSelfTransitionOnWithGuardAndHandler(Event& ev, auto_ptr<TransitionGuard> grd, 
                                                auto_ptr<EvHandler> evh) const; 
  
  //template methods ensure that "data events" are paired with "data event handlers"
  //IAR does not have runtime type check
  /*DataTransitionOn*/
  template <class T>
  bool DataTransitionOn(EventWithData<T>& ev) const;  
  template <class T>
  bool DataTransitionOnWith(EventWithData<T>& ev, auto_ptr<EvHandlerWithData<T> > evh) const; 
  template <class T>
  bool DataTransitionOnWithGuard(EventWithData<T>& ev, 
                                 auto_ptr<TransitionGuardWithData<T> > grd) const; 
  template <class T>
  bool DataTransitionOnWithGuardAndHandler(EventWithData<T>& ev,
                                            auto_ptr<TransitionGuardWithData<T> > grd,
                                            auto_ptr<EvHandlerWithData<T> > evh) const; 
   /*DataTransitionOnTo*/
  template <class T>
  bool DataTransitionOnTo(EventWithData<T>& ev, const State& to) const; 
  template <class T>
  bool DataTransitionOnToWith(EventWithData<T>& ev, const State& to, auto_ptr<EvHandlerWithData<T> > evh) const; 
  template <class T>
  bool DataTransitionOnToWithGuard(EventWithData<T>& ev, const State& to, 
                                   auto_ptr<TransitionGuardWithData<T> > grd) const; 
  template <class T>
  bool DataTransitionOnToWithGuardAndHandler(EventWithData<T>& ev, const State& to,
                                            auto_ptr<TransitionGuardWithData<T> > grd,
                                            auto_ptr<EvHandlerWithData<T> > evh) const; 
  
   /*InnerSelfDataTransitionOn*/
  template <class T>
  bool InnerSelfDataTransitionOn(EventWithData<T>& ev) const;
  template <class T>
  bool InnerSelfDataTransitionOnWith(EventWithData<T>& ev, 
                                     auto_ptr<EvHandlerWithData<T> > evh) const;  
  template <class T>
  bool InnerSelfDataTransitionOnWithGuard(EventWithData<T>& ev, 
                                          auto_ptr<TransitionGuardWithData<T> > grd) const;
  template <class T>
  bool InnerSelfDataTransitionOnWithGuardAndHandler(EventWithData<T>& ev, 
                                                    auto_ptr<TransitionGuardWithData<T> > grd,
                                                    auto_ptr<EvHandlerWithData<T> > evh) const; 
};


/******************************************************************************/
//template methods
/*DataTransitionOn*/
template <class T>
bool State::DataTransitionOn(EventWithData<T>& ev)const{
  return DataTransitionOnTo(ev, *this);
}  

template <class T>
bool State::DataTransitionOnWith(EventWithData<T>& ev, auto_ptr<EvHandlerWithData<T> > evh)const{
  return DataTransitionOnToWith(ev, *this, evh);
}  

template <class T>
bool State::DataTransitionOnWithGuard(EventWithData<T>& ev, 
                                        auto_ptr<TransitionGuardWithData<T> > grd) const{
  return DataTransitionOnToWithGuard(ev, *this, grd);
}

template <class T>
bool State::DataTransitionOnWithGuardAndHandler(EventWithData<T>& ev,
                                            auto_ptr<TransitionGuardWithData<T> > grd,
                                            auto_ptr<EvHandlerWithData<T> > evh) const{
  return DataTransitionOnWithGuardAndHandler(ev, *this, grd, evh);
}
/*DataTransitionOnTo*/
template <class T>
bool State::DataTransitionOnTo(EventWithData<T>& ev, const State& to)const{
  auto_ptr<EvHandlerWithData<T> > evh(new DummyEvHandlerWithData<T>());
  return DataTransitionOnToWith(ev, to, evh);
}  

template <class T>
bool State::DataTransitionOnToWith(EventWithData<T>& ev, const State& to, auto_ptr<EvHandlerWithData<T> > evh)const{
  auto_ptr<TransitionGuardWithData<T> > grd(new DummyTransitionGuardWithData<T>);
  return DataTransitionOnToWithGuardAndHandler(ev, to, grd, evh);
}  

template <class T>
bool State::DataTransitionOnToWithGuard(EventWithData<T>& ev, const State& to, 
                                        auto_ptr<TransitionGuardWithData<T> > grd) const{
  auto_ptr<EvHandlerWithData<T> > evh(new DummyEvHandlerWithData<T>());
  return DataTransitionOnToWithGuardAndHandler(ev, to, grd, evh);
}

template <class T>
bool State::DataTransitionOnToWithGuardAndHandler(EventWithData<T>& ev, const State& to,
                                            auto_ptr<TransitionGuardWithData<T> > grd,
                                            auto_ptr<EvHandlerWithData<T> > evh) const{
  return ev.AddTransition(*this, to, evh, grd);
}

/*InnerSelfDataTransitionOn*/
template <class T>
bool State::InnerSelfDataTransitionOn(EventWithData<T>& ev) const{
  auto_ptr<EvHandlerWithData<T> > evh(new DummyEvHandlerWithData<T>());
  return InnerSelfTransitionOnWith(ev, evh);
}

template <class T>
bool State::InnerSelfDataTransitionOnWith(EventWithData<T>& ev, auto_ptr<EvHandlerWithData<T> > evh) const{
  auto_ptr<TransitionGuardWithData<T> > grd(new DummyTransitionGuardWithData<T>);
  return InnerSelfDataTransitionOnWithGuardAndHandler(ev, grd, evh);
}


template <class T>
bool State::InnerSelfDataTransitionOnWithGuard(EventWithData<T>& ev, 
                                               auto_ptr<TransitionGuardWithData<T> > grd) const{
  auto_ptr<EvHandlerWithData<T> > evh(new DummyEvHandlerWithData<T>());
  return InnerSelfDataTransitionOnWithGuardAndHandler(ev, grd, evh);
}

template <class T>
bool State::InnerSelfDataTransitionOnWithGuardAndHandler(EventWithData<T>& ev, 
                                                    auto_ptr<TransitionGuardWithData<T> > grd,
                                                    auto_ptr<EvHandlerWithData<T> > evh) const{
  return ev.AddInnerTransition(*this, evh, grd);
}
#endif