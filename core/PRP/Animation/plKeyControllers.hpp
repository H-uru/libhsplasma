#ifndef _PLKEYCONTROLLERS_H
#define _PLKEYCONTROLLERS_H

#include "plLeafController.h"

// These are greatly simplified from Uru's versions, mostly for the sake of
// compatibility with Live/EOA's formats

DllClass plEaseController : public plLeafController {
    CREATABLE(plEaseController, kEaseController, plLeafController)
};


DllClass plMatrix33Controller : public plLeafController {
    CREATABLE(plMatrix33Controller, kMatrix33Controller, plLeafController)
};


DllClass plMatrix44Controller : public plLeafController {
    CREATABLE(plMatrix44Controller, kMatrix44Controller, plLeafController)
};


DllClass plPoint3Controller : public plLeafController {
    CREATABLE(plPoint3Controller, kPoint3Controller, plLeafController)
};


DllClass plQuatController : public plLeafController {
    CREATABLE(plQuatController, kQuatController, plLeafController)
};


DllClass plScalarController : public plLeafController {
    CREATABLE(plScalarController, kScalarController, plLeafController)
};


DllClass plScaleValueController : public plLeafController {
    CREATABLE(plScaleValueController, kScaleValueController, plLeafController)
};

#endif
