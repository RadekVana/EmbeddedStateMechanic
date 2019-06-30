/*******************************************************************************
CREATED: 29.05.2019, by Vana Radek

DESCRIPTION:

Handlers actions to be called when something happened like state change, 
event fire etc. Lambdas would be nace, but C++03 does not have them.

FILE: EvHandler.hpp
*******************************************************************************/

#ifndef __EVHANDLER__
#define __EVHANDLER__

#include "IEvHandler.hpp"
#include "InfoTemplate.hpp"

/******************************************************************************/
//event handler with no data
class EvHandler: public IEvHandler{
public:
  virtual void operator()(auto_ptr<Iinfo> info){}
  virtual auto_ptr<IEvHandler> Clone() = 0;
};

/******************************************************************************/
//dummy
class DummyEvHandler: public EvHandler{
public:
  virtual auto_ptr<IEvHandler> Clone(){auto_ptr<IEvHandler> ret(new DummyEvHandler()); return ret;}
};

/******************************************************************************/
//event handler template with data
template <class T>
class EvHandlerWithData: public IEvHandler{
protected:
  virtual void _do(auto_ptr<Info<T> > info){}//overload this
public:
  //do not overload this, this should be sealed
  virtual void operator()(auto_ptr<Iinfo> info){
    auto_ptr<Info<T> > aptr(reinterpret_cast<Info<T> *>(info.release()));
    _do(aptr);
  }
  virtual auto_ptr<IEvHandler> Clone() = 0;
};

/******************************************************************************/
//dummy template with data
template <class T>
class DummyEvHandlerWithData: public EvHandlerWithData<T>{
public:
  virtual auto_ptr<IEvHandler> Clone(){auto_ptr<IEvHandler> ret(new DummyEvHandlerWithData()); return ret;}
};


#endif