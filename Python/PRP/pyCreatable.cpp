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

#include <PyPlasma.h>
#include <PRP/plCreatable.h>
#include "pyCreatable.h"
#include "Stream/pyStream.h"
#include "ResManager/pyResManager.h"

extern "C" {

static void pyCreatable_dealloc(pyCreatable* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyCreatable___init__(pyCreatable* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCreatable_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plCreatable is abstract");
    return NULL;
}

static PyObject* pyCreatable_ClassIndex(pyCreatable* self) {
    return PyInt_FromLong(self->fThis->ClassIndex());
}

static PyObject* pyCreatable_ClassIndexVer(pyCreatable* self, PyObject* args) {
    int ver;
    if (!PyArg_ParseTuple(args, "i", &ver)) {
        PyErr_SetString(PyExc_TypeError, "ClassIndexVer expects an int");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->ClassIndex((PlasmaVer)ver));
}

static PyObject* pyCreatable_ClassName(pyCreatable* self) {
    return PyString_FromString(self->fThis->ClassName());
}

static PyObject* pyCreatable_ClassInstance(pyCreatable* self, PyObject* args) {
    int classId;
    if (!PyArg_ParseTuple(args, "i", &classId)) {
        PyErr_SetString(PyExc_TypeError, "ClassInstance expects an int");
        return NULL;
    }
    bool yes = self->fThis->ClassInstance(classId);
    return PyBool_FromLong(yes ? 1 : 0);
}

static PyObject* pyCreatable_isStub(pyCreatable* self) {
    bool yes = self->fThis->isStub();
    return PyBool_FromLong(yes ? 1 : 0);
}

static PyObject* pyCreatable_read(pyCreatable* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCreatable_write(pyCreatable* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyCreatable_Methods[] = {
    { "ClassIndex", (PyCFunction)pyCreatable_ClassIndex, METH_NOARGS,
      "Returns the Creatable Class Index of this Creatable" },
    { "ClassIndexVer", (PyCFunction)pyCreatable_ClassIndexVer, METH_VARARGS,
      "Params: version\n"
      "Returns the Creatable Class Index of this Creatable for\n"
      "the specified Plasma version" },
    { "ClassName", (PyCFunction)pyCreatable_ClassName, METH_NOARGS,
      "Returns the Creatable Name of this Creatable" },
    { "ClassInstance", (PyCFunction)pyCreatable_ClassInstance, METH_VARARGS,
      "Params: classId\n"
      "Returns true if this Creatable is an instance or subclass\n"
      "of `classId`" },
    { "isStub", (PyCFunction)pyCreatable_isStub, METH_NOARGS,
      "Returns true if this Creatable is a stub (plCreatableStub)" },
    { "read", (PyCFunction)pyCreatable_read, METH_VARARGS,
      "Params: stream, resManager\n"
      "Read this Creatable from `stream`" },
    { "write", (PyCFunction)pyCreatable_write, METH_VARARGS,
      "Params: stream, resManager\n"
      "Write this Creatable to `stream`" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyCreatable_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plCreatable",             /* tp_name */
    sizeof(pyCreatable),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyCreatable_dealloc,    /* tp_dealloc */
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

    (initproc)pyCreatable___init__,     /* tp_init */
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
};

PyObject* Init_pyCreatable_Type() {
    if (PyType_Ready(&pyCreatable_Type) < 0)
        return NULL;

    Py_INCREF(&pyCreatable_Type);
    return (PyObject*)&pyCreatable_Type;
}

int pyCreatable_Check(PyObject* obj) {
    if (obj->ob_type == &pyCreatable_Type
        || PyType_IsSubtype(obj->ob_type, &pyCreatable_Type))
        return 1;
    return 0;
}

PyObject* pyCreatable_FromCreatable(class plCreatable* pCre) {
    if (pCre == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCreatable* obj = PyObject_New(pyCreatable, &pyCreatable_Type);
    obj->fThis = pCre;
    obj->fPyOwned = false;
    return (PyObject*)obj;
}

}
