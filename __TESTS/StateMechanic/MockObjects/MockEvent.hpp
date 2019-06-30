#ifndef __MOCKEVENT__HPP
#define __MOCKEVENT__HPP

#include "AbstractEvents.hpp"

/******************************************************************************/
//mock objects used for test

class MockEvent: public AbstractEvent{
  //dummy not used 
  virtual auto_ptr<Iinfo> CreateIinfo(const IState& from, const IState& to, auto_ptr<IFiredData> firedData) const{
    return auto_ptr<Iinfo>();
  }
public:
  MockEvent(){}
};

template <class T>
class MockEventWithData: public IEventWithData<T>{
  //dummy not used 
  virtual auto_ptr<Iinfo> CreateIinfo(const IState& from, const IState& to, auto_ptr<IFiredData> firedData) const{
    return auto_ptr<Iinfo>();
  }
  virtual bool TryFire(T _data){return true;}
};
#endif