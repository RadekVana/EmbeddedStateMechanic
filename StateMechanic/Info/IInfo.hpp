/*******************************************************************************
CREATED: 29.05.2019, by Vana Radek

DESCRIPTION:
Info is mainly used by transitions. It contains informations from which state
to which state over which event a transition occurred. Child of Iinfo can also 
contain data.
 

FILE: IInfo.hpp
*******************************************************************************/

#ifndef __IINFO__
#define __IINFO__

#include "IState.hpp"
#include "IEvent.hpp"

/******************************************************************************/
//informations used by events
class Iinfo{
  const IState& From;
  const IState& To;  
  const IEvent& Ev;
public:
  Iinfo(const IState& from, const IState& to, const IEvent& ev):From(from),To(to),Ev(ev){}
  //virtual auto_ptr<Iinfo> Clone() const{ return auto_ptr<Iinfo>(new Iinfo(*this));}  
  //virtual auto_ptr<Iinfo> Clone() const{ auto_ptr<Iinfo> ret(new Iinfo(this->From,this->To, this->Ev)); return ret;} 
  
  const IState& GetFrom(){return From;}
  const IState& GetTo(){return To;} 
  virtual const IEvent& GetEv(){return Ev;}
  virtual ~Iinfo(){}
};

#endif