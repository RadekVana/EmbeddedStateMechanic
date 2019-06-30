/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana

FILE: TransitionGuard.h
*******************************************************************************/

#ifndef __TRANSITIONGUARD__
#define __TRANSITIONGUARD__

#include "ITransitionGuard.hpp"
/******************************************************************************/


//guard with no data, it is same as ITransitionGuard, but ITransitionGuard
//cannot be used. TransitionGuardWithData, cannot be child of TransitionGuard
class TransitionGuard: public ITransitionGuard{
  virtual bool operator()(auto_ptr <Iinfo> info) = 0;
  virtual auto_ptr<ITransitionGuard> Clone() = 0; 
};





//dummy is allways ok
class DummyTransitionGuard: public TransitionGuard{
public:
  virtual bool operator()(auto_ptr <Iinfo> info){return true;}
  virtual auto_ptr<ITransitionGuard> Clone(){
    return auto_ptr<DummyTransitionGuard> (new DummyTransitionGuard());
  }
};

#endif