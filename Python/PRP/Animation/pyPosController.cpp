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
#include "pyController.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(PosController, "plPosController is abstract")

PY_PROPERTY_RO(PosController, type, getType)

static PyGetSetDef pyPosController_GetSet[] = {
    pyPosController_type_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(PosController, plPosController, "plPosController wrapper")

PY_PLASMA_TYPE_INIT(PosController)
{
    pyPosController_Type.tp_new = pyPosController_new;
    pyPosController_Type.tp_getset = pyPosController_GetSet;
    pyPosController_Type.tp_base = &pyController_Type;
    if (PyType_CheckAndReady(&pyPosController_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(PosController, "kSimple", plPosController::kSimple);
    PY_TYPE_ADD_CONST(PosController, "kCompound", plPosController::kCompound);

    Py_INCREF(&pyPosController_Type);
    return (PyObject*)&pyPosController_Type;
}

PY_PLASMA_IFC_METHODS(PosController, plPosController)
