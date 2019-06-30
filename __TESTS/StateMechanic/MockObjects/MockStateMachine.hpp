#ifndef __MOCKSTATEMACHINE__HPP
#define __MOCKSTATEMACHINE__HPP

#include "IStateMachineWithEventFireRequest.hpp"

/******************************************************************************/

class MockStateMachine: public IStateMachineWithEventFireRequest{
protected:
  virtual bool RequestEventFireFromEvent(EventFireData efd){return true;};
public:
MockStateMachine(): someDummyState(new MockStateM(*this)){}

  auto_ptr<MockStateM> someDummyState;           
  virtual IState& GetCurrentState() const {return *someDummyState;}
  virtual IState* GetInitialState() const {return someDummyState.get();}
};

#endif