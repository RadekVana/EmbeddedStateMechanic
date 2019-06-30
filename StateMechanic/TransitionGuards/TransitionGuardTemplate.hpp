/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana

FILE: TransitionGuardTemplate.h
*******************************************************************************/

#ifndef __TRANSITIONGUARDTEMPLATE__
#define __TRANSITIONGUARDTEMPLATE__

#include "ITransitionGuard.hpp"
/******************************************************************************/


//guard with no data, it is same as ITransitionGuard, but ITransitionGuard
//cannot be used TransitionGuardWithData, cannot be child of TransitionGuard
template <class T>
class TransitionGuardWithData: public ITransitionGuard{
protected:  
  //overload this
  virtual bool _do(auto_ptr <Info<T> > info) = 0;
public:
  //do not overload this, do not have sealed
  virtual bool operator()(auto_ptr <Iinfo> info){
    //do not have dynamic_cast
    Info<T>* ptrInfo = reinterpret_cast<Info<T>* >(info.release());
    return _do(auto_ptr <Info<T> >(ptrInfo));
  }
  virtual auto_ptr<ITransitionGuard> Clone() = 0; 
};





//dummy is allways ok
template <class T>
class DummyTransitionGuardWithData: public TransitionGuardWithData<T>{
protected:  
  virtual bool _do(auto_ptr <Info<T> > info){return true;}
public:
  virtual auto_ptr<ITransitionGuard> Clone(){
    return auto_ptr<DummyTransitionGuardWithData<T> > (new DummyTransitionGuardWithData<T>());
  }
};

#endif