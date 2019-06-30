#ifndef __STRING_TO_VECTOR__H
#define __STRING_TO_VECTOR__H
#include "stdint.h"
#include <string>
#include <vector>
#include <queue>
#include <stdlib.h>     /* strtol */
//#include <sstream>

enum STR2INT_ERROR { SUCCESS, OVERFLOW, UNDERFLOW, INCONVERTIBLE };
//supports any number base from 2 to 36. If base is zero (the default) it will try to convert from any base.

class str2int{
public:
  enum RESULT { SUCCESS, OVERFLOW, UNDERFLOW, INCONVERTIBLE };
  //supports any number base from 2 to 36. If base is zero it will try to convert from any base.
  static RESULT s2i (int &i, char const *s, int base = 10){
      char *end;
      long  l;
      errno = 0;
      l = strtol(s, &end, base);
      #pragma diag_suppress=Pa084 //disable Warning[Pa084]: pointless integer comparison, the result is always false 
      if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
          return OVERFLOW;
      }
      if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
          return UNDERFLOW;
      }
      #pragma diag_default=Pa084 //pointless integer comparison, the result is always false to default
      if (*s == '\0' || *end != '\0') {
          return INCONVERTIBLE;
      }
      i = l;
      return SUCCESS;
  }
  static RESULT s2i (int &i, const string s, int base = 0){
    return s2i(i,s.c_str(),base);
  }
};



inline void string_to_v_u08(const string &s, vector<uint8_t> &v){
  string::const_iterator it;
  for(it = s.begin(); it!=s.end(); it++){
    v.push_back(*it);
  }
};


inline vector<uint8_t> string_to_u08(const string &s){

  vector<uint8_t> v;
  string_to_v_u08(s,v);
  return v;
};



inline void string_to_q_u08(const string &s, queue<uint8_t> &v){
  string::const_iterator it;
  for(it = s.begin(); it<s.end(); it++){
    v.push(*it);
  }
};

inline string my_substr(size_t &cut_front, size_t &len, string data){
  string ret;
  if (cut_front >= data.size()){
    cut_front   -= data.size();    
  }else{
    ret         = data.substr(cut_front, len);
//    Number of characters to include in the substring (if the string is shorter, 
//    as many characters as possible are used).
//    A value of string::npos indicates all characters until the end of the string.
    cut_front = 0;
    len -= ret.length();
    
  }
  return ret;

}
#endif