#ifndef _PREINCLUDE_H
#define _PREINCLUDE_H

#include <string>
#include <sstream>



template <typename T>
inline string __to_string ( T val )
{
   ostringstream ss;
   ss << val;
   return ss.str();
}


//c++ 11 definuje v std
//string to_string (int val);
//string to_string (long val);
//string to_string (long long val);
//string to_string (unsigned val);
//string to_string (unsigned long val);
//string to_string (unsigned long long val);
//string to_string (float val);
//string to_string (double val);
//string to_string (long double val);
//Convert numerical value to string
//Returns a string with the representation of val.
//
//The format used is the same that printf would print for the corresponding type:



inline string to_string (int val){
  return __to_string(val);  
}

inline string to_string (long val){
  return __to_string(val);
}

inline string to_string (long long val){
  return __to_string(val);
}

inline string to_string (unsigned val){
  return __to_string(val);
}

inline string to_string (unsigned long val){
  return __to_string(val);
}

inline string to_string (unsigned long long val){
  return __to_string(val);
}

inline string to_string (float val){
  return __to_string(val);
}

inline string to_string (double val){
  return __to_string(val);
}

inline string to_string (long double val){
  return __to_string(val);
}

#include <stdint.h>
#include <stdlib.h>


#ifdef __cplusplus
// global override of operator new, delete, new[] and delete[]
void* operator new (size_t bytes); 
void operator delete (void *p);
#endif

uint64_t _get_malloced          ();
uint64_t _get_freed             ();
uint64_t _get_freeing_null      ();
uint64_t _get_mallocing_err     ();
uint64_t _get_size_malloced     ();
uint64_t _get_size_freed        ();
uint64_t _get_size_mallocing_err();




#endif
//
//    #pragma diag_suppress=Pe186 //disable pointles comparation with zero warning
//    #pragma diag_default=Pe186 //pointles comparation with zero warning to default

