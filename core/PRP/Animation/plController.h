#ifndef _PLCONTROLLER_H
#define _PLCONTROLLER_H

#include "PRP/plCreatable.h"
#include "Util/hsTArray.hpp"
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
    class plTMController* convertToTMController();

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plController* getXController() const;
    plController* getYController() const;
    plController* getZController() const;

    void setXController(plController* controller);
    void setYController(plController* controller);
    void setZController(plController* controller);
};

#endif
