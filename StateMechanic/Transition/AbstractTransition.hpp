/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana


FILE: AbstractTransition.hpp

Definec changes of states
*******************************************************************************/

#ifndef __ABSTRACTTRANSITION__
#define __ABSTRACTTRANSITION__

#include "EvHandler.hpp"
#include "ITransition.hpp"
#include "ITransitionGuard.hpp"
/******************************************************************************/
//i can store transmisions in State (vector ... 12 Bytes per state)
//or in StateMachine (map 24 Bytes per machine)
//or in event

//data struct with State From Event State To and auto_ptr to EvHandler
//it Sinks EvHandler

//there will be guards ... later
//equal transitions have same "From" and Guards

/******************************************************************************/
//AbstractTransition
//childs can have or not have data
//AbstractTransition is base of "normal" Transition and InnerTransition, 
//so i can pass it by value in operator =
  
class AbstractTransition: public ITransition{
protected:  
  auto_ptr<Iinfo>     info;
  auto_ptr<IEvHandler> EvH;
  auto_ptr<ITransitionGuard> guard;
  
  //auto_ptr is not copyable so I need to create copy constructor and assignment operator
  AbstractTransition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh, auto_ptr<ITransitionGuard> grd);
  auto_ptr<Iinfo> CreateIinfoWithData(auto_ptr<IFiredData> firedData) const;
public:
  //AbstractTransition& operator = (const AbstractTransition& other);  
  AbstractTransition& operator = (AbstractTransition other);  // argument passed by value, no const reference .. swap is used
  AbstractTransition(const AbstractTransition& other);  
  
  void Swap(AbstractTransition & other);
  
  virtual Iinfo& GetInfo() const;
  virtual auto_ptr<Iinfo> SourceInfo() const;
  virtual void FireEntry() const {};//does nothing
  virtual void FireEventHandler(auto_ptr<IFiredData> firedData) const;
  virtual void FireExit() const {}; //does nothing 
  
  //guards
  virtual bool EvaluateGuard(auto_ptr<IFiredData> firedData) const;
  
};





#endif