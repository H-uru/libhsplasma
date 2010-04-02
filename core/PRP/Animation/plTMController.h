#ifndef _PLTMCONTROLLER_H
#define _PLTMCONTROLLER_H

#include "plPosController.h"
#include "plRotController.h"
#include "plScaleController.h"

DllClass plTMController : public plController {
    CREATABLE(plTMController, kTMController, plController)

protected:
    plPosController* fPosController;
    plRotController* fRotController;
    plScaleController* fScaleController;

public:
    plTMController();
    virtual ~plTMController();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    plCompoundController* convertToCompoundController();

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plPosController* getPosController() const { return fPosController; }
    plRotController* getRotController() const { return fRotController; }
    plScaleController* getScaleController() const { return fScaleController; }

    void setPosController(plPosController* controller);
    void setRotController(plRotController* controller);
    void setScaleController(plScaleController* controller);
};

#endif
