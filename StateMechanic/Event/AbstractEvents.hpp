/*******************************************************************************
CREATED: 06.06.2019, by Vana Radek

DESCRIPTION:
Abstract clases and class templates for events
Knowledge about transitions, transition guards and state machine is needed
First added transition "locks" event to machine. It cannot be used in different machine.
Transmitions are stored in events
Some event types (templates) can carry data. This data must be provided when event is being fired 
virtual bool TryFire() or virtual bool TryFire(T _data)



FILE: AbstractEvents.hpp
*******************************************************************************/

#ifndef __ABSTRACTEVENTS__
#define __ABSTRACTEVENTS__
#include "IEvent.hpp"
#include "IStateMachineWithEventFireRequest.hpp"
#include "ITransition.hpp"
#include "ITransitionGuard.hpp"
#include "IStateWithMachineRef.hpp"
#include "IEvHandler.hpp"

/******************************************************************************/
//transmissions are stored in events
//"State& From" of first added transitions is used to asociate event with StateMachine
//Event is ment as external influence on StateMachine, so it is not created from it
//transmissions are not stored in StateMachine, because vector of vectors of transitions 
//would be needed - it would consume more RAM and it would be more difficult to manage

//parent for IEventNoData and IEventWithData
class AbstractEvent: public IEvent{
protected:
  //protected ctor to make it abstract
  AbstractEvent():machine(NULL){}
  
  vector<ITransition*> transitions;
  //vector<ITransition*>::iterator getTransitionFromState(IState* from);
  IStateMachineWithEventFireRequest* machine;//need machine pointer to be able to request change of state 
  
  //transition creator signature
  typedef ITransition* (*transitionCreator)(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh, 
                                            auto_ptr<ITransitionGuard> grd);
  //factory methods for transmissions must be static
  static ITransition* createInnerTransition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh, auto_ptr<ITransitionGuard> grd);
  static ITransition* createTransition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh, auto_ptr<ITransitionGuard> grd);
  
  virtual bool __addTransition(const IStateWithMachineRef& from, const IStateWithMachineRef& to, 
                               auto_ptr<IEvHandler> evh, auto_ptr<ITransitionGuard> grd,
                               transitionCreator trCr); 
  friend class AbstractTransition;
  //need access to CreateIinfo. IFiredData must have right type!!! 
  //transition template is binded to correct event template
  //do not have dynamic_cast to check it in runtime
  virtual auto_ptr<Iinfo> CreateIinfo(const IState& from, const IState& to, auto_ptr<IFiredData> firedData) const= 0;
public:  
  
  auto_ptr<Iinfo> CreateBaseIinfo(const IState& from, const IState& to) const;
  
  virtual ~AbstractEvent();
  
  //AddTransition is not here 
  //it is in childern to ensure right parameter types are matched
};



/******************************************************************************/
//abstract parent for events with no data
class IEventNoData:public AbstractEvent{
protected:
  virtual auto_ptr<Iinfo> CreateIinfo(const IState& from, const IState& to, auto_ptr<IFiredData> firedData) const = 0;
public:
  virtual bool TryFire() = 0;
};

/******************************************************************************/
//abstract parent template for events with data
template <class T>
class IEventWithData:public AbstractEvent{
protected:
  virtual auto_ptr<Iinfo> CreateIinfo(const IState& from, const IState& to, auto_ptr<IFiredData> firedData) const = 0;
public:
  virtual bool TryFire(T _data) = 0;
};



#endif