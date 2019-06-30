#include "MySorting.h"




char Sorting::AvgMedian(string pole, size_t n_vyloucit){
  vector<char> data(pole.begin(), pole.end());
  return AvgMedian(data, n_vyloucit);
}

char Sorting::Median(string pole){
  vector<char> data(pole.begin(), pole.end());
  return Median(data);
}

