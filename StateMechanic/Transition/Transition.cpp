#include "Transition.hpp"
#include "State.hpp"

/******************************************************************************/
//InnerTransition

InnerTransition::InnerTransition(auto_ptr<Iinfo> _info, auto_ptr<IEvHandler> evh,
  auto_ptr<ITransitionGuard> grd):
  AbstractTransition(_info, evh,grd){}
  //AbstractTransition(info, evh,auto_ptr<ITransitionGuard>(grd.release())){}
 


/******************************************************************************/
//Transition

Transition::Transition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh,
  auto_ptr<ITransitionGuard> grd):
  InnerTransition(info, evh,grd){}
  
void Transition::FireEntry() const{
  //do not have dynamic_cast, have to use reinterpret_cast
  const State& to = reinterpret_cast<const State&>(info->GetTo());
  to.FireEntry(auto_ptr<Iinfo>(new Iinfo(*info)));
}

void Transition::FireExit() const{
  //do not have dynamic_cast, have to use reinterpret_cast
  const State& from = reinterpret_cast<const State&>(info->GetFrom());  
  from.FireExit(auto_ptr<Iinfo>(new Iinfo(*info)));
}