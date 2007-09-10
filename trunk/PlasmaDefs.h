#ifndef _PLASMA_DEFS_H
#define _PLASMA_DEFS_H

#ifdef WIN32
  #ifdef MAKEDLL
    #define DllExport __declspec(dllexport)
  #else
    #ifdef NODLL
      #define DllExport
    #else
      #define DllExport __declspec(dllimport)
    #endif
  #endif
#else
  #define DllExport
#endif
#define DllClass class DllExport

typedef signed char byte;
typedef unsigned char ubyte;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed long int32;
typedef unsigned long uint32;
#ifdef WIN32
  typedef signed __int64 int64;
  typedef unsigned __int64 uint64;
#else
  typedef signed long long int64;
  typedef unsigned long long uint64;
#endif

#endif
