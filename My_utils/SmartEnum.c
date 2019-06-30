#include "SmartEnum.h"

int FindMax (int n, ...)
{
  int i,val,largest;
  va_list vl;
  va_start(vl,n);
  largest=va_arg(vl,int);
  for (i=1;i<n;i++)
  {
    val=va_arg(vl,int);
    largest=(largest>val)?largest:val;
  }
  va_end(vl);
  return largest;
}

const dorazy_enum dorazy_enum::Nenacteny(0);
const dorazy_enum  dorazy_enum::Nacteny(1);


const dorazy_enum2 dorazy_enum2::Nacitam(2);


const regul_enum regul_enum::Reguluji(0);
const regul_enum regul_enum::Nereguluji(1);


