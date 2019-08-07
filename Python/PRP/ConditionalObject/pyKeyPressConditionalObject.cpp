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

#include "pyKeyPressConditionalObject.h"

#include <PRP/ConditionalObject/plKeyPressConditionalObject.h>
#include "pyConditionalObject.h"

PY_PLASMA_NEW(KeyPressConditionalObject, plKeyPressConditionalObject)

PY_PROPERTY(plKeyDef, KeyPressConditionalObject, keyEvent, getKeyEvent, setKeyEvent)

static PyGetSetDef pyKeyPressConditionalObject_GetSet[] = {
    pyKeyPressConditionalObject_keyEvent_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(KeyPressConditionalObject, plKeyPressConditionalObject,
               "plKeyPressConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(KeyPressConditionalObject)
{
    pyKeyPressConditionalObject_Type.tp_new = pyKeyPressConditionalObject_new;
    pyKeyPressConditionalObject_Type.tp_getset = pyKeyPressConditionalObject_GetSet;
    pyKeyPressConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_CheckAndReady(&pyKeyPressConditionalObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyKeyPressConditionalObject_Type);
    return (PyObject*)&pyKeyPressConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(KeyPressConditionalObject, plKeyPressConditionalObject)
