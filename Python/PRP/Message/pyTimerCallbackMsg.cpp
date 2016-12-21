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

#include "pyTimerCallbackMsg.h"

#include <PRP/Message/plTimerCallbackMsg.h>
#include "pyMessage.h"

extern "C" {

static PyObject* pyTimerCallbackMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyTimerCallbackMsg* self = (pyTimerCallbackMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plTimerCallbackMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyTimerCallbackMsg_getID(pyTimerCallbackMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getID());
}

static PyObject* pyTimerCallbackMsg_getTime(pyTimerCallbackMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getTime());
}

static int pyTimerCallbackMsg_setID(pyTimerCallbackMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ID expects an int");
        return -1;
    }
    self->fThis->setID(PyInt_AsLong(value));
    return 0;
}

static int pyTimerCallbackMsg_setTime(pyTimerCallbackMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "time expects a float");
        return -1;
    }
    self->fThis->setTime((float)PyFloat_AsDouble(value));
    return 0;
}

static PyGetSetDef pyTimerCallbackMsg_GetSet[] = {
    { _pycs("ID"), (getter)pyTimerCallbackMsg_getID, (setter)pyTimerCallbackMsg_setID, NULL, NULL },
    { _pycs("time"), (getter)pyTimerCallbackMsg_getTime, (setter)pyTimerCallbackMsg_setTime, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyTimerCallbackMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plTimerCallbackMsg",    /* tp_name */
    sizeof(pyTimerCallbackMsg),         /* tp_basicsize */
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
    "plTimerCallbackMsg wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyTimerCallbackMsg_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyTimerCallbackMsg_new,             /* tp_new */
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

PyObject* Init_pyTimerCallbackMsg_Type() {
    pyTimerCallbackMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyTimerCallbackMsg_Type) < 0)
        return NULL;

    Py_INCREF(&pyTimerCallbackMsg_Type);
    return (PyObject*)&pyTimerCallbackMsg_Type;
}

PY_PLASMA_IFC_METHODS(TimerCallbackMsg, plTimerCallbackMsg)

}
