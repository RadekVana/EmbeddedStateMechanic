#include "MockInfo.hpp"
#include "MockEvent.hpp"
#include "MockState.hpp"

/******************************************************************************/
//static objects to be pointed by refs in ctor
static const MockEvent _ev;
static const MockState _from;
static const MockState _to;

/******************************************************************************/
//simplified ctor

MockInfo::MockInfo():Iinfo(_from, _to, _ev){}