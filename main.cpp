#define UNITY_INCLUDE_SETUP_STUBS
#define UNITY_WEAK_ATTRIBUTE



#include "unity.h"

#include "_testStateMechanic.hpp"
#include "_testAbstractEvents.hpp"
#include "_testEvents.hpp"
#include "_testEvHandler.hpp"
#include "_testInfo.hpp"
#include "_testFiredData.hpp"
#include "_testState.hpp"
#include "_testTransition.hpp"


int main()
{
  //to see in log file
  printf("TESTING STARTED: %s %s\n",__DATE__,__TIME__);
  
 
  printf("Unit tests\n");
  printf("Events\n");
  RUN_TEST(AbstractEventTest);
  RUN_TEST(EventTest);
  RUN_TEST(EventTestInt);
  RUN_TEST(EventTestBool);
  RUN_TEST(EventTestDouble);
  RUN_TEST(EventTestString);
  RUN_TEST(EventTestStruct);
  
  printf("Event handlerss\n");
  RUN_TEST(EvHandlerCloneTest);   
  RUN_TEST(EvHandlerCloneTestInt); 
  RUN_TEST(EvHandlerCloneTestBool); 
  RUN_TEST(EvHandlerCloneTestDouble); 
  RUN_TEST(EvHandlerCloneTestString); 
  RUN_TEST(EvHandlerCloneTestStringPrt); 
  RUN_TEST(EvHandlerCloneTestStruct);  
  RUN_TEST(EvHandlerDataTestInt); 
  RUN_TEST(EvHandlerDataTestDouble); 
  RUN_TEST(EvHandlerDataTestBool); 
  RUN_TEST(EvHandlerDataTestString); 
  RUN_TEST(EvHandlerDataTestStruct); 
  
  printf("Info\n");
  RUN_TEST(IinfoTest); 
  RUN_TEST(InfoTestInt); 
  RUN_TEST(InfoTestBool); 
  RUN_TEST(InfoTestDouble); 
  RUN_TEST(InfoTestString); 
  RUN_TEST(InfoTestStruct); 
  
  printf("FiredData\n");
  RUN_TEST(FiredDataCloneTest); 
  RUN_TEST(FiredDataCloneTestInt); 
  RUN_TEST(FiredDataCloneTestBool); 
  RUN_TEST(FiredDataCloneTestDouble); 
  RUN_TEST(FiredDataCloneTestString); 
  RUN_TEST(FiredDataCloneTestStringPtr);
  RUN_TEST(FiredDataCloneTestStruct); 
  RUN_TEST(FiredData_DataTestInt); 
  RUN_TEST(FiredData_DataTestDouble); 
  RUN_TEST(FiredData_DataTestBool); 
  RUN_TEST(FiredData_DataTestString); 
  RUN_TEST(FiredData_DataTestStruct); 
  
  printf("State\n");
  RUN_TEST(IStateTest);
  RUN_TEST(StateHandlerTest);
  RUN_TEST(StateIsCurrentTest);
  RUN_TEST(State_TransitionTest);
  RUN_TEST(State_TransitionWithHandlerTest);
  RUN_TEST(State_TransitionWithGuardTest);
  RUN_TEST(State_TransitionWithGuardAndHandlerTest);
  printf("MISSING UNIT TESTS OT TEMPLATE METHODS\n");
  
  printf("Transition\n");
  RUN_TEST(TransitionCtorTest);
  RUN_TEST(InnerTransitionCtorTest);
  RUN_TEST(TransitionSourceInfoTest);
  RUN_TEST(TransitionAsigmentTest);
  
  printf("Integration tests\n");
  printf("State mechanic\n");
  RUN_TEST(StateMechanic_QuickStart);
  RUN_TEST(StateMechanic_InnerSelfTransitions);
  RUN_TEST(StateMechanic_EventData);
  RUN_TEST(StateMechanic_TransitionGuards);
  RUN_TEST(StateMechanic_TransitionGuardsWithData);
  RUN_TEST(StateMechanic_RecursiveTransition);
  RUN_TEST(StateMechanic_RecursiveTransition_allButFirstFiredAtOnce);
  printf("****************\n");
  printf("Testing finished\n");
  printf("****************\n");
  return 0;
}
