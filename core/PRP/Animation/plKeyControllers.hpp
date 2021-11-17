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

class HSPLASMA_EXPORT plEaseController : public plLeafController
{
    CREATABLE(plEaseController, kEaseController, plLeafController)
};


class HSPLASMA_EXPORT plMatrix33Controller : public plLeafController
{
    CREATABLE(plMatrix33Controller, kMatrix33Controller, plLeafController)
};


class HSPLASMA_EXPORT plMatrix44Controller : public plLeafController
{
    CREATABLE(plMatrix44Controller, kMatrix44Controller, plLeafController)
};


class HSPLASMA_EXPORT plPoint3Controller : public plLeafController
{
    CREATABLE(plPoint3Controller, kPoint3Controller, plLeafController)
};


class HSPLASMA_EXPORT plQuatController : public plLeafController
{
    CREATABLE(plQuatController, kQuatController, plLeafController)
};


class HSPLASMA_EXPORT plScalarController : public plLeafController
{
    CREATABLE(plScalarController, kScalarController, plLeafController)
};


class HSPLASMA_EXPORT plScaleValueController : public plLeafController
{
    CREATABLE(plScaleValueController, kScaleValueController, plLeafController)
};

#endif
