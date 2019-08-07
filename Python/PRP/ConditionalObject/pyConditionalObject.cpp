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

#include "pyConditionalObject.h"

#include <PRP/ConditionalObject/plConditionalObject.h>
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(ConditionalObject, "plConditionalObject is abstract")

PY_PROPERTY(bool, ConditionalObject, satisfied, getSatisfied, setSatisfied)
PY_PROPERTY(bool, ConditionalObject, toggle, getToggle, setToggle)

static PyGetSetDef pyConditionalObject_GetSet[] = {
    pyConditionalObject_satisfied_getset,
    pyConditionalObject_toggle_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ConditionalObject, plConditionalObject, "plConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(ConditionalObject)
{
    pyConditionalObject_Type.tp_new = pyConditionalObject_new;
    pyConditionalObject_Type.tp_getset = pyConditionalObject_GetSet;
    pyConditionalObject_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyConditionalObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyConditionalObject_Type);
    return (PyObject*)&pyConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(ConditionalObject, plConditionalObject)
