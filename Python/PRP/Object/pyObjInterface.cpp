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
#include <PRP/Object/plObjInterface.h>
#include "pyObjInterface.h"
#include "pySynchedObject.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Util/pyBitVector.h"

extern "C" {

static PyObject* pyObjInterface_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plObjInterface is abstract");
    return NULL;
}

static PyObject* pyObjInterface_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyObjInterface_FromObjInterface(plObjInterface::Convert(IConvert(cre)));
}

static PyObject* pyObjInterface_getProp(pyObjInterface* self, PyObject* args) {
    int prop;
    if (!PyArg_ParseTuple(args, "i", &prop)) {
        PyErr_SetString(PyExc_TypeError, "getProperty expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getProperty(prop) ? 1 : 0);
}

static PyObject* pyObjInterface_setProp(pyObjInterface* self, PyObject* args) {
    int prop, value;
    if (!PyArg_ParseTuple(args, "ii", &prop, &value)) {
        PyErr_SetString(PyExc_TypeError, "setProperty expects int, bool");
        return NULL;
    }
    self->fThis->setProperty(prop, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyObjInterface_getOwner(pyObjInterface* self, void*) {
    return pyKey_FromKey(self->fThis->getOwner());
}

static int pyObjInterface_setOwner(pyObjInterface* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setOwner(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setOwner(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "owner should be a plKey");
        return -1;
    }
}

PyMethodDef pyObjInterface_Methods[] = {
    { "Convert", (PyCFunction)pyObjInterface_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plObjInterface" },
    { "getProperty", (PyCFunction)pyObjInterface_getProp, METH_VARARGS,
      "Params: flag\n"
      "Returns whether the specified property is set" },
    { "setProperty", (PyCFunction)pyObjInterface_setProp, METH_VARARGS,
      "Params: flag, value\n"
      "Sets the specified property" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pyObjInterface_GetSet[] = {
    { "owner", (getter)pyObjInterface_getOwner, (setter)pyObjInterface_setOwner,
      "The SceneObject that owns this interface", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyObjInterface_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plObjInterface",          /* tp_name */
    sizeof(pyObjInterface),             /* tp_basicsize */
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
    "plObjInterface wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyObjInterface_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyObjInterface_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyObjInterface_new,                 /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyObjInterface_Type() {
    pyObjInterface_Type.tp_base = &pySynchedObject_Type;
    if (PyType_Ready(&pyObjInterface_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyObjInterface_Type.tp_dict, "kDisable",
                         PyInt_FromLong(plObjInterface::kDisable));

    Py_INCREF(&pyObjInterface_Type);
    return (PyObject*)&pyObjInterface_Type;
}

int pyObjInterface_Check(PyObject* obj) {
    if (obj->ob_type == &pyObjInterface_Type
        || PyType_IsSubtype(obj->ob_type, &pyObjInterface_Type))
        return 1;
    return 0;
}

PyObject* pyObjInterface_FromObjInterface(class plObjInterface* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyObjInterface* intf = PyObject_New(pyObjInterface, &pyObjInterface_Type);
    intf->fThis = obj;
    intf->fPyOwned = false;
    return (PyObject*)intf;
}

}
