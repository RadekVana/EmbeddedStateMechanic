#ifndef __TESTSTATEMECHANIC_HPP
#define __TESTSTATEMECHANIC_HPP

//integration tests of state machine
//https://github.com/canton7/StateMechanic#exceptions-and-faulting



//modified Quick Start
void StateMechanic_QuickStart();

//modified Inner Self Transitions
void StateMechanic_InnerSelfTransitions();

  
void StateMechanic_EventData();

void StateMechanic_TransitionGuards();

void StateMechanic_TransitionGuardsWithData();

void StateMechanic_RecursiveTransition();

void StateMechanic_RecursiveTransition_allButFirstFiredAtOnce();
#endif