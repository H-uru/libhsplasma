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
#include <PRP/Modifier/plLogicModifier.h>
#include "pyLogicModifier.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyLogicModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLogicModifier* self = (pyLogicModifier*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLogicModifier();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyLogicModifier_clearConditions(pyLogicModifier* self) {
    self->fThis->clearConditions();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLogicModifier_addCondition(pyLogicModifier* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addCondition expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addCondition expects a plKey");
        return NULL;
    }
    self->fThis->addCondition(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLogicModifier_delCondition(pyLogicModifier* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCondition expects an int");
        return NULL;
    }
    self->fThis->delCondition(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLogicModifier_getConditions(pyLogicModifier* self, void*) {
    PyObject* list = PyList_New(self->fThis->getConditions().getSize());
    for (size_t i=0; i<self->fThis->getConditions().getSize(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getConditions()[i]));
    return list;
}

static PyObject* pyLogicModifier_getCursor(pyLogicModifier* self, void*) {
    return PyInt_FromLong(self->fThis->getCursor());
}

static PyObject* pyLogicModifier_getParent(pyLogicModifier* self, void*) {
    return pyKey_FromKey(self->fThis->getParent());
}

static int pyLogicModifier_setConditions(pyLogicModifier* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add conditions, use addCondition");
    return -1;
}

static int pyLogicModifier_setCursor(pyLogicModifier* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "cursor should be an int");
        return -1;
    }
    self->fThis->setCursor(PyInt_AsLong(value));
    return 0;
}

static int pyLogicModifier_setParent(pyLogicModifier* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setParent(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setParent(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "parent should be a plKey");
        return -1;
    }
}

static PyMethodDef pyLogicModifier_Methods[] = {
    { "clearConditions", (PyCFunction)pyLogicModifier_clearConditions, METH_NOARGS,
      "Remove all condition keys" },
    { "addCondition", (PyCFunction)pyLogicModifier_addCondition, METH_VARARGS,
      "Params: key\n"
      "Add a condition key" },
    { "delCondition", (PyCFunction)pyLogicModifier_delCondition, METH_NOARGS,
      "Params: idx\n"
      "Remove a condition key" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLogicModifier_GetSet[] = {
    { "conditions", (getter)pyLogicModifier_getConditions, (setter)pyLogicModifier_setConditions, NULL, NULL },
    { "cursor", (getter)pyLogicModifier_getCursor, (setter)pyLogicModifier_setCursor, NULL, NULL },
    { "parent", (getter)pyLogicModifier_getParent, (setter)pyLogicModifier_setParent, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLogicModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plLogicModifier",         /* tp_name */
    sizeof(pyLogicModifier),            /* tp_basicsize */
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
    "plLogicModifier wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLogicModifier_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyLogicModifier_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLogicModifier_new,                /* tp_new */
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

PyObject* Init_pyLogicModifier_Type() {
    pyLogicModifier_Type.tp_base = &pyLogicModBase_Type;
    if (PyType_Ready(&pyLogicModifier_Type) < 0)
        return NULL;

    Py_INCREF(&pyLogicModifier_Type);
    return (PyObject*)&pyLogicModifier_Type;
}

int pyLogicModifier_Check(PyObject* obj) {
    if (obj->ob_type == &pyLogicModifier_Type
        || PyType_IsSubtype(obj->ob_type, &pyLogicModifier_Type))
        return 1;
    return 0;
}

PyObject* pyLogicModifier_FromLogicModifier(plLogicModifier* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLogicModifier* pyobj = PyObject_New(pyLogicModifier, &pyLogicModifier_Type);
    delete pyobj->fThis;
    pyobj->fThis = obj;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
