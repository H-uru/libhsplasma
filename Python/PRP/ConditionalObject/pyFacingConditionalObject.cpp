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
#include <PRP/ConditionalObject/plFacingConditionalObject.h>
#include "pyFacingConditionalObject.h"
#include "pyConditionalObject.h"

extern "C" {

static PyObject* pyFacingConditionalObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyFacingConditionalObject* self = (pyFacingConditionalObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plFacingConditionalObject();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyFacingConditionalObject_getTolerance(pyFacingConditionalObject* self, void*) {
    return PyFloat_FromDouble(self->fThis->getTolerance());
}

static PyObject* pyFacingConditionalObject_getDirectional(pyFacingConditionalObject* self, void*) {
    return PyBool_FromLong(self->fThis->getDirectional() ? 1 : 0);
}

static int pyFacingConditionalObject_setTolerance(pyFacingConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "tolerance should be a float");
        return -1;
    }
    self->fThis->setTolerance((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFacingConditionalObject_setDirectional(pyFacingConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "directional should be a boolean");
        return -1;
    }
    self->fThis->setDirectional(PyInt_AsLong(value) != 0);
    return 0;
}

static PyGetSetDef pyFacingConditionalObject_GetSet[] = {
    { _pycs("tolerance"), (getter)pyFacingConditionalObject_getTolerance,
       (setter)pyFacingConditionalObject_setTolerance, NULL, NULL },
    { _pycs("directional"), (getter)pyFacingConditionalObject_getDirectional,
       (setter)pyFacingConditionalObject_setDirectional, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyFacingConditionalObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plFacingConditionalObject", /* tp_name */
    sizeof(pyFacingConditionalObject),      /* tp_basicsize */
    0,                                      /* tp_itemsize */

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
    "plFacingConditionalObject wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyFacingConditionalObject_GetSet,   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFacingConditionalObject_new,      /* tp_new */
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

PyObject* Init_pyFacingConditionalObject_Type() {
    pyFacingConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_Ready(&pyFacingConditionalObject_Type) < 0)
        return NULL;

    Py_INCREF(&pyFacingConditionalObject_Type);
    return (PyObject*)&pyFacingConditionalObject_Type;
}

int pyFacingConditionalObject_Check(PyObject* obj) {
    if (obj->ob_type == &pyFacingConditionalObject_Type
        || PyType_IsSubtype(obj->ob_type, &pyFacingConditionalObject_Type))
        return 1;
    return 0;
}

PyObject* pyFacingConditionalObject_FromFacingConditionalObject(class plFacingConditionalObject* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyFacingConditionalObject* py = PyObject_New(pyFacingConditionalObject, &pyFacingConditionalObject_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
