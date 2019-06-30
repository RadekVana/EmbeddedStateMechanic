#ifndef __MOCKSTATEWITHMACHINEREF__HPP
#define __MOCKSTATEWITHMACHINEREF__HPP

#include "IStateWithMachineRef.hpp"

/******************************************************************************/
//mock objects used for test

class MockStateM: public IStateWithMachineRef{
public:
  MockStateM(IStateMachineWithEventFireRequest& mchn):IStateWithMachineRef(mchn){}
};

#endif