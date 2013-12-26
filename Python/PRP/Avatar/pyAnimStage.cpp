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
#include <PRP/Avatar/plAnimStage.h>
#include "pyMultistageBehMod.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pyAnimStage___init__(pyAnimStage* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyAnimStage_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAnimStage* self = (pyAnimStage*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAnimStage();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAnimStage_getForwardType(pyAnimStage* self, void*) {
    return PyInt_FromLong(self->fThis->getForwardType());
}

static PyObject* pyAnimStage_getBackType(pyAnimStage* self, void*) {
    return PyInt_FromLong(self->fThis->getBackType());
}

static PyObject* pyAnimStage_getAdvanceType(pyAnimStage* self, void*) {
    return PyInt_FromLong(self->fThis->getAdvanceType());
}

static PyObject* pyAnimStage_getRegressType(pyAnimStage* self, void*) {
    return PyInt_FromLong(self->fThis->getRegressType());
}

static PyObject* pyAnimStage_getAnimName(pyAnimStage* self, void*) {
    return PlStr_To_PyStr(self->fThis->getAnimName());
}

static PyObject* pyAnimStage_getNotify(pyAnimStage* self, void*) {
    return PyInt_FromLong(self->fThis->getNotify());
}

static PyObject* pyAnimStage_getLoops(pyAnimStage* self, void*) {
    return PyInt_FromLong(self->fThis->getLoops());
}

static PyObject* pyAnimStage_getAdvanceTo(pyAnimStage* self, void*) {
    if (self->fThis->doAdvanceTo()) {
        return PyInt_FromLong(self->fThis->getAdvanceTo());
    } else {
        Py_INCREF(Py_None);
        return Py_None;
    }
}

static PyObject* pyAnimStage_getRegressTo(pyAnimStage* self, void*) {
    if (self->fThis->doRegressTo()) {
        return PyInt_FromLong(self->fThis->getRegressTo());
    } else {
        Py_INCREF(Py_None);
        return Py_None;
    }
}

static int pyAnimStage_setForwardType(pyAnimStage* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "forwardType should be an int");
        return -1;
    }
    self->fThis->setForwardType((plAnimStage::PlayType)PyInt_AsLong(value));
    return 0;
}

static int pyAnimStage_setBackType(pyAnimStage* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "backType should be an int");
        return -1;
    }
    self->fThis->setBackType((plAnimStage::PlayType)PyInt_AsLong(value));
    return 0;
}

static int pyAnimStage_setAdvanceType(pyAnimStage* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "advanceType should be an int");
        return -1;
    }
    self->fThis->setAdvanceType((plAnimStage::AdvanceType)PyInt_AsLong(value));
    return 0;
}

static int pyAnimStage_setRegressType(pyAnimStage* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "regressType should be an int");
        return -1;
    }
    self->fThis->setRegressType((plAnimStage::AdvanceType)PyInt_AsLong(value));
    return 0;
}

static int pyAnimStage_setAnimName(pyAnimStage* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "animName should be a string");
        return -1;
    }
    self->fThis->setAnimName(PyStr_To_PlStr(value));
    return 0;
}

static int pyAnimStage_setNotify(pyAnimStage* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "notify should be an int");
        return -1;
    }
    self->fThis->setNotify(PyInt_AsLong(value));
    return 0;
}

static int pyAnimStage_setLoops(pyAnimStage* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "loops should be an int");
        return -1;
    }
    self->fThis->setLoops(PyInt_AsLong(value));
    return 0;
}

static int pyAnimStage_setAdvanceTo(pyAnimStage* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setAdvanceTo(false);
        return 0;
    } else if (PyInt_Check(value)) {
        self->fThis->setAdvanceTo(true, PyInt_AsLong(value));
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "advanceTo should be an int or None");
        return -1;
    }
}

static int pyAnimStage_setRegressTo(pyAnimStage* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setRegressTo(false);
        return 0;
    } else if (PyInt_Check(value)) {
        self->fThis->setRegressTo(true, PyInt_AsLong(value));
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "regressTo should be an int or None");
        return -1;
    }
}

static PyMethodDef pyAnimStage_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyAnimStage_GetSet[] = {
    { _pycs("forwardType"), (getter)pyAnimStage_getForwardType, (setter)pyAnimStage_setForwardType, NULL, NULL },
    { _pycs("backType"), (getter)pyAnimStage_getBackType, (setter)pyAnimStage_setBackType, NULL, NULL },
    { _pycs("advanceType"), (getter)pyAnimStage_getAdvanceType, (setter)pyAnimStage_setAdvanceType, NULL, NULL },
    { _pycs("regressType"), (getter)pyAnimStage_getRegressType, (setter)pyAnimStage_setRegressType, NULL, NULL },
    { _pycs("animName"), (getter)pyAnimStage_getAnimName, (setter)pyAnimStage_setAnimName, NULL, NULL },
    { _pycs("notify"), (getter)pyAnimStage_getNotify, (setter)pyAnimStage_setNotify, NULL, NULL },
    { _pycs("loops"), (getter)pyAnimStage_getLoops, (setter)pyAnimStage_setLoops, NULL, NULL },
    { _pycs("advanceTo"), (getter)pyAnimStage_getAdvanceTo, (setter)pyAnimStage_setAdvanceTo, NULL, NULL },
    { _pycs("regressTo"), (getter)pyAnimStage_getRegressTo, (setter)pyAnimStage_setRegressTo, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAnimStage_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAnimStage",           /* tp_name */
    sizeof(pyAnimStage),                /* tp_basicsize */
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
    "plAnimStage wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAnimStage_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyAnimStage_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyAnimStage___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyAnimStage_new,                    /* tp_new */
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

PyObject* Init_pyAnimStage_Type() {
    pyAnimStage_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAnimStage_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kNotifyEnter",
                         PyInt_FromLong(plAnimStage::kNotifyEnter));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kNotifyLoop",
                         PyInt_FromLong(plAnimStage::kNotifyLoop));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kNotifyAdvance",
                         PyInt_FromLong(plAnimStage::kNotifyAdvance));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kNotifyRegress",
                         PyInt_FromLong(plAnimStage::kNotifyRegress));

    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kPlayNone",
                         PyInt_FromLong(plAnimStage::kPlayNone));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kPlayKey",
                         PyInt_FromLong(plAnimStage::kPlayKey));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kPlayAuto",
                         PyInt_FromLong(plAnimStage::kPlayAuto));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kPlayMax",
                         PyInt_FromLong(plAnimStage::kPlayMax));

    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceNone",
                         PyInt_FromLong(plAnimStage::kAdvanceNone));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceOnMove",
                         PyInt_FromLong(plAnimStage::kAdvanceOnMove));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceAuto",
                         PyInt_FromLong(plAnimStage::kAdvanceAuto));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceOnAnyKey",
                         PyInt_FromLong(plAnimStage::kAdvanceOnAnyKey));
    PyDict_SetItemString(pyAnimStage_Type.tp_dict, "kAdvanceMax",
                         PyInt_FromLong(plAnimStage::kAdvanceMax));

    Py_INCREF(&pyAnimStage_Type);
    return (PyObject*)&pyAnimStage_Type;
}

int pyAnimStage_Check(PyObject* obj) {
    if (obj->ob_type == &pyAnimStage_Type
        || PyType_IsSubtype(obj->ob_type, &pyAnimStage_Type))
        return 1;
    return 0;
}

PyObject* pyAnimStage_FromAnimStage(plAnimStage* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAnimStage* pyobj = PyObject_New(pyAnimStage, &pyAnimStage_Type);
    pyobj->fThis = obj;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
