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

#include "pyMsgForwarder.h"

#include <PRP/Message/plMsgForwarder.h>
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(MsgForwarder, plMsgForwarder)

PY_METHOD_NOARGS(MsgForwarder, clearForwardKeys,
    "Remove all forward keys from the forwarder")
{
    self->fThis->clearForwardKeys();
    Py_RETURN_NONE;
}

PY_METHOD_VA(MsgForwarder, addForwardKey,
    "Params: key\n"
    "Add a forward key to the forwarder")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addForwardKey expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addForwardKey expects a plKey");
        return NULL;
    }
    self->fThis->addForwardKey(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(MsgForwarder, delForwardKey,
    "Params: idx\n"
    "Remove a forward key from the forwarder")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delForwardKey expects an int");
        return NULL;
    }
    self->fThis->delForwardKey(idx);
    Py_RETURN_NONE;
}

static PyObject* pyMsgForwarder_getForwardKeys(pyMsgForwarder* self, void*) {
    PyObject* list = PyList_New(self->fThis->getForwardKeys().size());
    for (size_t i=0; i<self->fThis->getForwardKeys().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getForwardKeys()[i]));
    return list;
}

static int pyMsgForwarder_setForwardKeys(pyMsgForwarder* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add forward keys, use addForwardKey");
    return -1;
}

static PyMethodDef pyMsgForwarder_Methods[] = {
    pyMsgForwarder_clearForwardKeys_method,
    pyMsgForwarder_addForwardKey_method,
    pyMsgForwarder_delForwardKey_method,
    PY_METHOD_TERMINATOR
};

static PyGetSetDef pyMsgForwarder_GetSet[] = {
    { _pycs("forwardKeys"), (getter)pyMsgForwarder_getForwardKeys,
        (setter)pyMsgForwarder_setForwardKeys, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyMsgForwarder_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plMsgForwarder",        /* tp_name */
    sizeof(pyMsgForwarder),             /* tp_basicsize */
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
    "plMsgForwarder wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMsgForwarder_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyMsgForwarder_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMsgForwarder_new,                 /* tp_new */
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

PyObject* Init_pyMsgForwarder_Type() {
    pyMsgForwarder_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyMsgForwarder_Type) < 0)
        return NULL;

    Py_INCREF(&pyMsgForwarder_Type);
    return (PyObject*)&pyMsgForwarder_Type;
}

PY_PLASMA_IFC_METHODS(MsgForwarder, plMsgForwarder)

}
