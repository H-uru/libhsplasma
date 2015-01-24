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
#include <PRP/Animation/plScaleController.h>
#include "pyScaleController.h"
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pySimpleScaleController___init__(pySimpleScaleController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pySimpleScaleController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySimpleScaleController* self = (pySimpleScaleController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSimpleScaleController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySimpleScaleController_getValue(pySimpleScaleController* self, void*) {
    return pyScaleValueController_FromScaleValueController(self->fThis->getValue());
}

static int pySimpleScaleController_setValue(pySimpleScaleController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setValue(NULL);
        return 0;
    }
    if (!pyScaleValueController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value should be a plScaleValueController");
        return -1;
    }
    self->fThis->setValue(((pyScaleValueController*)value)->fThis);
    ((pyScaleValueController*)value)->fPyOwned = false;
    return 0;
}

static PyMethodDef pySimpleScaleController_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pySimpleScaleController_GetSet[] = {
    { _pycs("value"), (getter)pySimpleScaleController_getValue,
        (setter)pySimpleScaleController_setValue, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySimpleScaleController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSimpleScaleController", /* tp_name */
    sizeof(pySimpleScaleController),    /* tp_basicsize */
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
    "plSimpleScaleController wrapper",  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySimpleScaleController_Methods,    /* tp_methods */
    NULL,                               /* tp_members */
    pySimpleScaleController_GetSet,     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pySimpleScaleController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pySimpleScaleController_new,        /* tp_new */
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

PyObject* Init_pySimpleScaleController_Type() {
    pySimpleScaleController_Type.tp_base = &pyScaleController_Type;
    if (PyType_Ready(&pySimpleScaleController_Type) < 0)
        return NULL;

    Py_INCREF(&pySimpleScaleController_Type);
    return (PyObject*)&pySimpleScaleController_Type;
}

int pySimpleScaleController_Check(PyObject* obj) {
    if (obj->ob_type == &pySimpleScaleController_Type
        || PyType_IsSubtype(obj->ob_type, &pySimpleScaleController_Type))
        return 1;
    return 0;
}

PyObject* pySimpleScaleController_FromSimpleScaleController(class plSimpleScaleController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySimpleScaleController* pyobj = PyObject_New(pySimpleScaleController, &pySimpleScaleController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
