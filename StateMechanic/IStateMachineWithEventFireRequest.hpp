/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana
Inspired by https://github.com/canton7/StateMechanic
But much lighter version unlike original I do not use names in constreuctor - need to save RAM  
targetted for IAR compilled V850 Extended Embedded c++ 
  == no namespaces no exceptions and c++03 and some other limitations

please do not inherit State, SourceEventTarget
there is no way in c++03 to disable inheritance
this clases does not have virtual destructors (to be smaller)

//original implementation has transitions inside states
//my implementation has transitions inside events 
//I store them in vectors and can have fewer vectors this way - it saves lot of RAM

*******************************************************************************/

#ifndef __ISTATEMACHINEWITHRQFIRE__
#define __ISTATEMACHINEWITHRQFIRE__

#include "IStateMachine.hpp"
#include "ITransition.hpp"
#include "IFiredData.hpp"

#include <memory>
#include <vector>

//need this object to be able to enque fired requestfroman event
class EventFireData{
  const vector<ITransition*>& _transitions; 
  IEvent& _ev;
  auto_ptr<IFiredData> _firedData;
public:
  EventFireData(const vector<ITransition*>& transitions, IEvent& ev, auto_ptr<IFiredData> firedData):
    _transitions(transitions), _ev(ev), _firedData(firedData){}
  EventFireData(const EventFireData& other):
    _transitions(other._transitions), _ev(other._ev), _firedData(other.SourceData()){}
    
  auto_ptr<IFiredData> SourceData() const{return _firedData->Clone();}
  IFiredData* GetData() const {return _firedData.get();}
  IEvent& GetEvent() const{return _ev;}
  const vector<ITransition*>& GetTransitions() const{ return _transitions;}
};


class IStateMachineWithEventFireRequest: public IStateMachine{
protected:
  virtual bool RequestEventFireFromEvent(EventFireData efd) = 0;
  
  
public:
  bool RequestEventFireFromEvent(const vector<ITransition*>& transitions, 
                                 IEvent& ev, auto_ptr<IFiredData> firedData = 
                                 auto_ptr<IFiredData>(new IFiredData)){
     return RequestEventFireFromEvent(EventFireData(transitions, ev, firedData));                   
  }
  
  // Gets the state which this state machine is currently in
  virtual IState& GetCurrentState() const = 0;

  // Gets the initial state of this state machine
  virtual IState* GetInitialState() const = 0;
};

#endif