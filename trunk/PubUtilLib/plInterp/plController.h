#ifndef _PLCONTROLLER_H
#define _PLCONTROLLER_H

#include "NucleusLib/pnFactory/plCreatable.h"
#include "CoreLib/hsTArray.hpp"
#include "hsKeys.h"

DllClass plController : public plCreatable {
public:
    plController();
    virtual ~plController();

    DECLARE_CREATABLE(plController)
};

DllClass plCompoundController : public plController {
protected:
    plController* fXController;
    plController* fYController;
    plController* fZController;

public:
    plCompoundController();
    virtual ~plCompoundController();

    DECLARE_CREATABLE(plCompoundController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    class plTMController* convertToTMController();
};

#endif
