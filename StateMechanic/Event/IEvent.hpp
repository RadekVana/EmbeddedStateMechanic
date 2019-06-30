/*******************************************************************************
CREATED: 29.05.2019, by Vana Radek

DESCRIPTION:
Porvides basic interface for events

FILE: IEvent.hpp
*******************************************************************************/

#ifndef __IEVENT__
#define __IEVENT__

/******************************************************************************/
class IEvent{
  //copy/assign not implemented .. not copyable
  IEvent(const IEvent& s){}
  IEvent& operator=(const IEvent&){return *this;}
protected:
  //protected ctor - it is an interface
  IEvent(){}
public:
  virtual ~IEvent(){}
};



#endif