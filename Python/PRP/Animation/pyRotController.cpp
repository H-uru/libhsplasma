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
#include "pyController.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(RotController, "plRotController is abstract")

PY_PROPERTY_RO(RotController, type, getType)

static PyGetSetDef pyRotController_GetSet[] = {
    pyRotController_type_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(RotController, plRotController, "plRotController wrapper")

PY_PLASMA_TYPE_INIT(RotController)
{
    pyRotController_Type.tp_new = pyRotController_new;
    pyRotController_Type.tp_getset = pyRotController_GetSet;
    pyRotController_Type.tp_base = &pyController_Type;
    if (PyType_CheckAndReady(&pyRotController_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(RotController, "kSimple", plRotController::kSimple);
    PY_TYPE_ADD_CONST(RotController, "kCompound", plRotController::kCompound);

    Py_INCREF(&pyRotController_Type);
    return (PyObject*)&pyRotController_Type;
}

PY_PLASMA_IFC_METHODS(RotController, plRotController)
