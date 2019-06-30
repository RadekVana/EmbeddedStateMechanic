/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana
Inspired by https://github.com/canton7/StateMechanic
But much lighter version unlike original I do not use names in constreuctor - need to save RAM  
targetted for IAR compilled V850 Extended Embedded c++ 
  == no namespaces no exceptions and c++03 and some other limitations


FILE: ITransition.h
*******************************************************************************/

#ifndef __ITRANSITION__
#define __ITRANSITION__

#include "IInfo.hpp"
#include "IFiredData.hpp"
/******************************************************************************/
//i can store transmisions in State (vector ... 12 Bytes per state)
//or in StateMachine (map 24 Bytes per machine)
//or in event

//data struct with State From Event State To and auto_ptr to EvHandler
//it Sinks EvHandler

//there will be guards ... later
//equal transitions have same "From" and Guards
class ITransition{
public:
  virtual Iinfo& GetInfo() const = 0;
  virtual auto_ptr<Iinfo> SourceInfo() const = 0;
  virtual void FireEntry() const = 0;
  virtual void FireEventHandler(auto_ptr<IFiredData> firedData) const = 0;
  virtual void FireExit() const = 0;  
  
  virtual bool EvaluateGuard(auto_ptr<IFiredData> firedData) const = 0;
  virtual ~ITransition(){}
};



#endif