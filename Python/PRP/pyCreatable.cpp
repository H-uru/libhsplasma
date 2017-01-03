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
#include "Stream/pyStream.h"
#include "ResManager/pyResManager.h"

extern "C" {

PY_PLASMA_DEALLOC(Creatable)
PY_PLASMA_EMPTY_INIT(Creatable)
PY_PLASMA_NEW_MSG(Creatable, "plCreatable is abstract")

PY_METHOD_NOARGS(Creatable, ClassIndex,
    "Returns the Creatable Class Index of this Creatable")
{
    return pyPlasma_convert(self->fThis->ClassIndex());
}

PY_METHOD_VA(Creatable, ClassIndexVer,
    "Params: version\n"
    "Returns the Creatable Class Index of this Creatable for\n"
    "the specified Plasma version")
{
    int ver;
    if (!PyArg_ParseTuple(args, "i", &ver)) {
        PyErr_SetString(PyExc_TypeError, "ClassIndexVer expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->ClassIndex((PlasmaVer)ver));
}

PY_METHOD_NOARGS(Creatable, ClassName,
    "Returns the Creatable Name of this Creatable")
{
    return pyPlasma_convert(self->fThis->ClassName());
}

PY_METHOD_VA(Creatable, ClassInstance,
    "Params: classId\n"
    "Returns true if this Creatable is an instance or subclass\n"
    "of `classId`")
{
    int classId;
    if (!PyArg_ParseTuple(args, "i", &classId)) {
        PyErr_SetString(PyExc_TypeError, "ClassInstance expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->ClassInstance(classId));
}

PY_METHOD_NOARGS(Creatable, isStub,
    "Returns true if this Creatable is a stub (plCreatableStub)")
{
    return pyPlasma_convert(self->fThis->isStub());
}

PY_METHOD_VA(Creatable, read,
    "Params: stream, resManager\n"
    "Read this Creatable from `stream`")
{
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plResManager");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plResManager");
        return NULL;
    }
    self->fThis->read(stream->fThis, mgr->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Creatable, write,
    "Params: stream, resManager\n"
    "Write this Creatable to `stream`")
{
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return NULL;
    }
    self->fThis->write(stream->fThis, mgr->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyCreatable_Methods[] = {
    pyCreatable_ClassIndex_method,
    pyCreatable_ClassIndexVer_method,
    pyCreatable_ClassName_method,
    pyCreatable_ClassInstance_method,
    pyCreatable_isStub_method,
    pyCreatable_read_method,
    pyCreatable_write_method,
    PY_METHOD_TERMINATOR
};

PyTypeObject pyCreatable_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCreatable",           /* tp_name */
    sizeof(pyCreatable),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyCreatable_dealloc,                /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plCreatable wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCreatable_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyCreatable___init__,               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCreatable_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyCreatable_Type() {
    if (PyType_Ready(&pyCreatable_Type) < 0)
        return NULL;

    Py_INCREF(&pyCreatable_Type);
    return (PyObject*)&pyCreatable_Type;
}

PY_PLASMA_IFC_METHODS(Creatable, plCreatable)

}
