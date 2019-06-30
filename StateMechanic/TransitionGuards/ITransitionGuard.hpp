/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana

FILE: ITransitionGuards.h
*******************************************************************************/

#ifndef __ITRANSITIONGUARD__
#define __ITRANSITIONGUARD__

#include "IInfo.hpp"
/******************************************************************************/
class ITransitionGuard{
public:
  virtual bool operator()(auto_ptr <Iinfo> info) = 0;
  virtual auto_ptr<ITransitionGuard> Clone() = 0;
  virtual ~ITransitionGuard(){}
};


#endif