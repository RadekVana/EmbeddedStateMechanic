#ifndef __MOCKFULLEVENT__HPP
#define __MOCKFULLEVENT__HPP

#include "Event.hpp"
#include "EventTemplate.hpp"
/******************************************************************************/
//mock objects allowing access to transitions - for testing

class MockFullEvent: public Event{
  virtual bool __addTransition(const IStateWithMachineRef& from, const IStateWithMachineRef& to, 
                               auto_ptr<IEvHandler> evh, auto_ptr<ITransitionGuard> grd,
                               transitionCreator trCr){
    _from       = &from;
    _to         = &to;
    _evh        = evh;
    _grd        = grd;
    if(trCr == createInnerTransition){
      _wasInnerTR = true;
      return true;
    }
    if(trCr == createTransition){
      _wasInnerTR = false;
      return true;
    }
    return false;
  }
public:
  MockFullEvent():_from(NULL), _to(NULL), _wasInnerTR(false){}
  const IStateWithMachineRef*   _from; 
  const IStateWithMachineRef*   _to;
  auto_ptr<IEvHandler>          _evh; 
  auto_ptr<ITransitionGuard>    _grd;
  bool                          _wasInnerTR;
};

template <class T>
class MockFullEventWithData: public EventWithData<T>{
public:
  vector<ITransition*>& GetTransitions(){return EventWithData<T>::transitions;}
};
#endif