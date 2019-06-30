#ifndef __MOCKTRANSITIONGUARDS_HPP
#define __MOCKTRANSITIONGUARDS_HPP

/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana
To be used with unity in integration tests of state mechanic
*******************************************************************************/

#include "StateMechanic.hpp"


/******************************************************************************/
//Transmission guards
//points to bool and returns its value 
class BoolGuard: public TransitionGuard{
  const bool& Enable;
public:  
  
  BoolGuard(const bool& enable):Enable(enable){}
  virtual bool operator()(auto_ptr <Iinfo> info){return Enable;}
  virtual auto_ptr<ITransitionGuard> Clone(){
    return auto_ptr<BoolGuard> (new BoolGuard(Enable));
  }
};

//accepts info with bool data which are directly returned
class EnableBoolGuard: public TransitionGuardWithData<bool>{
protected:  
  virtual bool _do(auto_ptr <Info<bool> > info){return info->GetData();}
public:
  virtual auto_ptr<ITransitionGuard> Clone(){
    return auto_ptr<EnableBoolGuard > (new EnableBoolGuard());
  }
};

//to check if clone works by comparing PInt
class GuardWithPInt: public TransitionGuard{
public:   
  int* PInt;
 
  
  GuardWithPInt(int* pInt):PInt(pInt){}
  virtual bool operator()(auto_ptr <Iinfo> info){return true;}
  virtual auto_ptr<ITransitionGuard> Clone(){
    return auto_ptr<GuardWithPInt> (new GuardWithPInt(PInt));
  }
};
#endif