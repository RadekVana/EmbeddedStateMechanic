#include "StateMechanic.hpp"
#include "MyMutex.h"
  
/******************************************************************************/
//StateMachine
//dummy events in constructor - so I do not need to check if(some_auto_ptr.get() == NULL) when they are rised
StateMachine::StateMachine():
  transitionEv(new DummyEvHandler()),
  defaultTransitionEv(new DummyEvHandler()),
  transitionNotFoundEv(new DummyEvHandler()),
  faultedEv(new DummyEvHandler()),
  AnEventIsBeingFired(0)
{
  for (size_t i = 0; i < DS_COUNT; ++i){
    DefaultStates.push_back(new State(*this));
  }
  
  //set all default states to transits into itself
  // == all transitions are defined.  
  for (size_t i = 0; i < DS_COUNT; ++i){
    //cannot merge for cycles, iterators might not be valid
    DefaultStatesTransitions.push_back(DefaultStates.begin()+i);
  }

  //DS_UNINICIALIZED changes to DS_FAULTED
  DefaultStatesTransitions.push_back(DefaultStates.begin()+DS_UNINICIALIZED);
  
  //entry handlers for faulted is changed by SinkFaultedEv
}


//const State* == NULL indicates an error
State* StateMachine::CreateInitialState(auto_ptr<EvHandler> entry, auto_ptr<EvHandler> exit){
  Mutex M;
  //empty means there is no initial state .. I want that
  if (!states.empty()) return NULL;
  return __createState(entry, exit); 
}

State* StateMachine::CreateState(auto_ptr<EvHandler> entry, auto_ptr<EvHandler> exit){
  Mutex M;
  //empty means there is no initial state
  if (states.empty()) return NULL;
  return __createState(entry, exit);
}

State* StateMachine::__createState(auto_ptr<EvHandler> entry, auto_ptr<EvHandler> exit){
  Mutex M;
  states.push_back(new State(*this, entry, exit));
  //adding could invalidate iterator need to Reset
  Reset();
  return *(states.end() -1);
}

void StateMachine::Reset(){
  Mutex M;
  currentState = states.begin();
  faulted = false;
}

/******************************************************************************/
//registration o events
void StateMachine::SinkTransitionEv(auto_ptr<EvHandler> eh){
  transitionEv = eh;
}

void StateMachine::SinkTransitionNotFoundEv(auto_ptr<EvHandler> eh){
  transitionNotFoundEv = eh;
}

void StateMachine::SinkFaultedEv(auto_ptr<EvHandler> eh){
  //entry handler for faulted state
  DefaultStates[DS_FAULTED]->SinkEntryHandler(eh);
}
//end registration o events
/******************************************************************************/

StateMachine::DEFAULT_STATES StateMachine::getDefaultId(vector<State*>::iterator state){
  if (!isDefaultState(state)) return DS_COUNT;
  return static_cast<DEFAULT_STATES>(state - DefaultStates.begin());
}

bool StateMachine::isDefaultState(vector<State*>::iterator state){
  return (static_cast<size_t>(DefaultStates.end() - state)) <  static_cast<size_t>(DS_COUNT);
}

//default transitions are fired on any event - if state is one of default states
//they must be created in runtime - or there would be one transmission for every 
//combination of actual state, next state and event
//behavior of default states is similar to behavior of "normal" states 
//they change state using _changeState_FireEvents just like "normals"
void StateMachine::defaultTransition(vector<State*>::iterator itActualState, 
                                     vector<State*>::iterator itNextState, 
                                     IEvent& ev){
  //create info
  auto_ptr<Iinfo> errInfo(new Iinfo(**itActualState, **itNextState, ev));
  //create event handler - default - empty
  auto_ptr<IEvHandler> EvH(new DummyEvHandler);
  //default guard
  auto_ptr<ITransitionGuard> grd (new DummyTransitionGuard);
  //create transmission
  InnerTransition tr(errInfo, EvH, grd);
  //activate next state and fire events
  _changeState_FireEvents(tr, *defaultTransitionEv, itNextState, auto_ptr<IFiredData>(new IFiredData));//*tr.EvH - dummy event sinked by Transition constructor
}

/******************************************************************************/
//comparer for RequestEventFireFromEvent
//it checks state and firedData
struct IsFromStateWithGuards {
  IsFromStateWithGuards(const IState* s, const IFiredData* firedData) : state(s),_firedData(firedData){}
  bool operator()(const ITransition* t) const { 
    return (&(t->GetInfo().GetFrom()) == state) && 
      (t->EvaluateGuard(_firedData->Clone()));
  }
  const IState* state;
  const IFiredData* _firedData;
};

//first transmission event, than state leave than new state enter
bool StateMachine::RequestEventFireFromEvent(EventFireData efd){
  //is not save in multi thread, just protects from recursive transitions
  if(IsAnEventBeingFired()){
  //enque
    return enque(efd);
  }
  
  bool ret = __requestEventFireFromEvent(efd);

  while(!evQueue.empty()){
    if(!deque()) ret = false;
  }
  
  return ret;
}


//first transmission event, than state leave than new state enter
bool StateMachine::__requestEventFireFromEvent(EventFireData efd){
  const vector<ITransition*>& transitions = efd.GetTransitions();
  IEvent& ev = efd.GetEvent();
  
  //lock to force enque
  EventFireLocker lck(*this);

  vector<State*>::iterator itActualState = currentState;
  DEFAULT_STATES ID = getDefaultId(itActualState);
  
  //check if state is one of default states 
  if (ID != DS_COUNT) {//it is
     //fired data not relevant
    vector<State*>::iterator itNextState = DefaultStatesTransitions[ID];//find next state
    defaultTransition(itActualState, itNextState, ev);//fire events and change state
    return false;
  }
  
  //find transition if exists
  vector<ITransition*>::const_iterator it_transition = find_if(transitions.begin(), transitions.end(), 
                                                               IsFromStateWithGuards(*itActualState,efd.GetData()));
  
  //does not exist .. do nothing just fire event and return false
  //info is in transitions, do not have it, must create new info
  if (it_transition == transitions.end()) {
    auto_ptr<Iinfo> errInfo(new Iinfo(**itActualState, **itActualState, ev));
    (*transitionNotFoundEv)(errInfo); return false;
  };

  //find next state
  //do not have dynamic_cast, have to use reinterpret_cast
  const State* ptrStateToFnd = reinterpret_cast<const State*>(&((*it_transition)->GetInfo().GetTo()));
  vector<State*>::iterator nextState = find(states.begin(), states.end(), ptrStateToFnd);
  
  //this should never happen, but still it is better to check it
  if (nextState == states.end()) return false;
  
  //transition exists. Transitions have valid copy constructors
  _changeState_FireEvents(**it_transition, *transitionEv, nextState, efd.SourceData());

  return true;
}

bool StateMachine::enque(EventFireData efd){
  evQueue.push(efd);
  return true;
}

bool StateMachine::deque(){
  bool ret = __requestEventFireFromEvent(evQueue.front());
  evQueue.pop();
  return ret;
}


/******************************************************************************/
State& StateMachine::GetCurrentState() const{
  return **currentState;
}

State* StateMachine::GetInitialState() const{
  if (states.empty()) return NULL;
  return *states.begin();
}
  

StateMachine::~StateMachine(){
  Mutex M;
  for (currentState= states.begin(); currentState != states.end(); ++currentState){
    delete(*currentState);
  }
  for (currentState= DefaultStates.begin(); currentState != DefaultStates.end(); ++currentState){
    delete(*currentState);
  }
} 

/******************************************************************************/
//state exit is fired
//event handler is called 
//state is changed 
//state enter is fired
//transition is fired
void StateMachine::_changeState_FireEvents(const ITransition& transition, IEvHandler& transmEv,
                               vector<State*>::iterator to, auto_ptr<IFiredData> firedData){
  //state leave
  transition.FireExit();
  
  //event
  transition.FireEventHandler(firedData);
  
  //change state
  currentState = to;
  
  //state enter
  transition.FireEntry();
  
  //transition
  transmEv(transition.SourceInfo());
 
}