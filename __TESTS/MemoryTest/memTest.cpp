#include "memTest.hpp"

//#include "UnityAddin.h"
//#define UNITY_INCLUDE_SETUP_STUBS
//#define UNITY_WEAK_ATTRIBUTE
#include "unity.h"



/******************************************************************************/
//tests if dynamic memory was dealocated
//new and delete operators are overloaded
//they count numbers of being called
//more sofisticated test would be great, 
//but dthere is no information about amount of dealocated memory in delete

void DynMemTest(){
  UnityBegin(__FILE__);
  
  
  TEST_ASSERT_EQUAL_UINT32(uint32_t(_get_malloced()), uint32_t(_get_freed()));
  
}