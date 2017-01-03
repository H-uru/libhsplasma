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

#include "pyInterfaceInfoModifier.h"

#include <PRP/Modifier/plInterfaceInfoModifier.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(InterfaceInfoModifier, plInterfaceInfoModifier)

PY_METHOD_NOARGS(InterfaceInfoModifier, clearIntfKeys, "Remove all interface keys") {
    self->fThis->clearIntfKeys();
    Py_RETURN_NONE;
}

PY_METHOD_VA(InterfaceInfoModifier, addIntfKey,
    "Params: key\n"
    "Add an interface key")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addIntfKey expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addIntfKey expects a plKey");
        return NULL;
    }
    self->fThis->addIntfKey(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(InterfaceInfoModifier, delIntfKey,
    "Params: idx\n"
    "Remove an interface key" )
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delIntfKey expects an int");
        return NULL;
    }
    self->fThis->delIntfKey(idx);
    Py_RETURN_NONE;
}

static PyObject* pyInterfaceInfoModifier_getIntfKeys(pyInterfaceInfoModifier* self, void*) {
    PyObject* list = PyList_New(self->fThis->getIntfKeys().size());
    for (size_t i=0; i<self->fThis->getIntfKeys().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getIntfKeys()[i]));
    return list;
}

static int pyInterfaceInfoModifier_setIntfKeys(pyInterfaceInfoModifier* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add interface keys, use addIntfKey");
    return -1;
}

static PyMethodDef pyInterfaceInfoModifier_Methods[] = {
    pyInterfaceInfoModifier_clearIntfKeys_method,
    pyInterfaceInfoModifier_addIntfKey_method,
    pyInterfaceInfoModifier_delIntfKey_method,
    PY_METHOD_TERMINATOR
};

static PyGetSetDef pyInterfaceInfoModifier_GetSet[] = {
    { _pycs("intfKeys"), (getter)pyInterfaceInfoModifier_getIntfKeys,
        (setter)pyInterfaceInfoModifier_setIntfKeys, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyInterfaceInfoModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plInterfaceInfoModifier", /* tp_name */
    sizeof(pyInterfaceInfoModifier),    /* tp_basicsize */
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
    "plInterfaceInfoModifier wrapper",  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyInterfaceInfoModifier_Methods,    /* tp_methods */
    NULL,                               /* tp_members */
    pyInterfaceInfoModifier_GetSet,     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyInterfaceInfoModifier_new,        /* tp_new */
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

PyObject* Init_pyInterfaceInfoModifier_Type() {
    pyInterfaceInfoModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyInterfaceInfoModifier_Type) < 0)
        return NULL;

    Py_INCREF(&pyInterfaceInfoModifier_Type);
    return (PyObject*)&pyInterfaceInfoModifier_Type;
}

PY_PLASMA_IFC_METHODS(InterfaceInfoModifier, plInterfaceInfoModifier)

}
