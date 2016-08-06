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

#include "pyKeyPressConditionalObject.h"

#include <PRP/ConditionalObject/plKeyPressConditionalObject.h>
#include "pyConditionalObject.h"

extern "C" {

static PyObject* pyKeyPressConditionalObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyKeyPressConditionalObject* self = (pyKeyPressConditionalObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plKeyPressConditionalObject();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyKeyPressConditionalObject_getKeyEvent(pyKeyPressConditionalObject* self, void*) {
    return PyInt_FromLong(self->fThis->getKeyEvent());
}

static int pyKeyPressConditionalObject_setKeyEvent(pyKeyPressConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "keyEvent should be an int");
        return -1;
    }
    self->fThis->setKeyEvent((plKeyDef)PyInt_AsLong(value));
    return 0;
}

static PyGetSetDef pyKeyPressConditionalObject_GetSet[] = {
    { _pycs("keyEvent"), (getter)pyKeyPressConditionalObject_getKeyEvent,
       (setter)pyKeyPressConditionalObject_setKeyEvent, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyKeyPressConditionalObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plKeyPressConditionalObject", /* tp_name */
    sizeof(pyKeyPressConditionalObject),      /* tp_basicsize */
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
    "plKeyPressConditionalObject wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyKeyPressConditionalObject_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyKeyPressConditionalObject_new,    /* tp_new */
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

PyObject* Init_pyKeyPressConditionalObject_Type() {
    pyKeyPressConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_Ready(&pyKeyPressConditionalObject_Type) < 0)
        return NULL;

    Py_INCREF(&pyKeyPressConditionalObject_Type);
    return (PyObject*)&pyKeyPressConditionalObject_Type;
}

int pyKeyPressConditionalObject_Check(PyObject* obj) {
    if (obj->ob_type == &pyKeyPressConditionalObject_Type
        || PyType_IsSubtype(obj->ob_type, &pyKeyPressConditionalObject_Type))
        return 1;
    return 0;
}

PyObject* pyKeyPressConditionalObject_FromKeyPressConditionalObject(class plKeyPressConditionalObject* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyKeyPressConditionalObject* py = PyObject_New(pyKeyPressConditionalObject, &pyKeyPressConditionalObject_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
