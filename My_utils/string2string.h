#ifndef __STRING_TO_STRING__H
#define __STRING_TO_STRING__H

/*******************************************************************************
CREATED: 25.07.2019, by Vana Radek

DESCRIPTION:
Allow to use to_string on a string. Helps in templates.
Used it unit test templates when printing an error.

FILE: string2string.hpp
*******************************************************************************/

inline string& to_string (string& val){
  return val;
}

inline const string& to_string (const string& val){
  return val;
}
#endif