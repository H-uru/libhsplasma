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

#include "pySharedMesh.h"

#include <PRP/Geometry/plSharedMesh.h>
#include "PRP/Geometry/pyGeometrySpan.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(SharedMesh, plSharedMesh)

PY_METHOD_VA(SharedMesh, addSpan,
    "Params: span\n"
    "Add a GeometrySpan to this SharedMesh")
{
    pyGeometrySpan* span;
    if (!PyArg_ParseTuple(args, "O", &span)) {
        PyErr_SetString(PyExc_TypeError, "addSpan expects a plGeometrySpan");
        return nullptr;
    }
    if (!pyGeometrySpan_Check((PyObject*)span)) {
        PyErr_SetString(PyExc_TypeError, "addSpan expects a plGeometrySpan");
        return nullptr;
    }
    span->fPyOwned = false;
    self->fThis->addSpan(span->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SharedMesh, delSpan,
    "Params: idx\n"
    "Delete a GeometrySpan from this SharedMesh")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delSpan expects an int");
        return nullptr;
    }
    if ((size_t)idx < self->fThis->getSpans().size()) {
        self->fThis->delSpan(idx);
        Py_RETURN_NONE;
    } else {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
}

PY_METHOD_NOARGS(SharedMesh, clearSpans,
    "Remove all GeometrySpans from this SharedMesh object")
{
    self->fThis->clearSpans();
    Py_RETURN_NONE;
}

static PyMethodDef pySharedMesh_Methods[] = {
    pySharedMesh_addSpan_method,
    pySharedMesh_delSpan_method,
    pySharedMesh_clearSpans_method,
    PY_METHOD_TERMINATOR
};


PY_GETSET_GETTER_DECL(SharedMesh, spans)
{
    PyObject* list = PyTuple_New(self->fThis->getSpans().size());
    for (size_t i = 0; i < self->fThis->getSpans().size(); ++i)
        PyTuple_SET_ITEM(list, i, pyGeometrySpan_FromGeometrySpan(self->fThis->getSpans()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(SharedMesh, spans, "To add spans, use addSpan()")
PY_PROPERTY_GETSET_DECL(SharedMesh, spans)


PY_PROPERTY(uint8_t, SharedMesh, flags, getFlags, setFlags)
PY_PROPERTY(plKey, SharedMesh, morphSet, getMorphSet, setMorphSet)

PyGetSetDef pySharedMesh_GetSet[] = {
    pySharedMesh_flags_getset,
    pySharedMesh_morphSet_getset,
    PY_GETSET_TERMINATOR
};


PY_PLASMA_TYPE(SharedMesh, plSharedMesh, "plSharedMesh wrapper")

PY_PLASMA_TYPE_INIT(SharedMesh) {
    pySharedMesh_Type.tp_new = pySharedMesh_new;
    pySharedMesh_Type.tp_base = &pyKeyedObject_Type;
    pySharedMesh_Type.tp_methods = pySharedMesh_Methods;
    pySharedMesh_Type.tp_getset = pySharedMesh_GetSet;
    if (PyType_CheckAndReady(&pySharedMesh_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(SharedMesh, "kDontSaveMorphState", plSharedMesh::kDontSaveMorphState);
    PY_TYPE_ADD_CONST(SharedMesh, "kLayer0GlobalToMod", plSharedMesh::kLayer0GlobalToMod);

    Py_INCREF(&pySharedMesh_Type);
    return (PyObject*)&pySharedMesh_Type;
}

PY_PLASMA_IFC_METHODS(SharedMesh, plSharedMesh)