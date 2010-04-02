#ifndef _PLCONTROLLER_H
#define _PLCONTROLLER_H

#include "PRP/plCreatable.h"
#include "hsKeys.h"

DllClass plController : public plCreatable {
    CREATABLE(plController, kController, plCreatable)

public:
    static void WriteController(hsStream* S, plResManager* mgr, plController* controller);
};


DllClass plCompoundController : public plController {
    CREATABLE(plCompoundController, kCompoundController, plController)

protected:
    plController* fXController;
    plController* fYController;
    plController* fZController;

public:
    plCompoundController();
    virtual ~plCompoundController();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    class plTMController* convertToTMController();

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plController* getXController() const { return fXController; }
    plController* getYController() const { return fYController; }
    plController* getZController() const { return fZController; }

    void setXController(plController* controller);
    void setYController(plController* controller);
    void setZController(plController* controller);
};

#endif
