#ifndef __MYSORTING__H
#define __MYSORTING__H
#include "stdint.h"
#include <vector>



//na konci inkluduju MySorting_T.c
//to muze obsahovat pouze definice sablon
//zbytek musi byt v MySorting.c

class Sorting{
public:
  template <class T> 
  static T AvgMedian(vector<T> pole, size_t n_vyloucit);
  
  template <class T> 
  static T Median(vector<T> pole);
  
  static char AvgMedian(string pole, size_t n_vyloucit);
  
  static char Median(string pole);
  
};

#include "MySorting_T.c"
#endif