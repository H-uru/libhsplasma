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

typedef signed char hsByte;
typedef unsigned char hsUbyte;
typedef signed short hsInt16;
typedef unsigned short hsUint16;
typedef signed long hsInt32;
typedef unsigned long hsUint32;
#ifdef WIN32
  typedef signed __int64 hsInt64;
  typedef unsigned __int64 hsUint64;
#else
  typedef signed long long hsInt64;
  typedef unsigned long long hsUint64;
#endif

#endif
