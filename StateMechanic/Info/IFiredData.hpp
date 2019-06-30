/*******************************************************************************
CREATED: 13.06.2019, by Vana Radek

DESCRIPTION:
Interface for data sent to State Machine when an event is fired = parent for any data.
Sometimes Info is created at runtime. In this case separate data are needed.

FILE: IFiredData.hpp
*******************************************************************************/

#ifndef __IFIREDDATA__
#define __IFIREDDATA__


/******************************************************************************/
//#include "IInfo.hpp"
#include <memory>
#include <vector>

class IFiredData{

public:
  //IFiredData has no data
  //virtual auto_ptr<Iinfo> GenerateInfoWithData(auto_ptr<Iinfo> info){return info;}
  virtual ~IFiredData(){}
  virtual auto_ptr<IFiredData> Clone() const{return auto_ptr<IFiredData>(new IFiredData);}
};


#endif