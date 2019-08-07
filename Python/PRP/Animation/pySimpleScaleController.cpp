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
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_EMPTY_INIT(SimpleScaleController)
PY_PLASMA_NEW(SimpleScaleController, plSimpleScaleController)

PY_PROPERTY_CREATABLE(plScaleValueController, ScaleValueController,
                      SimpleScaleController, value, getValue, setValue)

static PyGetSetDef pySimpleScaleController_GetSet[] = {
    pySimpleScaleController_value_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SimpleScaleController, plSimpleScaleController,
               "plSimpleScaleController wrapper")

PY_PLASMA_TYPE_INIT(SimpleScaleController)
{
    pySimpleScaleController_Type.tp_init = pySimpleScaleController___init__;
    pySimpleScaleController_Type.tp_new = pySimpleScaleController_new;
    pySimpleScaleController_Type.tp_getset = pySimpleScaleController_GetSet;
    pySimpleScaleController_Type.tp_base = &pyScaleController_Type;
    if (PyType_CheckAndReady(&pySimpleScaleController_Type) < 0)
        return nullptr;

    Py_INCREF(&pySimpleScaleController_Type);
    return (PyObject*)&pySimpleScaleController_Type;
}

PY_PLASMA_IFC_METHODS(SimpleScaleController, plSimpleScaleController)
