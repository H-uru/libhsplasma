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

PY_PLASMA_NEW(ORConditionalObject, plORConditionalObject)

static PyObject* pyORConditionalObject_addChild(pyORConditionalObject* self, PyObject* args) {
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addChild expects a plKey");
        return NULL;
    }
    self->fThis->addChild(*((pyKey*)key)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyORConditionalObject_clearChildren(pyORConditionalObject* self) {
    self->fThis->clearChildren();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyORConditionalObject_delChild(pyORConditionalObject* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delChild expects an int");
        return NULL;
    }
    self->fThis->delChild((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyORConditionalObject_Methods[] = {
    { "addChild", (PyCFunction)pyORConditionalObject_addChild, METH_VARARGS,
      "Params: key\n"
      "Adds a child condition key" },
    { "clearChildren", (PyCFunction)pyORConditionalObject_clearChildren, METH_NOARGS,
      "Removes all children condition keys" },
    { "delChild", (PyCFunction)pyORConditionalObject_delChild, METH_VARARGS,
      "Params: idx\n"
      "Removes a child condition key" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyORConditionalObject_getORs(pyORConditionalObject* self, void*) {
    PyObject* children = PyTuple_New(self->fThis->getChildren().size());
    for (size_t i = 0; i < self->fThis->getChildren().size(); ++i)
        PyTuple_SET_ITEM(children, i, pyKey_FromKey(self->fThis->getChildren()[i]));
    return children;
}

static int pyORConditionalObject_setORs(pyORConditionalObject* self, PyObject*, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add children, use addChild()");
    return -1;
}

static PyGetSetDef pyORConditionalObject_GetSet[] = {
    { _pycs("children"), (getter)pyORConditionalObject_getORs,
       (setter)pyORConditionalObject_setORs, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyORConditionalObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plORConditionalObject", /* tp_name */
    sizeof(pyORConditionalObject),      /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,  /* tp_flags */
    "plORConditionalObject wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyORConditionalObject_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyORConditionalObject_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyORConditionalObject_new,          /* tp_new */
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

PyObject* Init_pyORConditionalObject_Type() {
    pyORConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_Ready(&pyORConditionalObject_Type) < 0)
        return NULL;

    Py_INCREF(&pyORConditionalObject_Type);
    return (PyObject*)&pyORConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(ORConditionalObject, plORConditionalObject)

};
