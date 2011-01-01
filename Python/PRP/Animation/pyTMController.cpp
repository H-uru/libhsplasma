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
#include <PRP/Animation/plTMController.h>
#include "pyController.h"
#include "pyPosController.h"
#include "pyRotController.h"
#include "pyScaleController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pyTMController___init__(pyTMController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyTMController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyTMController* self = (pyTMController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plTMController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyTMController_getPos(pyTMController* self, void*) {
    return pyPosController_FromPosController(self->fThis->getPosController());
}

static PyObject* pyTMController_getRot(pyTMController* self, void*) {
    return pyRotController_FromRotController(self->fThis->getRotController());
}

static PyObject* pyTMController_getScale(pyTMController* self, void*) {
    return pyScaleController_FromScaleController(self->fThis->getScaleController());
}

static int pyTMController_setPos(pyTMController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setPosController(NULL);
        return 0;
    }
    if (!pyPosController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "pos should be a plPosController");
        return -1;
    }
    self->fThis->setPosController(((pyPosController*)value)->fThis);
    ((pyPosController*)value)->fPyOwned = false;
    return 0;
}

static int pyTMController_setRot(pyTMController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setRotController(NULL);
        return 0;
    }
    if (!pyRotController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "rot should be a plRotController");
        return -1;
    }
    self->fThis->setRotController(((pyRotController*)value)->fThis);
    ((pyRotController*)value)->fPyOwned = false;
    return 0;
}

static int pyTMController_setScale(pyTMController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setScaleController(NULL);
        return 0;
    }
    if (!pyScaleController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "scale should be a plSclaeController");
        return -1;
    }
    self->fThis->setScaleController(((pyScaleController*)value)->fThis);
    ((pyScaleController*)value)->fPyOwned = false;
    return 0;
}

static PyMethodDef pyTMController_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyTMController_GetSet[] = {
    { "pos", (getter)pyTMController_getPos, (setter)pyTMController_setPos, NULL, NULL },
    { "rot", (getter)pyTMController_getRot, (setter)pyTMController_setRot, NULL, NULL },
    { "scale", (getter)pyTMController_getScale, (setter)pyTMController_setScale, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyTMController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plTMController",          /* tp_name */
    sizeof(pyTMController),             /* tp_basicsize */
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
    "plTMController wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyTMController_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyTMController_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyTMController___init__,  /* tp_init */
    NULL,                               /* tp_alloc */
    pyTMController_new,                 /* tp_new */
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

PyObject* Init_pyTMController_Type() {
    pyTMController_Type.tp_base = &pyController_Type;
    if (PyType_Ready(&pyTMController_Type) < 0)
        return NULL;

    Py_INCREF(&pyTMController_Type);
    return (PyObject*)&pyTMController_Type;
}

int pyTMController_Check(PyObject* obj) {
    if (obj->ob_type == &pyTMController_Type
        || PyType_IsSubtype(obj->ob_type, &pyTMController_Type))
        return 1;
    return 0;
}

PyObject* pyTMController_FromTMController(class plTMController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyTMController* pyobj = PyObject_New(pyTMController, &pyTMController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
