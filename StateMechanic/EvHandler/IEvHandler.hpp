/*******************************************************************************
CREATED: 07.06.2019, by Vana Radek

DESCRIPTION:
Interface for event handlers

FILE: IEvHandler.hpp
*******************************************************************************/

#ifndef __IEVHANDLER__
#define __IEVHANDLER__

#include "IInfo.hpp"
#include <memory>


/******************************************************************************/
class IEvHandler{
public:
  virtual void operator()(auto_ptr<Iinfo> info) = 0;
  virtual auto_ptr<IEvHandler> Clone() = 0;
  virtual ~IEvHandler(){}
};

#endif