/*******************************************************************************
CREATED: 13.06.2019, by Vana Radek

DESCRIPTION:
Data sent to State Machine when an event is fired

FILE: IFiredData.hpp
*******************************************************************************/

#ifndef __FIREDDATA__
#define __FIREDDATA__


/******************************************************************************/
#include "IFiredData.hpp"
//#include "InfoTemplate.hpp"

template <class T>
class FiredData: public IFiredData{
  T _data;	
public:
//  virtual auto_ptr<Iinfo> GenerateInfoWithData(auto_ptr<Iinfo> info){
//    auto_ptr<Iinfo> ret = auto_ptr<Info<T> >(new Info<T>() );
//    return info;}
  FiredData(T data):_data(data){}
  T Get()const {return _data;}
  void Set(T data){_data = data;}
  virtual auto_ptr<IFiredData> Clone() const{return auto_ptr<IFiredData>(new FiredData(_data));}

};
#endif