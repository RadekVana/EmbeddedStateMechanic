#include "Event.hpp"
#include "Transition.hpp"

/******************************************************************************/
//Event
bool Event::TryFire(){
  if (machine == NULL) return false;
//machine will handle all
  return machine->RequestEventFireFromEvent(transitions, *this);
}

bool Event::AddTransition(const IStateWithMachineRef& from, const IStateWithMachineRef& to, 
                          auto_ptr<EvHandler> evh, auto_ptr<TransitionGuard> grd){
  return __addTransition(from, to, auto_ptr<IEvHandler>(evh.release()), 
                         auto_ptr<ITransitionGuard>(grd.release()), &Event::createTransition);
}

bool Event::AddInnerTransition(const IStateWithMachineRef& from_to, auto_ptr<EvHandler> evh,
                               auto_ptr<TransitionGuard> grd){
  return __addTransition(from_to, from_to, auto_ptr<IEvHandler>(evh.release()), 
                         auto_ptr<ITransitionGuard>(grd.release()), &Event::createInnerTransition);
}

auto_ptr<Iinfo> Event::CreateIinfo(const IState& from, const IState& to, auto_ptr<IFiredData> firedData) const{
  //no data
  return CreateBaseIinfo(from, to);
}
