#ifndef __STRUCT_CMP_H
#define __STRUCT_CMP_H
#include "stdint.h"//size_t

/*



<0      sizeof(lhs) < sizeof(rhs)
        the first byte that does not match in both memory blocks has a lower 
        value in lhs than in rhs (if evaluated as unsigned char values)
0	the contents of both memory blocks are equal
        sizeof(lhs) > sizeof(rhs)
>0	the first byte that does not match in both memory blocks has a greater 
        value in lhs than in rhs (if evaluated as unsigned char values)
*/

template<class T, class U>
inline bool structcmp(T lhs,U rhs){
  size_t sol = sizeof(lhs);
  size_t sor = sizeof(rhs);  
  size_t diff = sol - sor;
  if (diff==0){
    return memcmp((const void*)&lhs,(const void*)&rhs, sizeof(lhs));
  }else{
    return diff;
  }

};

template<class T>
inline bool structcmp(T lhs,T rhs){
  return memcmp((const void*)&lhs,(const void*)&rhs, sizeof(lhs));
};
#endif