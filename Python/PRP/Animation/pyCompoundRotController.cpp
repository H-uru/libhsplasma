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

#include "pyRotController.h"

#include <PRP/Animation/plRotController.h>
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_EMPTY_INIT(CompoundRotController)
PY_PLASMA_NEW(CompoundRotController, plCompoundRotController)

PY_PROPERTY_CREATABLE(plScalarController, ScalarController,
                      CompoundRotController, X, getX, setX)
PY_PROPERTY_CREATABLE(plScalarController, ScalarController,
                      CompoundRotController, Y, getY, setY)
PY_PROPERTY_CREATABLE(plScalarController, ScalarController,
                      CompoundRotController, Z, getZ, setZ)

static PyGetSetDef pyCompoundRotController_GetSet[] = {
    pyCompoundRotController_X_getset,
    pyCompoundRotController_Y_getset,
    pyCompoundRotController_Z_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CompoundRotController, plCompoundRotController,
               "plCompoundRotController wrapper")

PY_PLASMA_TYPE_INIT(CompoundRotController)
{
    pyCompoundRotController_Type.tp_init = pyCompoundRotController___init__;
    pyCompoundRotController_Type.tp_new = pyCompoundRotController_new;
    pyCompoundRotController_Type.tp_getset = pyCompoundRotController_GetSet;
    pyCompoundRotController_Type.tp_base = &pyRotController_Type;
    if (PyType_CheckAndReady(&pyCompoundRotController_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCompoundRotController_Type);
    return (PyObject*)&pyCompoundRotController_Type;
}

PY_PLASMA_IFC_METHODS(CompoundRotController, plCompoundRotController)
