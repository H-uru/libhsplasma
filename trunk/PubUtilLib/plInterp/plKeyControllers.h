#ifndef _PLKEYCONTROLLERS_H
#define _PLKEYCONTROLLERS_H

#include "plLeafController.h"

DllClass plEaseController : public plLeafController {
};

DllClass plMatrix33Controller : public plLeafController {
};

DllClass plMatrix44Controller : public plLeafController {
};

DllClass plPoint3Controller : public plLeafController {
};

DllClass plQuatController : public plLeafController {
};

DllClass plScalarController : public plLeafController {
};

DllClass plScaleValueController : public plLeafController {
};

#endif
