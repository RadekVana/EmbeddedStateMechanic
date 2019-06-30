#include "preinclude.h"

#include <cstdarg>//va_list, va_start, va_end


#ifdef __cplusplus
// global override of operator new, delete, new[] and delete[]
//void* operator new (size_t bytes) { return MyMalloc(bytes); } 
//void operator delete (void *p) { MyFree(p); }
uint64_t _malloced              = 0;
uint64_t _freed                 = 0;
uint64_t _freeing_null          = 0;
uint64_t _mallocing_err         = 0;
uint64_t _size_malloced         = 0;
uint64_t _size_freed            = 0;
uint64_t _size_mallocing_err    = 0;

uint64_t _get_malloced          (){return _malloced          ;}
uint64_t _get_freed             (){return _freed             ;}
uint64_t _get_freeing_null      (){return _freeing_null      ;}
uint64_t _get_mallocing_err     (){return _mallocing_err     ;}
uint64_t _get_size_malloced     (){return _size_malloced     ;}
uint64_t _get_size_freed        (){return _size_freed        ;}
uint64_t _get_size_mallocing_err(){return _size_mallocing_err;}


void* operator new (size_t bytes) { 
  
  void *p = malloc(bytes); 
  if (p == NULL) {
    _mallocing_err++;
    _size_mallocing_err += bytes;
    //Main_WDT_force_reset_debug_print_ERROR();
  }
  else{
    _malloced ++;
    _size_malloced += bytes;
  }
  return p;
} 

//pozor fronta zpusobuje freeing error
void operator delete (void *p) { 
  if (p == NULL){
    _freeing_null++;
    //_size_freeing_err += 
    return;
} 
  _freed ++;
  free(p); 
  p = NULL;
}
#endif