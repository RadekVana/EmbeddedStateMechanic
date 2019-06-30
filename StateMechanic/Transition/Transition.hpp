/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana


FILE: Transition.hpp

Defines changes of states
*******************************************************************************/

#ifndef __TRANSITION__
#define __TRANSITION__

#include "AbstractTransition.hpp"
#include "ITransitionGuard.hpp"
//#include "TransitionGuard.hpp"
/******************************************************************************/
//InnerTransition
//entry / exit state evets are not fired  
//InnerTransition is base of "normal" Transition, so i can pass it by value in operator =
  

//ITransitionGuard is used so template transitions for 
//transitions with data are not needed
class InnerTransition: public AbstractTransition{
public:
  InnerTransition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh,
    auto_ptr<ITransitionGuard> grd/* = auto_ptr<DummyTransitionGuard> (new DummyTransitionGuard())*/);
  //coppy ctor and assgnment operators will be auto generated
  
  virtual void FireEntry() const {};//does nothing
  virtual void FireExit() const {}; //does nothing 
  
  //void SinkGuard(auto_ptr<TransitionGuard> grd);
};

/******************************************************************************/
//Transition
//entry / exit state evets are fired   
class Transition: public InnerTransition{
public:
  Transition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh,
    auto_ptr<ITransitionGuard> grd/* = auto_ptr<DummyTransitionGuard> (new DummyTransitionGuard())*/);
  //coppy ctor and assgnment operators will be auto generated
  virtual void FireEntry() const;
  virtual void FireExit() const;  
};




#endif