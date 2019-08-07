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

#include "pyObjInterface.h"

#include <PRP/Object/plDrawInterface.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(DrawInterface, plDrawInterface)

PY_METHOD_NOARGS(DrawInterface, clearDrawables,
    "Removes all drawables from the Draw Interface")
{
    self->fThis->clearDrawables();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawInterface, addDrawable,
    "Params: (key, idx,)\n"
    "Adds a drawable reference and key index to the Draw Interface")
{
    pyKey* draw;
    int key;
    if (!PyArg_ParseTuple(args, "Oi", &draw, &key)) {
        PyErr_SetString(PyExc_TypeError, "addDrawable expects plKey, int");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)draw)) {
        PyErr_SetString(PyExc_TypeError, "addDrawable expects plKey, int");
        return nullptr;
    }
    self->fThis->addDrawable(*draw->fThis, key);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawInterface, delDrawable,
    "Params: idx\n"
    "Removes a drawable reference and key from the Draw Interface")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delDrawable expects an int");
        return nullptr;
    }
    self->fThis->delDrawable(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DrawInterface, clearRegions,
    "Removes all regions from the Draw Interface")
{
    self->fThis->clearRegions();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawInterface, addRegion,
    "Params: key\n"
    "Adds a region to the Draw Interface")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return nullptr;
    }
    self->fThis->addRegion(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DrawInterface, delRegion,
    "Params: idx\n"
    "Removes a region from the Draw Interface")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delRegion expects an int");
        return nullptr;
    }
    self->fThis->delRegion(idx);
    Py_RETURN_NONE;
}

PyMethodDef pyDrawInterface_Methods[] = {
    pyDrawInterface_clearDrawables_method,
    pyDrawInterface_addDrawable_method,
    pyDrawInterface_delDrawable_method,
    pyDrawInterface_clearRegions_method,
    pyDrawInterface_addRegion_method,
    pyDrawInterface_delRegion_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(DrawInterface, drawables)
{
    PyObject* list = PyTuple_New(self->fThis->getNumDrawables());
    for (size_t i=0; i<self->fThis->getNumDrawables(); i++) {
        PyObject* tup = Py_BuildValue("(Oi)",
            pyKey_FromKey(self->fThis->getDrawable(i)),
            self->fThis->getDrawableKey(i));
        if (tup == nullptr)
            return nullptr;
        PyTuple_SET_ITEM(list, i, tup);
    }
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawInterface, drawables, "To add Drawables, use addDrawable")
PY_PROPERTY_GETSET_DECL(DrawInterface, drawables)

PY_GETSET_GETTER_DECL(DrawInterface, regions)
{
    PyObject* list = PyTuple_New(self->fThis->getRegions().size());
    for (size_t i=0; i<self->fThis->getRegions().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getRegions()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(DrawInterface, regions, "To add Regions, use addRegion")
PY_PROPERTY_GETSET_DECL(DrawInterface, regions)

PyGetSetDef pyDrawInterface_GetSet[] = {
    pyDrawInterface_drawables_getset,
    pyDrawInterface_regions_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DrawInterface, plDrawInterface, "plDrawInterface wrapper")

PY_PLASMA_TYPE_INIT(DrawInterface)
{
    pyDrawInterface_Type.tp_new = pyDrawInterface_new;
    pyDrawInterface_Type.tp_methods = pyDrawInterface_Methods;
    pyDrawInterface_Type.tp_getset = pyDrawInterface_GetSet;
    pyDrawInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pyDrawInterface_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDrawInterface_Type);
    return (PyObject*)&pyDrawInterface_Type;
}

PY_PLASMA_IFC_METHODS(DrawInterface, plDrawInterface)
