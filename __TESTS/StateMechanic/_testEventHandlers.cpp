#include "_testEventHandlers.hpp"

//static initializations
uint32_t TestEvHandler::static_call_count = 0;
int TestIntEvHandler::static_int = 0;


/******************************************************************************/
//TestEvHandlerFireingAnEv


//static initializations
vector<int> TestEvHandlerFireingAnEv::calls;
void TestEvHandlerFireingAnEv::operator()(auto_ptr<Iinfo> info){
  calls.push_back(_ID); 
  ev.TryFire();
}

auto_ptr<IEvHandler> TestEvHandlerFireingAnEv::Clone(){
  return auto_ptr<IEvHandler>(new TestEvHandlerFireingAnEv(ev, _ID));
}



/******************************************************************************/
//TestEvHandlerFireingVectorOfEv

void TestEvHandlerFireingVectorOfEv::operator()(auto_ptr<Iinfo> info){
  vector<Event *>::iterator it;
  for(it = events.begin(); it != events.end(); ++it){
    (*it)->TryFire();
  }
}

auto_ptr<IEvHandler> TestEvHandlerFireingVectorOfEv::Clone(){
  return auto_ptr<IEvHandler>(new TestEvHandlerFireingVectorOfEv(events));
}



/******************************************************************************/
//LoggingEvHandler

vector<TestData> LoggingEvHandler::dataFromTests;

void LoggingEvHandler::operator()(auto_ptr<Iinfo> info){
  TestData dt(name, reinterpret_cast<uint32_t>(&(info->GetFrom())), 
                    reinterpret_cast<uint32_t>(&(info->GetTo())), 
                    reinterpret_cast<uint32_t>(&(info->GetEv())));
  dataFromTests.push_back(dt);                                      
}

auto_ptr<IEvHandler> LoggingEvHandler::Clone(){
  return auto_ptr<IEvHandler>(new LoggingEvHandler(name.c_str()));
}