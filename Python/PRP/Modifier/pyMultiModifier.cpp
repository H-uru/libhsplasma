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

PY_PLASMA_NEW_MSG(MultiModifier, "plMultiModifier is abstract")

PY_METHOD_VA(MultiModifier, getFlag,
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

PY_METHOD_VA(MultiModifier, setFlag,
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

static PyMethodDef pyMultiModifier_Methods[] = {
    pyMultiModifier_getFlag_method,
    pyMultiModifier_setFlag_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(MultiModifier, plMultiModifier, "plMultiModifier wrapper")

PY_PLASMA_TYPE_INIT(MultiModifier)
{
    pyMultiModifier_Type.tp_new = pyMultiModifier_new;
    pyMultiModifier_Type.tp_methods = pyMultiModifier_Methods;
    pyMultiModifier_Type.tp_base = &pyModifier_Type;
    if (PyType_CheckAndReady(&pyMultiModifier_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMultiModifier_Type);
    return (PyObject*)&pyMultiModifier_Type;
}

PY_PLASMA_IFC_METHODS(MultiModifier, plMultiModifier)
