#ifndef _PLKEYCONTROLLERS_H
#define _PLKEYCONTROLLERS_H

#include "plLeafController.h"

// These are greatly simplified from Uru's versions, mostly for the sake of
// compatibility with Live/EOA's formats

DllClass plEaseController : public plLeafController {
public:
    plEaseController();
    virtual ~plEaseController();

    DECLARE_CREATABLE(plEaseController)
};

DllClass plMatrix33Controller : public plLeafController {
public:
    plMatrix33Controller();
    virtual ~plMatrix33Controller();

    DECLARE_CREATABLE(plMatrix33Controller)
};

DllClass plMatrix44Controller : public plLeafController {
public:
    plMatrix44Controller();
    virtual ~plMatrix44Controller();

    DECLARE_CREATABLE(plMatrix44Controller)
};

DllClass plPoint3Controller : public plLeafController {
public:
    plPoint3Controller();
    virtual ~plPoint3Controller();

    DECLARE_CREATABLE(plPoint3Controller)
};

DllClass plQuatController : public plLeafController {
public:
    plQuatController();
    virtual ~plQuatController();

    DECLARE_CREATABLE(plQuatController)
};

DllClass plScalarController : public plLeafController {
public:
    plScalarController();
    virtual ~plScalarController();

    DECLARE_CREATABLE(plScalarController)
};

DllClass plScaleValueController : public plLeafController {
public:
    plScaleValueController();
    virtual ~plScaleValueController();

    DECLARE_CREATABLE(plScaleValueController)
};

#endif
