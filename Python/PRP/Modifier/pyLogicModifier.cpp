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

#include "pyLogicModifier.h"

#include <PRP/Modifier/plLogicModifier.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(LogicModifier, plLogicModifier)

PY_METHOD_NOARGS(LogicModifier, clearConditions, "Remove all condition keys") {
    self->fThis->clearConditions();
    Py_RETURN_NONE;
}

PY_METHOD_VA(LogicModifier, addCondition,
    "Params: key\n"
    "Add a condition key")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addCondition expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addCondition expects a plKey");
        return NULL;
    }
    self->fThis->addCondition(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(LogicModifier, delCondition,
    "Params: idx\n"
    "Remove a condition key")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCondition expects an int");
        return NULL;
    }
    self->fThis->delCondition(idx);
    Py_RETURN_NONE;
}

static PyObject* pyLogicModifier_getConditions(pyLogicModifier* self, void*) {
    PyObject* list = PyList_New(self->fThis->getConditions().size());
    for (size_t i=0; i<self->fThis->getConditions().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getConditions()[i]));
    return list;
}

static int pyLogicModifier_setConditions(pyLogicModifier* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add conditions, use addCondition");
    return -1;
}

static PyMethodDef pyLogicModifier_Methods[] = {
    pyLogicModifier_clearConditions_method,
    pyLogicModifier_addCondition_method,
    pyLogicModifier_delCondition_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(unsigned int, LogicModifier, cursor, getCursor, setCursor)
PY_PROPERTY(plKey, LogicModifier, parent, getParent, setParent)

static PyGetSetDef pyLogicModifier_GetSet[] = {
    { _pycs("conditions"), (getter)pyLogicModifier_getConditions,
        (setter)pyLogicModifier_setConditions, NULL, NULL },
    pyLogicModifier_cursor_getset,
    pyLogicModifier_parent_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyLogicModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plLogicModifier",       /* tp_name */
    sizeof(pyLogicModifier),            /* tp_basicsize */
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
    "plLogicModifier wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLogicModifier_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyLogicModifier_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLogicModifier_new,                /* tp_new */
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

PyObject* Init_pyLogicModifier_Type() {
    pyLogicModifier_Type.tp_base = &pyLogicModBase_Type;
    if (PyType_Ready(&pyLogicModifier_Type) < 0)
        return NULL;

    Py_INCREF(&pyLogicModifier_Type);
    return (PyObject*)&pyLogicModifier_Type;
}

PY_PLASMA_IFC_METHODS(LogicModifier, plLogicModifier)

}
