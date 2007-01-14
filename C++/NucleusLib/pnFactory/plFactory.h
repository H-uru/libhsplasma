#ifndef _PLFACTORY_H
#define _PLFACTORY_H

#include "plCreatable.h"

class plFactory {
private:
    PlasmaVer ver;

public:
    plFactory();
    plFactory(PlasmaVer pv);
    ~plFactory();

    PlasmaVer getVer();
    void setVer(PlasmaVer pv, bool mutate = false);

    plCreatable* Create(short typeIdx);
};

#endif

