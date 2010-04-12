/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

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
