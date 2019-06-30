#include "AbstractEvents.hpp"
#include "Transition.hpp"
/******************************************************************************/
//AbstractEvent

//finds an transition from an state
//vector<ITransition*>::iterator AbstractEvent::getTransitionFromState(IState* from){
//  vector<ITransition*>::iterator it;
//  for(it = transitions.begin(); it != transitions.end(); ++it){
//    if(&((*it)->GetInfo().GetFrom()) == from ) break;//have it
//  }
//  return it;
//}


//if i could use unique_ptr, destructor body would not be needed
AbstractEvent::~AbstractEvent(){
  for (vector<ITransition*>::iterator it = transitions.begin(); it != transitions.end(); ++it){
    delete(*it);
  }
}

//this can add any transition, childs use this
bool AbstractEvent::__addTransition(const IStateWithMachineRef& from, const IStateWithMachineRef& to, 
                            auto_ptr<IEvHandler> evh, auto_ptr<ITransitionGuard> grd,
                            transitionCreator trCr){
  //there is no checking if same transition exists
  
  //check if both states belong to same machine
  if(&from.GetParentStateMachine() != &to.GetParentStateMachine()) return false;
  //first transmission registers machine
  if(machine == NULL) machine = &from.GetParentStateMachine();
  //other transitions must have same machine
  else if(machine != &from.GetParentStateMachine())return false;
  
  //member fce version would be
  //ITransition* ptr = ((this)->*(trCr))(CreateBaseIinfo(from, to),evh,grd);
  
  //non member fce is used
  ITransition* ptr = (*(trCr))(CreateBaseIinfo(from, to),evh,grd);//transition needs Iinfo, not childs
  transitions.push_back(ptr);
  return true;
}

//create an info with no data
auto_ptr<Iinfo> AbstractEvent::CreateBaseIinfo(const IState& from, const IState& to)const{
  auto_ptr<Iinfo> ret(new Iinfo(from, to, *this));
  return ret;
}


//factory methods to create transitions - non member (static)
ITransition* AbstractEvent::createInnerTransition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh, auto_ptr<ITransitionGuard> grd){
  return new InnerTransition(info,evh,grd);
}

ITransition* AbstractEvent::createTransition(auto_ptr<Iinfo> info, auto_ptr<IEvHandler> evh, auto_ptr<ITransitionGuard> grd){
  return new Transition(info,evh,grd);
} 