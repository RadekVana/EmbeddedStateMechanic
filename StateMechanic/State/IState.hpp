/*******************************************************************************
CREATED: 29.05.2019, by Vana Radek

DESCRIPTION:
Interface for a state of state mechine.

FILE: IState.hpp
*******************************************************************************/

#ifndef __ISTATE__
#define __ISTATE__



// A state, which can be transioned from/to, and which can represent the current state 
class IState{

    //cannot copy/assign
  IState(const IState& s){}
  IState& operator=(const IState&){return *this;}
protected:
  //protected constructor makes it abstract
  IState(){}
public:  
  virtual ~IState(){}

};

#endif