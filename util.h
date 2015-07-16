#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
#include <sstream>
#include <iomanip>
//將class T轉成字串
template <class T>
inline std::basic_string<wchar_t> ttos(const T& t, int precision = 2)
{	
  std::ostringstream buffer;
  buffer << std::fixed << std::setprecision(precision) << t;
  std::basic_string<char> c = buffer.str();
  const size_t cSize = buffer.str().length()+1;
  wchar_t* wc = new wchar_t[cSize];
  const char* src = c.c_str(); 
  //size_t mbstowcs(wchar_t* dest, const char* src, size_t max);
  mbstowcs(wc, src, cSize);
  return wc;
}
inline std::basic_string<wchar_t> btos(bool b)
{
  if (b) return L"true";
  return L"false";
}
#endif