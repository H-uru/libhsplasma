#ifndef _PLASMA_DEFS_H
#define _PLASMA_DEFS_H

#ifdef WIN32
  #ifdef MAKEDLL
    #define DllExport __declspec(dllexport)
  #else
    #define DllExport __declspec(dllimport)
  #endif
#else
  #define DllExport
#endif
#define DllClass class DllExport

#endif
