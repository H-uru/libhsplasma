#ifndef _PLFACTORY_H
#define _PLFACTORY_H

#include "plCreatable.h"
#include "DynLib/pdUnifiedTypeMap.h"

class plFactory {
public:
    static plCreatable* Create(short typeIdx);
    static plCreatable* Create(short typeIdx, PlasmaVer ver);
    static plCreatable* Create(const char* typeName);
    static const char* ClassName(short typeIdx);
    static const char* ClassName(short typeIdx, PlasmaVer ver);
    static short ClassIndex(const char* typeName);
};

#endif
