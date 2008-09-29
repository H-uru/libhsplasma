#ifndef _PLKEYCONTROLLERS_H
#define _PLKEYCONTROLLERS_H

#include "plLeafController.h"
#include "UruKeys.h"

// These are slightly simplified from Uru's versions, mostly for the sake of
// compatibility with Live/EOA's formats

DllClass plEaseController : public plLeafController {
protected:
    hsTArray<ScalarKeyFrame> fEaseKeys;

public:
    plEaseController();
    virtual ~plEaseController();

    DECLARE_CREATABLE(plEaseController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plMatrix33Controller : public plLeafController {
protected:
    hsTArray<Matrix33KeyFrame> fMatrixKeys;

public:
    plMatrix33Controller();
    virtual ~plMatrix33Controller();

    DECLARE_CREATABLE(plMatrix33Controller)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plMatrix44Controller : public plLeafController {
protected:
    hsTArray<Matrix44KeyFrame> fMatrixKeys;

public:
    plMatrix44Controller();
    virtual ~plMatrix44Controller();

    DECLARE_CREATABLE(plMatrix44Controller)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plPoint3Controller : public plLeafController {
protected:
    hsTArray<Point3KeyFrame> fPointKeys;

public:
    plPoint3Controller();
    virtual ~plPoint3Controller();

    DECLARE_CREATABLE(plPoint3Controller)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plQuatController : public plLeafController {
protected:
    hsTArray<QuatKeyFrame> fQuatKeys;

public:
    plQuatController();
    virtual ~plQuatController();

    DECLARE_CREATABLE(plQuatController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plScalarController : public plLeafController {
protected:
    hsTArray<ScalarKeyFrame> fScalarKeys;

public:
    plScalarController();
    virtual ~plScalarController();

    DECLARE_CREATABLE(plScalarController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plScaleValueController : public plLeafController {
protected:
    hsTArray<ScaleKeyFrame> fScaleKeys;

public:
    plScaleValueController();
    virtual ~plScaleValueController();

    DECLARE_CREATABLE(plScaleValueController)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
