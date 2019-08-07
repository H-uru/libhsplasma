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

#include "pyControlEventConditionalObject.h"

#include <PRP/ConditionalObject/plControlEventConditionalObject.h>
#include "pyConditionalObject.h"

PY_PLASMA_NEW(ControlEventConditionalObject, plControlEventConditionalObject)

PY_PROPERTY(ControlEventCode, ControlEventConditionalObject, controlEvent,
            getControlEvent, setControlEvent)

static PyGetSetDef pyControlEventConditionalObject_GetSet[] = {
    pyControlEventConditionalObject_controlEvent_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ControlEventConditionalObject, plControlEventConditionalObject,
               "plControlEventConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(ControlEventConditionalObject)
{
    pyControlEventConditionalObject_Type.tp_new = pyControlEventConditionalObject_new;
    pyControlEventConditionalObject_Type.tp_getset = pyControlEventConditionalObject_GetSet;
    pyControlEventConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_CheckAndReady(&pyControlEventConditionalObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyControlEventConditionalObject_Type);
    return (PyObject*)&pyControlEventConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(ControlEventConditionalObject, plControlEventConditionalObject)
