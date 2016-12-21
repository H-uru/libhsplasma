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

#include "pyBooleanConditionalObject.h"

#include <PRP/ConditionalObject/plBooleanConditionalObject.h>
#include "pyConditionalObject.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyANDConditionalObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyANDConditionalObject* self = (pyANDConditionalObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plANDConditionalObject();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyANDConditionalObject_addChild(pyANDConditionalObject* self, PyObject* args) {
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addChild expects a plKey");
        return NULL;
    }
    self->fThis->addChild(*((pyKey*)key)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyANDConditionalObject_clearChildren(pyANDConditionalObject* self) {
    self->fThis->clearChildren();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyANDConditionalObject_delChild(pyANDConditionalObject* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delChild expects an int");
        return NULL;
    }
    self->fThis->delChild((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyANDConditionalObject_Methods[] = {
    { "addChild", (PyCFunction)pyANDConditionalObject_addChild, METH_VARARGS,
      "Params: key\n"
      "Adds a child condition key" },
    { "clearChildren", (PyCFunction)pyANDConditionalObject_clearChildren, METH_NOARGS,
      "Removes all children condition keys" },
    { "delChild", (PyCFunction)pyANDConditionalObject_delChild, METH_VARARGS,
      "Params: idx\n"
      "Removes a child condition key" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyANDConditionalObject_getANDs(pyANDConditionalObject* self, void*) {
    PyObject* children = PyTuple_New(self->fThis->getChildren().size());
    for (size_t i = 0; i < self->fThis->getChildren().size(); ++i)
        PyTuple_SET_ITEM(children, i, pyKey_FromKey(self->fThis->getChildren()[i]));
    return children;
}

static int pyANDConditionalObject_setANDs(pyANDConditionalObject* self, PyObject*, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add children, use addChild()");
    return -1;
}

static PyGetSetDef pyANDConditionalObject_GetSet[] = {
    { _pycs("children"), (getter)pyANDConditionalObject_getANDs,
       (setter)pyANDConditionalObject_setANDs, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyANDConditionalObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plANDConditionalObject", /* tp_name */
    sizeof(pyANDConditionalObject),      /* tp_basicsize */
    0,                                   /* tp_itemsize */

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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,  /* tp_flags */
    "plANDConditionalObject wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyANDConditionalObject_Methods,     /* tp_methods */
    NULL,                               /* tp_members */
    pyANDConditionalObject_GetSet,      /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyANDConditionalObject_new,         /* tp_new */
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

PyObject* Init_pyANDConditionalObject_Type() {
    pyANDConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_Ready(&pyANDConditionalObject_Type) < 0)
        return NULL;

    Py_INCREF(&pyANDConditionalObject_Type);
    return (PyObject*)&pyANDConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(ANDConditionalObject, plANDConditionalObject)

};
