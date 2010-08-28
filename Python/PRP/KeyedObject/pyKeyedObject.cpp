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
#include <PRP/KeyedObject/hsKeyedObject.h>
#include "pyKeyedObject.h"
#include "pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pyKeyedObject___init__(pyKeyedObject* self, PyObject* args, PyObject* kwds) {
    const char* name = "";
    if (!PyArg_ParseTuple(args, "|s", &name)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects an optional string");
        return -1;
    }

    self->fThis->init(name);
    self->fClsType = self->fThis->ClassIndex();
    return 0;
}

static PyObject* pyKeyedObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "hsKeyedObject is abstract");
    return NULL;
}

static PyObject* pyKeyedObject_getKey(pyKeyedObject* self, void*) {
    if (self->fThis->getKey().Exists()) {
        return pyKey_FromKey(self->fThis->getKey());
    } else {
        Py_INCREF(Py_None);
        return Py_None;
    }
}

static int pyKeyedObject_setKey(pyKeyedObject* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "key is read-only");
    return -1;
}

static PyObject* pyKeyedObject_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyKeyedObject_FromKeyedObject(hsKeyedObject::Convert(IConvert(cre)));
}

static PyMethodDef pyKeyedObject_Methods[] = {
    { "Convert", (PyCFunction)pyKeyedObject_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to an hsKeyedObject" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyKeyedObject_GetSet[] = {
    { "key", (getter)pyKeyedObject_getKey, (setter)pyKeyedObject_setKey,
      "The plKey for this object", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyKeyedObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsKeyedObject",           /* tp_name */
    sizeof(pyKeyedObject),              /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
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
    "hsKeyedObject wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyKeyedObject_Methods,              /* tp_methods */
    NULL,                               /* tp_members */
    pyKeyedObject_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyKeyedObject___init__,   /* tp_init */
    NULL,                               /* tp_alloc */
    pyKeyedObject_new,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyKeyedObject_Type() {
    pyKeyedObject_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyKeyedObject_Type) < 0)
        return NULL;

    Py_INCREF(&pyKeyedObject_Type);
    return (PyObject*)&pyKeyedObject_Type;
}

int pyKeyedObject_Check(PyObject* obj) {
    if (obj->ob_type == &pyKeyedObject_Type
        || PyType_IsSubtype(obj->ob_type, &pyKeyedObject_Type))
        return 1;
    return 0;
}

PyObject* pyKeyedObject_FromKeyedObject(class hsKeyedObject* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyKeyedObject* ko = PyObject_New(pyKeyedObject, &pyKeyedObject_Type);
    ko->fThis = obj;
    ko->fPyOwned = false;
    ko->fClsType = obj->ClassIndex();
    return (PyObject*)ko;
}

}
