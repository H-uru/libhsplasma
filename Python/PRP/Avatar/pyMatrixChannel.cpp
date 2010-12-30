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
#include <PRP/Avatar/plMatrixChannel.h>
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"

extern "C" {

static PyObject* pyMatrixChannel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMatrixChannel* self = (pyMatrixChannel*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plMatrixChannel();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMatrixChannel_getAffine(pyMatrixChannel* self, void*) {
    return pyAffineParts_FromAffineParts(self->fThis->getAffine());
}

static int pyMatrixChannel_setAffine(pyMatrixChannel* self, PyObject* value, void*) {
    if (value == NULL || !pyAffineParts_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "result should be an hsAffineParts");
        return -1;
    }
    self->fThis->setAffine(*((pyAffineParts*)value)->fThis);
    return 0;
}

static PyMethodDef pyMatrixChannel_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyMatrixChannel_GetSet[] = {
    { "affine", (getter)pyMatrixChannel_getAffine, (setter)pyMatrixChannel_setAffine, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyMatrixChannel_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plMatrixChannel",         /* tp_name */
    sizeof(pyMatrixChannel),            /* tp_basicsize */
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
    "plMatrixChannel wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMatrixChannel_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyMatrixChannel_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMatrixChannel_new,                /* tp_new */
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

PyObject* Init_pyMatrixChannel_Type() {
    pyMatrixChannel_Type.tp_base = &pyAGChannel_Type;
    if (PyType_Ready(&pyMatrixChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyMatrixChannel_Type);
    return (PyObject*)&pyMatrixChannel_Type;
}

int pyMatrixChannel_Check(PyObject* obj) {
    if (obj->ob_type == &pyMatrixChannel_Type
        || PyType_IsSubtype(obj->ob_type, &pyMatrixChannel_Type))
        return 1;
    return 0;
}

PyObject* pyMatrixChannel_FromMatrixChannel(class plMatrixChannel* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMatrixChannel* pyobj = PyObject_New(pyMatrixChannel, &pyMatrixChannel_Type);
    delete pyobj->fThis;
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
