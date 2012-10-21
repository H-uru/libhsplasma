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
#include "Math/pyGeometry3.h"

extern "C" {

static PyObject* pyPickedEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyPickedEventData* self = (pyPickedEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proPickedEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyPickedEventData_getPicker(pyPickedEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getPicker());
}

static PyObject* pyPickedEventData_getPicked(pyPickedEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getPicked());
}

static PyObject* pyPickedEventData_getEnabled(pyPickedEventData* self, void*) {
    return PyBool_FromLong(self->fThis->isEnabled());
}

static PyObject* pyPickedEventData_getHitPoint(pyPickedEventData* self, void*) {
    return pyVector3_FromVector3(self->fThis->getHitPoint());
}

static int pyPickedEventData_setPicker(pyPickedEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setPicker(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setPicker(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "picker should be a plKey");
        return -1;
    }
}

static int pyPickedEventData_setPicked(pyPickedEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setPicked(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setPicked(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "picked should be a plKey");
        return -1;
    }
}

static int pyPickedEventData_setEnabled(pyPickedEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "enabled should be a bool");
        return -1;
    }
    self->fThis->setEnabled(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyPickedEventData_setHitPoint(pyPickedEventData* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "hitPoint should be an hsVector3");
        return -1;
    }
    self->fThis->setHitPoint(*((pyVector3*)value)->fThis);
    return 0;
}

static PyMethodDef pyPickedEventData_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyPickedEventData_GetSet[] = {
    { _pycs("picker"), (getter)pyPickedEventData_getPicker,
        (setter)pyPickedEventData_setPicker, NULL, NULL },
    { _pycs("picked"), (getter)pyPickedEventData_getPicked,
        (setter)pyPickedEventData_setPicked, NULL, NULL },
    { _pycs("enabled"), (getter)pyPickedEventData_getEnabled,
        (setter)pyPickedEventData_setEnabled, NULL, NULL },
    { _pycs("hitPoint"), (getter)pyPickedEventData_getHitPoint,
        (setter)pyPickedEventData_setHitPoint, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyPickedEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proPickedEventData",      /* tp_name */
    sizeof(pyPickedEventData),          /* tp_basicsize */
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
    "proPickedEventData wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPickedEventData_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pyPickedEventData_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyPickedEventData_new,              /* tp_new */
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

PyObject* Init_pyPickedEventData_Type() {
    pyPickedEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyPickedEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyPickedEventData_Type);
    return (PyObject*)&pyPickedEventData_Type;
}

int pyPickedEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyPickedEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyPickedEventData_Type))
        return 1;
    return 0;
}

PyObject* pyPickedEventData_FromPickedEventData(proPickedEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyPickedEventData* pyobj = PyObject_New(pyPickedEventData, &pyPickedEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
