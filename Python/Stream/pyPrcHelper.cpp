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

#include "pyPrcHelper.h"
#include <Stream/pfPrcHelper.h>
#include "pyStream.h"

PY_PLASMA_DEALLOC(PrcHelper)

PY_PLASMA_INIT_DECL(PrcHelper)
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream) || !pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects an hsStream");
        return -1;
    }

    *(self->fThis) = pfPrcHelper(stream->fThis);
    return 0;
}

PY_PLASMA_NEW_DECL(PrcHelper)
{
    pyPrcHelper* self = (pyPrcHelper*)type->tp_alloc(type, 0);
    // This will get populated in __init__(stream)
    self->fThis = nullptr;
    return (PyObject*)self;
}

PY_PLASMA_TYPE(PrcHelper, pfPrcHelper, "pfPrcHelper wrapper")

PY_PLASMA_TYPE_INIT(PrcHelper)
{
    pyPrcHelper_Type.tp_dealloc = pyPrcHelper_dealloc;
    pyPrcHelper_Type.tp_init = pyPrcHelper___init__;
    pyPrcHelper_Type.tp_new = pyPrcHelper_new;
    if (PyType_CheckAndReady(&pyPrcHelper_Type) < 0)
        return nullptr;

    /* PrcExcludes */
    PY_TYPE_ADD_CONST(PrcHelper, "kNone", pfPrcHelper::kNone);
    PY_TYPE_ADD_CONST(PrcHelper, "kExcludeTextureData", pfPrcHelper::kExcludeTextureData);
    PY_TYPE_ADD_CONST(PrcHelper, "kExcludeVertexData", pfPrcHelper::kExcludeVertexData);

    Py_INCREF(&pyPrcHelper_Type);
    return (PyObject*)&pyPrcHelper_Type;
}

PY_PLASMA_IFC_METHODS(PrcHelper, pfPrcHelper)
