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
#include <PRP/Animation/hsKeys.h>
#include "pyKeys.h"
#include "Math/pyGeometry3.h"

extern "C" {

static int pyG3DSMaxKeyFrame___init__(pyG3DSMaxKeyFrame* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyG3DSMaxKeyFrame_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyG3DSMaxKeyFrame* self = (pyG3DSMaxKeyFrame*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsG3DSMaxKeyFrame();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyG3DSMaxKeyFrame_getValue(pyG3DSMaxKeyFrame* self, void*) {
    return pyAffineParts_FromAffineParts(self->fThis->fValue);
}

static int pyG3DSMaxKeyFrame_setValue(pyG3DSMaxKeyFrame* self, PyObject* value, void*) {
    if (value == NULL || !pyAffineParts_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value should be an hsAffineParts");
        return -1;
    }
    self->fThis->fValue = *((pyAffineParts*)value)->fThis;
    return 0;
}

static PyGetSetDef pyG3DSMaxKeyFrame_GetSet[] = {
    { "value", (getter)pyG3DSMaxKeyFrame_getValue, (setter)pyG3DSMaxKeyFrame_setValue, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyG3DSMaxKeyFrame_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsG3DSMaxKeyFrame",       /* tp_name */
    sizeof(pyG3DSMaxKeyFrame),          /* tp_basicsize */
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
    "hsG3DSMaxKeyFrame wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyG3DSMaxKeyFrame_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyG3DSMaxKeyFrame___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyG3DSMaxKeyFrame_new,              /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyG3DSMaxKeyFrame_Type() {
    pyG3DSMaxKeyFrame_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyG3DSMaxKeyFrame_Type) < 0)
        return NULL;

    Py_INCREF(&pyG3DSMaxKeyFrame_Type);
    return (PyObject*)&pyG3DSMaxKeyFrame_Type;
}

int pyG3DSMaxKeyFrame_Check(PyObject* obj) {
    if (obj->ob_type == &pyG3DSMaxKeyFrame_Type
        || PyType_IsSubtype(obj->ob_type, &pyG3DSMaxKeyFrame_Type))
        return 1;
    return 0;
}

PyObject* pyG3DSMaxKeyFrame_FromG3DSMaxKeyFrame(hsG3DSMaxKeyFrame* frame) {
    if (frame == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyG3DSMaxKeyFrame* pyobj = PyObject_New(pyG3DSMaxKeyFrame, &pyG3DSMaxKeyFrame_Type);
    pyobj->fThis = frame;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
