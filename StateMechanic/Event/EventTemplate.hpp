/*******************************************************************************
CREATED: 06.06.2019, by Vana Radek

DESCRIPTION:
Templates for events which can carry data.
Description of Event is in Event.hpp.

FILE: EventTemplate.hpp
*******************************************************************************/

#ifndef __EVENT_TEMPLATE__
#define __EVENT_TEMPLATE__
#include "IEvent.hpp"
#include "IStateMachineWithEventFireRequest.hpp"
#include "AbstractTransition.hpp"
#include "IStateWithMachineRef.hpp"
#include "TransitionGuardTemplate.hpp"
#include "FiredData.hpp"
/******************************************************************************/
//You can associate data with particular events. When you fire the event, you also provide the data. 
template <class T>
class EventWithData: public IEventWithData<T>{
protected:
  //cannot return auto_ptr<Info<T> > it is not covariant
  //an exception should be rised when firedData does not match T
  //but there is no dynamic_cast in IAR "Embedded c++"
  virtual auto_ptr<Iinfo> CreateIinfo(const IState& from, const IState& to, auto_ptr<IFiredData> firedData) const;//adds data too
public:
  virtual bool TryFire(T _data);
  
  //EvHandlerWithData<T> ensure data match .. there cannot be IEvHandler
  bool AddTransition(const IStateWithMachineRef& from, const IStateWithMachineRef& to, 
                     auto_ptr<EvHandlerWithData<T> > evh, auto_ptr<TransitionGuardWithData<T> > grd);  
  bool AddInnerTransition(const IStateWithMachineRef& from_to, auto_ptr<EvHandlerWithData<T> > evh,
                          auto_ptr<TransitionGuardWithData<T> > grd);  
};  
  



/******************************************************************************/  
//templte method definitions cannot be in cpp file

  
template <class T>
bool EventWithData<T>::TryFire(T _data){
  if (IEventWithData<T>::machine == NULL) return false;
  auto_ptr<IFiredData> firedData = auto_ptr<IFiredData>(new FiredData<T>(_data));
  //machine will handle all
  return IEventWithData<T>::machine->RequestEventFireFromEvent(IEventWithData<T>::transitions, *this, firedData);
};




template <class T>
auto_ptr<Iinfo> EventWithData<T>::CreateIinfo(const IState& from, const IState& to, auto_ptr<IFiredData> firedData)const{
  FiredData<T>* data_ptr = reinterpret_cast<FiredData<T>* > (firedData.release());
  auto_ptr<FiredData<T> > data (data_ptr);
    auto_ptr<Iinfo> ret( new Info<T>(from, to, *this, data->Get()));
    return ret;
  };

//cannot use &AbstractEvent::createInnerTransition
//protected function "AbstractEvent::createTransition" is not accessible through a "AbstractEvent" pointer or object 
template <class T>
bool EventWithData<T>::AddTransition(const IStateWithMachineRef& from, const IStateWithMachineRef& to, 
                                     auto_ptr<EvHandlerWithData<T> > evh, auto_ptr<TransitionGuardWithData<T> > grd){
  return AbstractEvent::__addTransition(from, to, 
                                        auto_ptr<IEvHandler>(evh.release()), 
                                        auto_ptr<ITransitionGuard>(grd.release()),
                                        &EventWithData<T>::createTransition);
}

template <class T>
bool EventWithData<T>::AddInnerTransition(const IStateWithMachineRef& from_to, 
                                          auto_ptr<EvHandlerWithData<T> > evh, auto_ptr<TransitionGuardWithData<T> > grd){
  return AbstractEvent::__addTransition(from_to, from_to, 
                                        auto_ptr<IEvHandler>(evh.release()), 
                                        auto_ptr<ITransitionGuard>(grd.release()),
                                        &EventWithData<T>::createInnerTransition);
}
#endif