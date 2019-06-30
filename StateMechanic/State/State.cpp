#include "State.hpp"




/******************************************************************************/
//State
State::State(IStateMachineWithEventFireRequest& sm, auto_ptr<EvHandler> entry, auto_ptr<EvHandler> exit):
  IStateWithMachineRef(sm),
  entryHandler(entry),
  exitHandler(exit){}
  

void State::SinkEntryHandler(auto_ptr<EvHandler> eh){
  entryHandler = eh;
} 

void State::SinkExitHandler(auto_ptr<EvHandler> eh){
  exitHandler = eh;
}



void State::FireEntry(auto_ptr<Iinfo> info) const{
  (*entryHandler)(info);
}

void State::FireExit(auto_ptr<Iinfo> info) const{
  (*exitHandler)(info);
}  

bool State::IsCurrent() const{
  return (&(GetParentStateMachine().GetCurrentState())) == this;
} 

/******************************************************************************/
//TransitionOn
bool State::TransitionOn(Event& ev)const{
  return TransitionOnTo(ev, *this);
}  

bool State::TransitionOnWith(Event& ev, auto_ptr<EvHandler> evh)const{
  return TransitionOnToWith(ev, *this, evh);
}  

bool State::TransitionOnWithGuard(Event& ev, auto_ptr<TransitionGuard> grd) const{
  return TransitionOnToWithGuard(ev, *this, grd);
} 

bool State::TransitionOnWithGuardAndHandler(Event& ev, auto_ptr<TransitionGuard> grd, 
                                            auto_ptr<EvHandler> evh) const{
  return TransitionOnToWithGuardAndHandler(ev, *this, grd, evh);
}

/******************************************************************************/
//TransitionOnTo
bool State::TransitionOnTo(Event& ev, const State& to)const{
  auto_ptr<EvHandler> evh(new DummyEvHandler());
  return TransitionOnToWith(ev, to, evh);
}  

bool State::TransitionOnToWith(Event& ev, const State& to, auto_ptr<EvHandler> evh)const{
  auto_ptr<TransitionGuard> grd(new DummyTransitionGuard);
  return TransitionOnToWithGuardAndHandler(ev, to, grd, evh);
}  

bool State::TransitionOnToWithGuard(Event& ev, const State& to, auto_ptr<TransitionGuard> grd) const{
  auto_ptr<EvHandler> evh(new DummyEvHandler());
  return TransitionOnToWithGuardAndHandler(ev, to, grd, evh);
} 

bool State::TransitionOnToWithGuardAndHandler(Event& ev, const State& to, 
                                              auto_ptr<TransitionGuard> grd, auto_ptr<EvHandler> evh) const{
  return ev.AddTransition(*this, to, evh, grd);
}

/******************************************************************************/
//InnerSelfTransitionOn
bool State::InnerSelfTransitionOn(Event& ev) const{
  auto_ptr<EvHandler> evh(new DummyEvHandler());
  return InnerSelfTransitionOnWith(ev, evh);
}

bool State::InnerSelfTransitionOnWith(Event& ev, auto_ptr<EvHandler> evh) const{
  auto_ptr<TransitionGuard> grd(new DummyTransitionGuard);
  return InnerSelfTransitionOnWithGuardAndHandler(ev, grd, evh);
}

bool State::InnerSelfTransitionOnWithGuard(Event& ev,  auto_ptr<TransitionGuard> grd) const{
  auto_ptr<EvHandler> evh(new DummyEvHandler());
  return InnerSelfTransitionOnWithGuardAndHandler(ev, grd, evh);
} 

bool State::InnerSelfTransitionOnWithGuardAndHandler(Event& ev, auto_ptr<TransitionGuard> grd, 
                                                     auto_ptr<EvHandler> evh) const{
  return ev.AddInnerTransition(*this, evh, grd);
}