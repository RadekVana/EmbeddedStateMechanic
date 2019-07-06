#ifndef __TESTEVETTHANDLERS_HPP
#define __TESTEVETTHANDLERS_HPP

/*******************************************************************************
DESCRIPTION:
  --

CREATED: 23.05.2019, by vana
To be used with unity in integration tests of state mechanic
*******************************************************************************/


#include "StateMechanic.hpp"
#include <vector>
/******************************************************************************/
//Event Handlers
//TestEvHandler counts how many times it was called in global
class TestEvHandler: public EvHandler{
public:
  virtual void operator()(auto_ptr<Iinfo> info){++static_call_count;}
  virtual auto_ptr<IEvHandler> Clone(){return auto_ptr<IEvHandler>(new TestEvHandler());}

  static uint32_t static_call_count;//global count
};

/******************************************************************************/
//stores int data into static variable
class TestIntEvHandler: public EvHandlerWithData<int>{
public:
  virtual void _do(auto_ptr<Info<int> > info){
    static_int = info->GetData();
  }
  virtual auto_ptr<IEvHandler> Clone(){return auto_ptr<IEvHandler>(new TestIntEvHandler());}

  static int static_int;
};
/******************************************************************************/
//fires an event and stores ID into an vector
class TestEvHandlerFireingAnEv: public EvHandler{
  Event &ev;
  int _ID;
public:
  TestEvHandlerFireingAnEv(Event& e, int ID, vector<int>& calls):ev(e),_ID(ID),Calls(calls){}
  virtual void operator()(auto_ptr<Iinfo> info);
  virtual auto_ptr<IEvHandler> Clone();
  vector<int>& Calls;
};

/******************************************************************************/
//fires vector of events
class TestEvHandlerFireingVectorOfEv: public EvHandler{
  vector<Event *> events;
public:
  TestEvHandlerFireingVectorOfEv(){}
  TestEvHandlerFireingVectorOfEv(const vector<Event *> evnts):events(evnts){}
  void AddEv(Event &e){events.push_back(&e);}
  virtual void operator()(auto_ptr<Iinfo> info);
  virtual auto_ptr<IEvHandler> Clone();
};

/******************************************************************************/
struct TestData{
  string HandlerName;
  uint32_t AddrFrom;
  uint32_t AddrTo;
  uint32_t AddrEv;
  
  TestData():AddrFrom(0), AddrTo(0), AddrEv(0){}
  
  TestData(string name, uint32_t aFrom, uint32_t aTo, uint32_t aEv):
    HandlerName(name), AddrFrom(aFrom), AddrTo(aTo), AddrEv(aEv){}
};

class LoggingEvHandler: public EvHandler{
  string name;
public:
  LoggingEvHandler(const char* txt, vector<TestData>& dataFromTests):name(txt),DataFromTests(dataFromTests){}
  virtual void operator()(auto_ptr<Iinfo> info);
  virtual auto_ptr<IEvHandler> Clone();
  
  vector<TestData>& DataFromTests;
};

#endif