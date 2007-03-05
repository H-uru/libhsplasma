#ifndef _PLASMA_DEFS_H
#define _PLASMA_DEFS_H

#ifdef WIN32
  #ifdef _MAKEDLL_
    #define DllExport __declspec(dllexport)
  #else
    #define DllExport __declspec(dllimport)
  #endif
#else
  #define DllExport
#endif

#endif
