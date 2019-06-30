#include "AbstractTransition.hpp"
#include "State.hpp"

/******************************************************************************/
//AbstractTransition

AbstractTransition::AbstractTransition(auto_ptr<Iinfo> _info, auto_ptr<IEvHandler> evh, 
  auto_ptr<ITransitionGuard> grd):
  info(_info), EvH(evh), guard(grd){}
 
/*AbstractTransition& AbstractTransition::operator = (const AbstractTransition& other){
  if (this != &other) { // protect against invalid self-assignment

  }
  
  return *this;
}*/

  
AbstractTransition& AbstractTransition::operator = (AbstractTransition other){
  Swap(other);
  return *this;
}
  
//info is not ment to be replaced by its child 
AbstractTransition::AbstractTransition(const AbstractTransition& other):
  info(auto_ptr<Iinfo>(new Iinfo(*other.info))),EvH(other.EvH->Clone()), guard(other.guard->Clone()){
}  

void AbstractTransition::Swap(AbstractTransition & other){
  this->info = other.info;
  this->EvH = other.EvH;
  this->guard = other.guard;
}

Iinfo& AbstractTransition::GetInfo() const{
  return *info;
}

auto_ptr<Iinfo> AbstractTransition::SourceInfo() const{
  return auto_ptr<Iinfo>(new Iinfo(*info));
}


void AbstractTransition::FireEventHandler(auto_ptr<IFiredData> firedData) const{
  (*(EvH))(CreateIinfoWithData(firedData));
}


bool AbstractTransition::EvaluateGuard(auto_ptr<IFiredData> firedData) const{
  return (*guard)(CreateIinfoWithData(firedData));
}

auto_ptr<Iinfo> AbstractTransition::CreateIinfoWithData(auto_ptr<IFiredData> firedData) const{
  const AbstractEvent& evnt = reinterpret_cast<const AbstractEvent&>(info->GetEv());
  return evnt.CreateIinfo(info->GetFrom(),info->GetTo(),firedData);
}