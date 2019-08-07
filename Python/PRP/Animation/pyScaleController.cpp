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

#include "pyScaleController.h"

#include <PRP/Animation/plScaleController.h>
#include "pyController.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(ScaleController, "plScaleController is abstract")

PY_PROPERTY_RO(ScaleController, type, getType)

static PyGetSetDef pyScaleController_GetSet[] = {
    pyScaleController_type_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ScaleController, plScaleController, "plScaleController wrapper")

PY_PLASMA_TYPE_INIT(ScaleController)
{
    pyScaleController_Type.tp_new = pyScaleController_new;
    pyScaleController_Type.tp_getset = pyScaleController_GetSet;
    pyScaleController_Type.tp_base = &pyController_Type;
    if (PyType_CheckAndReady(&pyScaleController_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ScaleController, "kSimple", plScaleController::kSimple);

    Py_INCREF(&pyScaleController_Type);
    return (PyObject*)&pyScaleController_Type;
}

PY_PLASMA_IFC_METHODS(ScaleController, plScaleController)
