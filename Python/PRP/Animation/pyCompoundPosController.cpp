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

#include "pyPosController.h"

#include <PRP/Animation/plPosController.h>
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_EMPTY_INIT(CompoundPosController)
PY_PLASMA_NEW(CompoundPosController, plCompoundPosController)

PY_PROPERTY_CREATABLE(plScalarController, ScalarController,
                      CompoundPosController, X, getX, setX)
PY_PROPERTY_CREATABLE(plScalarController, ScalarController,
                      CompoundPosController, Y, getY, setY)
PY_PROPERTY_CREATABLE(plScalarController, ScalarController,
                      CompoundPosController, Z, getZ, setZ)

static PyGetSetDef pyCompoundPosController_GetSet[] = {
    pyCompoundPosController_X_getset,
    pyCompoundPosController_Y_getset,
    pyCompoundPosController_Z_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CompoundPosController, plCompoundPosController,
               "plCompoundPosController wrapper")

PY_PLASMA_TYPE_INIT(CompoundPosController)
{
    pyCompoundPosController_Type.tp_init = pyCompoundPosController___init__;
    pyCompoundPosController_Type.tp_new = pyCompoundPosController_new;
    pyCompoundPosController_Type.tp_getset = pyCompoundPosController_GetSet;
    pyCompoundPosController_Type.tp_base = &pyPosController_Type;
    if (PyType_CheckAndReady(&pyCompoundPosController_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCompoundPosController_Type);
    return (PyObject*)&pyCompoundPosController_Type;
}

PY_PLASMA_IFC_METHODS(CompoundPosController, plCompoundPosController)
