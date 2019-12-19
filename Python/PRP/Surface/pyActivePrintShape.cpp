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

#include "pyPrintShape.h"

#include "PRP/KeyedObject/pyKey.h"
#include <PRP/Surface/plPrintShape.h>

PY_PLASMA_NEW(ActivePrintShape, plActivePrintShape)

PY_METHOD_VA(ActivePrintShape, addDecalMgr,
    "Params: key\n"
    "Adds the specified decal manager key")
{
    PyObject* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyPlasma_check<plKey>(key)) {
        PyErr_SetString(PyExc_TypeError, "addDecalMgr expects a plKey");
        return nullptr;
    }

    self->fThis->addDecalMgr(pyPlasma_get<plKey>(key));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ActivePrintShape, clearDecalMgrs,
    "Clears the decal manager keys")
{
    self->fThis->clearDecalMgrs();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ActivePrintShape, delDecalMgr,
    "Params: idx\n"
    "Removes the specified decal manager key by index")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delDecalMgr expects an int");
        return nullptr;
    }

    if (idx < 0 || size_t(idx) >= self->fThis->getNumDecalMgrs()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }

    self->fThis->delDecalMgr(idx);
    Py_RETURN_NONE;
}
static PyMethodDef pyActivePrintShape_Methods[] = {
    pyActivePrintShape_addDecalMgr_method,
    pyActivePrintShape_clearDecalMgrs_method,
    pyActivePrintShape_delDecalMgr_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(ActivePrintShape, decalMgrs)
{
    PyObject* tup = PyTuple_New(self->fThis->getNumDecalMgrs());
    for (size_t i = 0; i < self->fThis->getNumDecalMgrs(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(self->fThis->getDecalMgr(i)));
    return tup;
}

PY_PROPERTY_GETSET_RO_DECL(ActivePrintShape, decalMgrs)

static PyGetSetDef pyActivePrintShape_GetSet[] = {
    pyActivePrintShape_decalMgrs_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ActivePrintShape, plActivePrintShape, "plActivePrintShape wrapper")

PY_PLASMA_TYPE_INIT(ActivePrintShape)
{
    pyActivePrintShape_Type.tp_new = pyActivePrintShape_new;
    pyActivePrintShape_Type.tp_methods = pyActivePrintShape_Methods;
    pyActivePrintShape_Type.tp_getset = pyActivePrintShape_GetSet;
    pyActivePrintShape_Type.tp_base = &pyPrintShape_Type;
    if (PyType_CheckAndReady(&pyActivePrintShape_Type) < 0)
        return nullptr;

    Py_INCREF(&pyActivePrintShape_Type);
    return (PyObject*)&pyActivePrintShape_Type;
}

PY_PLASMA_IFC_METHODS(ActivePrintShape, plActivePrintShape)
