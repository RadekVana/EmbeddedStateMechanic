#ifndef _SMART_ENUM_
#define _SMART_ENUM_


#include "stdint.h"



#include <stdarg.h> 

int FindMax (int n, ...);

struct SmartEnum
{
  explicit SmartEnum(int v) : value_(v) { }
   // explicit // if you have it!
  
  operator int() const { return value_; }

protected:
  int value_;
};






struct dorazy_enum: public SmartEnum
{
    static const dorazy_enum Nenacteny;
    static const dorazy_enum Nacteny;
    
    explicit dorazy_enum(int v) : SmartEnum(v) { }
};

struct dorazy_enum2: public dorazy_enum
{
    static const dorazy_enum2 Nacitam;

    explicit dorazy_enum2(int v) : dorazy_enum(v) { }
    dorazy_enum2(const dorazy_enum& v) : dorazy_enum(v) { }
};

struct regul_enum: public SmartEnum
{
    static const regul_enum Reguluji;
    static const regul_enum Nereguluji;
    
    explicit regul_enum(int v) : SmartEnum(v) { }
};

struct all_enum: public SmartEnum
{
    explicit all_enum(int v) : SmartEnum(v) { }
    all_enum(regul_enum v) : SmartEnum(int(v)) { }
    all_enum(dorazy_enum v) : SmartEnum(int(v)) { }
};



#endif