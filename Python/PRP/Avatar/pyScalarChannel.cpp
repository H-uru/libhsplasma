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

#include "pyAGChannel.h"

#include <PRP/Avatar/plScalarChannel.h>
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyScalarChannel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyScalarChannel* self = (pyScalarChannel*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plScalarChannel();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyScalarChannel_getResult(pyScalarChannel* self, void*) {
    return PyFloat_FromDouble(self->fThis->getResult());
}

static int pyScalarChannel_setResult(pyScalarChannel* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "result should be a float");
        return -1;
    }
    self->fThis->setResult(PyFloat_AsDouble(value));
    return 0;
}

static PyMethodDef pyScalarChannel_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyScalarChannel_GetSet[] = {
    { _pycs("result"), (getter)pyScalarChannel_getResult,
        (setter)pyScalarChannel_setResult, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyScalarChannel_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plScalarChannel",       /* tp_name */
    sizeof(pyScalarChannel),            /* tp_basicsize */
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
    "plScalarChannel wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyScalarChannel_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyScalarChannel_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyScalarChannel_new,                /* tp_new */
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

PyObject* Init_pyScalarChannel_Type() {
    pyScalarChannel_Type.tp_base = &pyAGChannel_Type;
    if (PyType_Ready(&pyScalarChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyScalarChannel_Type);
    return (PyObject*)&pyScalarChannel_Type;
}

int pyScalarChannel_Check(PyObject* obj) {
    if (obj->ob_type == &pyScalarChannel_Type
        || PyType_IsSubtype(obj->ob_type, &pyScalarChannel_Type))
        return 1;
    return 0;
}

PyObject* pyScalarChannel_FromScalarChannel(class plScalarChannel* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScalarChannel* pyobj = PyObject_New(pyScalarChannel, &pyScalarChannel_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
