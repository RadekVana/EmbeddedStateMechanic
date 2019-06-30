/*******************************************************************************
CREATED: 06.06.2019, by Vana Radek

DESCRIPTION:
Version of IInfo containing data.
 

FILE: InfoTemplate.hpp
*******************************************************************************/

#ifndef __INFOTEMPLATE__
#define __INFOTEMPLATE__

#include "IInfo.hpp"
#include "AbstractEvents.hpp"
/******************************************************************************/
//informations used by events with data 
template <class T>
class Info: public Iinfo{
  T data;
public:
  Info(const IState& from, const IState& to, const IEventWithData<T>& ev, T dt):Iinfo(from, to, ev), data(dt){}
  //Info(const Iinfo& from, const IState& to, const IEventWithData<T>& ev, T dt):Iinfo(from, to, ev), data(dt){}
  //virtual auto_ptr<Info<T> > Clone() const{ return auto_ptr<Info<T> >(new Info<T>(*this));} //not covariant
  //virtual auto_ptr<Iinfo> Clone() const{ return auto_ptr<Info<T> >(new Info<T>(*this));} 
  
  //cannot use dynamic_cast in IAR - Error[Pe878]: Embedded C++ does not support run-time type information 
  virtual const IEventWithData<T>& getEv(){return reinterpret_cast<const IEventWithData<T>& >(GetEv());} 
  
  T GetData(){return data;}
  void SetData(T d){data = d;}
};
#endif