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
#include <PRP/ConditionalObject/plAnimationEventConditionalObject.h>
#include "pyAnimationEventConditionalObject.h"
#include "pyConditionalObject.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyAnimationEventConditionalObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAnimationEventConditionalObject* self = (pyAnimationEventConditionalObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAnimationEventConditionalObject();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAnimationEventConditionalObject_getAction(pyAnimationEventConditionalObject* self, void*) {
    return PyInt_FromLong(self->fThis->getAction());
}

static PyObject* pyAnimationEventConditionalObject_getTarget(pyAnimationEventConditionalObject* self, void*) {
    return pyKey_FromKey(self->fThis->getTarget());
}

static int pyAnimationEventConditionalObject_setAction(pyAnimationEventConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "action should be an int");
        return -1;
    }
    self->fThis->setAction((CallbackEvent)PyInt_AsLong(value));
    return 0;
}

static int pyAnimationEventConditionalObject_setTarget(pyAnimationEventConditionalObject* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setTarget(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setTarget(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "target expects a plKey");
        return -1;
    }
}

static PyGetSetDef pyAnimationEventConditionalObject_GetSet[] = {
    { _pycs("action"), (getter)pyAnimationEventConditionalObject_getAction,
       (setter)pyAnimationEventConditionalObject_setAction, NULL, NULL },
    { _pycs("target"), (getter)pyAnimationEventConditionalObject_getTarget,
       (setter)pyAnimationEventConditionalObject_setTarget, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAnimationEventConditionalObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAnimationEventConditionalObject", /* tp_name */
    sizeof(pyAnimationEventConditionalObject),      /* tp_basicsize */
    0,                                             /* tp_itemsize */

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
    "plAnimationEventConditionalObject wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyAnimationEventConditionalObject_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAnimationEventConditionalObject_new, /* tp_new */
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

PyObject* Init_pyAnimationEventConditionalObject_Type() {
    pyAnimationEventConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_Ready(&pyAnimationEventConditionalObject_Type) < 0)
        return NULL;

    Py_INCREF(&pyAnimationEventConditionalObject_Type);
    return (PyObject*)&pyAnimationEventConditionalObject_Type;
}

int pyAnimationEventConditionalObject_Check(PyObject* obj) {
    if (obj->ob_type == &pyAnimationEventConditionalObject_Type
        || PyType_IsSubtype(obj->ob_type, &pyAnimationEventConditionalObject_Type))
        return 1;
    return 0;
}

PyObject* pyAnimationEventConditionalObject_FromAnimationEventConditionalObject(class plAnimationEventConditionalObject* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAnimationEventConditionalObject* py = PyObject_New(pyAnimationEventConditionalObject, &pyAnimationEventConditionalObject_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
