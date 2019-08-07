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

#include "pyModifier.h"

#include <PRP/Modifier/plModifier.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(SingleModifier, "plSingleModifier is abstract")

PY_METHOD_VA(SingleModifier, getFlag,
    "Params: flag\n"
    "Returns whether the specified modifier flag is set")
{
    int flag;
    if (!PyArg_ParseTuple(args, "i", &flag)) {
        PyErr_SetString(PyExc_TypeError, "getFlag expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getFlag(flag));
}

PY_METHOD_VA(SingleModifier, setFlag,
    "Params: flag, value\n"
    "Sets the specified modifier flag")
{
    int flag, value;
    if (!PyArg_ParseTuple(args, "ii", &flag, &value)) {
        PyErr_SetString(PyExc_TypeError, "setFlag expects int, bool");
        return nullptr;
    }
    self->fThis->setFlag(flag, value != 0);
    Py_RETURN_NONE;
}

static PyMethodDef pySingleModifier_Methods[] = {
    pySingleModifier_getFlag_method,
    pySingleModifier_setFlag_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(SingleModifier, plSingleModifier, "plSingleModifier wrapper")

PY_PLASMA_TYPE_INIT(SingleModifier)
{
    pySingleModifier_Type.tp_new = pySingleModifier_new;
    pySingleModifier_Type.tp_methods = pySingleModifier_Methods;
    pySingleModifier_Type.tp_base = &pyModifier_Type;
    if (PyType_CheckAndReady(&pySingleModifier_Type) < 0)
        return nullptr;

    Py_INCREF(&pySingleModifier_Type);
    return (PyObject*)&pySingleModifier_Type;
}

PY_PLASMA_IFC_METHODS(SingleModifier, plSingleModifier)
