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

#include "pyBooleanConditionalObject.h"

#include <PRP/ConditionalObject/plBooleanConditionalObject.h>
#include "pyConditionalObject.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW(ORConditionalObject, plORConditionalObject)

PY_METHOD_VA(ORConditionalObject, addChild,
    "Params: key\n"
    "Adds a child condition key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addChild expects a plKey");
        return NULL;
    }
    self->fThis->addChild(*((pyKey*)key)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ORConditionalObject, clearChildren,
    "Removes all children condition keys")
{
    self->fThis->clearChildren();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ORConditionalObject, delChild,
    "Params: idx\n"
    "Removes a child condition key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delChild expects an int");
        return NULL;
    }
    self->fThis->delChild((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyORConditionalObject_Methods[] = {
    pyORConditionalObject_addChild_method,
    pyORConditionalObject_clearChildren_method,
    pyORConditionalObject_delChild_method,
    PY_METHOD_TERMINATOR
};

static PyObject* pyORConditionalObject_getORs(pyORConditionalObject* self, void*) {
    PyObject* children = PyTuple_New(self->fThis->getChildren().size());
    for (size_t i = 0; i < self->fThis->getChildren().size(); ++i)
        PyTuple_SET_ITEM(children, i, pyKey_FromKey(self->fThis->getChildren()[i]));
    return children;
}

static int pyORConditionalObject_setORs(pyORConditionalObject* self, PyObject*, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add children, use addChild()");
    return -1;
}

static PyGetSetDef pyORConditionalObject_GetSet[] = {
    { _pycs("children"), (getter)pyORConditionalObject_getORs,
       (setter)pyORConditionalObject_setORs, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ORConditionalObject, plORConditionalObject,
               "plORConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(ORConditionalObject) {
    pyORConditionalObject_Type.tp_new = pyORConditionalObject_new;
    pyORConditionalObject_Type.tp_methods = pyORConditionalObject_Methods;
    pyORConditionalObject_Type.tp_getset = pyORConditionalObject_GetSet;
    pyORConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_CheckAndReady(&pyORConditionalObject_Type) < 0)
        return NULL;

    Py_INCREF(&pyORConditionalObject_Type);
    return (PyObject*)&pyORConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(ORConditionalObject, plORConditionalObject)

};
