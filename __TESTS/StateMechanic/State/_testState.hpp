#ifndef __TESTSTATE_HPP
#define __TESTSTATE_HPP

//unit tests of state

void IStateTest();
void StateHandlerTest();
void StateIsCurrentTest();
void State_TransitionTest();
void State_TransitionWithHandlerTest();
void State_TransitionWithGuardTest();
void State_TransitionWithGuardAndHandlerTest();
#endif