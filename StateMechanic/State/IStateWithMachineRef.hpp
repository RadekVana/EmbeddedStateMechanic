/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana

FILE: IStateWithMachineRef.hpp
*******************************************************************************/

#ifndef __ISTATEWITHMACHINEREF__
#define __ISTATEWITHMACHINEREF__


#include "IState.hpp"
#include "IStateMachineWithEventFireRequest.hpp"


// Event must be able to check machine reference
// IState does not have, IStateWithMachineRef does 
class IStateWithMachineRef: public IState{
  IStateMachineWithEventFireRequest& machine;
protected:
  //protected constructor makes it abstract
  IStateWithMachineRef(IStateMachineWithEventFireRequest& mchn):machine(mchn){}
public:
  // Gets the state machine to which this state belongs
  IStateMachineWithEventFireRequest& GetParentStateMachine() const{return machine;}

};

#endif