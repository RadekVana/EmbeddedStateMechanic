#ifndef __MYSORTING_T__C
#define __MYSORTING_T__C

#include "MySorting.h"



template <class T> 
T Sorting::AvgMedian(vector<T> pole, size_t n_vyloucit){
  T pom;
  size_t n_o_samples = pole.size();
  //vylouceni X nejvetsich a nejmensich hodnot
  //podobne jako bubblesort
  for (size_t j = 0; j < n_vyloucit; ++j){
    for (size_t i = j; i < n_o_samples - j - 1; ++i){//tady vybubla pri kazdym prubehu 1 nejvetsi
      if (pole[i] > pole[i+1]){
        pom = pole[i];
        pole[i] = pole[i+1];
        pole[i+1] = pom;      
      }
    }
    for (size_t i = n_o_samples - j - 2; i > j ; --i){//tady vybubla pri kazdym prubehu 1 nejmensi
      //stihl mi jeden nejvetsi prvek probublat - proto ta 2
      if (pole[i] < pole[i-1]){
        pom = pole[i];
        pole[i] = pole[i-1];
        pole[i-1] = pom;      
      }
    }
  }
    
//udelam prumer ze stredu
  T prumer = pole[n_vyloucit];
  for (size_t i = n_vyloucit + 1; i < n_o_samples - n_vyloucit; i++)prumer += pole[i];
  prumer /= n_o_samples - n_vyloucit*2;
  
  return prumer;
}

template <class T> 
T Sorting::Median(vector<T> pole){
  size_t n_vyloucit = (pole.size() - 1)/2;
  return AvgMedian(pole,n_vyloucit);

}



#endif