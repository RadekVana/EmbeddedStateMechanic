#ifndef __TRANSITION__HPP
#define __TRANSITION__HPP

#include "Transition.hpp"

/******************************************************************************/
//mock objects used for test
//used to acces protected members

class MockInnerTransition: public InnerTransition{
public:
  IEvHandler& GetHndlr(){return *EvH;}
  ITransitionGuard& GetGrd(){return *guard;}
  
  MockInnerTransition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh,
                      auto_ptr<ITransitionGuard> grd): InnerTransition(info, evh, grd){}
};

class MockTransition: public Transition{
public:
  IEvHandler& GetHndlr(){return *EvH;}
  ITransitionGuard& GetGrd(){return *guard;}
  
  MockTransition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh,
                 auto_ptr<ITransitionGuard> grd): Transition(info, evh, grd){}
};

#endif