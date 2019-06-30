#ifndef __FNC_TYPEDEFS__H
#define __FNC_TYPEDEFS__H
#include "stdint.h"
typedef void    (*fnc)(); 
typedef void    (*fncChar)(char); 
typedef void    (*fncInt32)(int32_t); 
typedef void    (*fncDouble)(double); 
typedef void    (*fncStr)(const char*); 
#endif