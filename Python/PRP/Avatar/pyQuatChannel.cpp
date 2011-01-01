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
#include <PRP/Avatar/plQuatChannel.h>
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"

extern "C" {

static PyObject* pyQuatChannel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyQuatChannel* self = (pyQuatChannel*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plQuatChannel();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyQuatChannel_getResult(pyQuatChannel* self, void*) {
    return pyQuat_FromQuat(self->fThis->getResult());
}

static int pyQuatChannel_setResult(pyQuatChannel* self, PyObject* value, void*) {
    if (value == NULL || !pyQuat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "result should be an hsQuat");
        return -1;
    }
    self->fThis->setResult(*((pyQuat*)value)->fThis);
    return 0;
}

static PyMethodDef pyQuatChannel_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyQuatChannel_GetSet[] = {
    { "result", (getter)pyQuatChannel_getResult, (setter)pyQuatChannel_setResult, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyQuatChannel_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plQuatChannel",           /* tp_name */
    sizeof(pyQuatChannel),              /* tp_basicsize */
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
    "plQuatChannel wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyQuatChannel_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyQuatChannel_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyQuatChannel_new,                /* tp_new */
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

PyObject* Init_pyQuatChannel_Type() {
    pyQuatChannel_Type.tp_base = &pyAGChannel_Type;
    if (PyType_Ready(&pyQuatChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyQuatChannel_Type);
    return (PyObject*)&pyQuatChannel_Type;
}

int pyQuatChannel_Check(PyObject* obj) {
    if (obj->ob_type == &pyQuatChannel_Type
        || PyType_IsSubtype(obj->ob_type, &pyQuatChannel_Type))
        return 1;
    return 0;
}

PyObject* pyQuatChannel_FromQuatChannel(class plQuatChannel* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyQuatChannel* pyobj = PyObject_New(pyQuatChannel, &pyQuatChannel_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
