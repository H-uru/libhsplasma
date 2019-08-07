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

#include "pyCreatable.h"

#include <PRP/plCreatable.h>

PY_PLASMA_INIT_DECL(CreatableStub)
{
    int classId, length;
    if (!PyArg_ParseTuple(args, "ii", &classId, &length)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects int, int");
        return -1;
    }
    if (self->fPyOwned)
        delete self->fThis;
    self->fThis = new plCreatableStub(classId, (size_t)length);
    return 0;
}

PY_PLASMA_NEW_DECL(CreatableStub)
{
    pyCreatableStub* self = (pyCreatableStub*)type->tp_alloc(type, 0);
    // This will get populated in __init__(classID, size)
    self->fThis = nullptr;
    return (PyObject*)self;
}

PY_METHOD_NOARGS(CreatableStub, getData, "Returns the Creatable's raw data")
{
    return PyBytes_FromStringAndSize((const char*)self->fThis->getData(),
                                     self->fThis->getLength());
}

PY_METHOD_NOARGS(CreatableStub, getLength,
    "Returns the length of the Creatable's raw data")
{
    return pyPlasma_convert(self->fThis->getLength());
}

static PyMethodDef pyCreatableStub_Methods[] = {
    pyCreatableStub_getData_method,
    pyCreatableStub_getLength_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(CreatableStub, plCreatableStub, "plCreatableStub wrapper")

PY_PLASMA_TYPE_INIT(CreatableStub)
{
    pyCreatableStub_Type.tp_init = pyCreatableStub___init__;
    pyCreatableStub_Type.tp_new = pyCreatableStub_new;
    pyCreatableStub_Type.tp_methods = pyCreatableStub_Methods;
    pyCreatableStub_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyCreatableStub_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCreatableStub_Type);
    return (PyObject*)&pyCreatableStub_Type;
}

PY_PLASMA_IFC_METHODS(CreatableStub, const plCreatableStub)
