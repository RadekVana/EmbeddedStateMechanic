#ifndef __MOCKEVHANDLER__HPP
#define __MOCKEVHANDLER__HPP

#include "IEvHandler.hpp"
#include "InfoTemplate.hpp"

/******************************************************************************/
//event handler counting calls
class EvHandlerCountingCalls: public EvHandler{
  size_t& _cnt;
public:
  EvHandlerCountingCalls(size_t& cnt):_cnt(cnt){}
  virtual void operator()(auto_ptr<Iinfo> info){++_cnt;}
  virtual auto_ptr<IEvHandler> Clone(){auto_ptr<IEvHandler> ret(new EvHandlerCountingCalls(_cnt)); return ret;}
};




/******************************************************************************/
//event handler template setting an variable
template <class T>
class EvHandlerSettingVar: public EvHandlerWithData<T>{
  T& _var;
protected:
  virtual void _do(auto_ptr<Info<T> > info){_var = info->GetData();}//overload this  
public:
  EvHandlerSettingVar(T& var):_var(var){}
  virtual auto_ptr<IEvHandler> Clone(){auto_ptr<IEvHandler> ret(new EvHandlerSettingVar(_var)); return ret;}
};

/******************************************************************************/
//to be able check if it was cloned right
class EvHandlerWithPInt: public EvHandler{
  
public:
  int* PInt;
  
  EvHandlerWithPInt(int* pInt):PInt(pInt){}
  virtual auto_ptr<IEvHandler> Clone(){auto_ptr<IEvHandler> ret(new EvHandlerWithPInt(PInt)); return ret;}
};
#endif