#ifndef __MOCKSTRUCT__HPP
#define __MOCKSTRUCT__HPP


/******************************************************************************/
//mock objects used for test

struct mockStruct{
  double d;
  bool b;
  mockStruct():d(0),b(true){}
  mockStruct(double _d, bool _b):d(_d),b(_b){}
  
  friend bool operator==(const mockStruct& lhs, const mockStruct& rhs){ return lhs.d == rhs.d && lhs.b == rhs.b; }
  friend bool operator!=(const mockStruct& lhs, const mockStruct& rhs){ return !(lhs == rhs); }
};

//so an error in tests can be printed
//mockStruct can be used in templates just like basic types
inline string to_string (mockStruct val){
   ostringstream ss;
   ss << val.d;
   ss << ";";
   ss << val.b;
   return ss.str();
}

#endif