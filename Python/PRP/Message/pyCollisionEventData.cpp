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
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyCollisionEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCollisionEventData* self = (pyCollisionEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proCollisionEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCollisionEventData_getEnter(pyCollisionEventData* self, void*) {
    return PyBool_FromLong(self->fThis->isEnter());
}

static PyObject* pyCollisionEventData_getHitter(pyCollisionEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getHitter());
}

static PyObject* pyCollisionEventData_getHittee(pyCollisionEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getHittee());
}

static int pyCollisionEventData_setEnter(pyCollisionEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "enter should be a bool");
        return -1;
    }
    self->fThis->setEnter(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyCollisionEventData_setHitter(pyCollisionEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setHitter(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setHitter(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "hitter should be a plKey");
        return -1;
    }
}

static int pyCollisionEventData_setHittee(pyCollisionEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setHittee(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setHittee(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "hittee should be a plKey");
        return -1;
    }
}

static PyMethodDef pyCollisionEventData_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCollisionEventData_GetSet[] = {
    { "enter", (getter)pyCollisionEventData_getEnter, (setter)pyCollisionEventData_setEnter, NULL, NULL },
    { "hitter", (getter)pyCollisionEventData_getHitter, (setter)pyCollisionEventData_setHitter, NULL, NULL },
    { "hittee", (getter)pyCollisionEventData_getHittee, (setter)pyCollisionEventData_setHittee, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCollisionEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proCollisionEventData",   /* tp_name */
    sizeof(pyCollisionEventData),       /* tp_basicsize */
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
    "proCollisionEventData wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCollisionEventData_Methods,       /* tp_methods */
    NULL,                               /* tp_members */
    pyCollisionEventData_GetSet,        /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCollisionEventData_new,           /* tp_new */
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

PyObject* Init_pyCollisionEventData_Type() {
    pyCollisionEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyCollisionEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyCollisionEventData_Type);
    return (PyObject*)&pyCollisionEventData_Type;
}

int pyCollisionEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyCollisionEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyCollisionEventData_Type))
        return 1;
    return 0;
}

PyObject* pyCollisionEventData_FromCollisionEventData(proCollisionEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCollisionEventData* pyobj = PyObject_New(pyCollisionEventData, &pyCollisionEventData_Type);
    delete pyobj->fThis;
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
