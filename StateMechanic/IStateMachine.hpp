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

#ifndef __ISTATEMACHINE__
#define __ISTATEMACHINE__

#include "IState.hpp"

// A state machine, which may exist as a child state machine
class IStateMachine
{
  //copy/assign not implemented
  IStateMachine(const IStateMachine& s){}
  IStateMachine& operator=(const IStateMachine&){return *this;}    
protected:
  bool faulted;
public:
  IStateMachine():faulted(false){}
  virtual ~IStateMachine(){}

  bool IsFaulted(){return faulted;}
  
  
    // Gets the state which this state machine is currently in
    virtual IState& GetCurrentState() const = 0;

    // Gets the initial state of this state machine
    virtual IState* GetInitialState() const = 0;


	/*to be implemented*/
	// // Gets a vector of all states which are part of this state machine
    // vector<IState*> GetStates() = 0;
	
    // // Gets the parent state of this state machine, or null if there is none
    // IState* GetParentState() = 0;

    // // Gets the parent of this state machine, or null if there is none
    // IStateMachine* GetParentStateMachine() = 0;

    // // Gets the top-most state machine in this state machine hierarchy (which may be 'this')
    // IStateMachine& TopmostStateMachine() = 0;
	
	// // If has a child state machine, gets that child state machine's current state (recursively), otherwise gets CurrentState
    // virtual IState& CurrentChildState() = 0;

    // // Gets a value indicating whether the current state machine is active
    // virtual bool IsActive() = 0;

    // // Determines whether this state machine is a child of another state machine
    // virtual bool IsChildOf(IStateMachine& parentStateMachine) = 0;
};


#endif