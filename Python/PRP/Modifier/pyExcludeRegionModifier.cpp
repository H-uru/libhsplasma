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

#include "pyExcludeRegionModifier.h"

#include <PRP/Modifier/plExcludeRegionModifier.h>
#include "pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(ExcludeRegionModifier, plExcludeRegionModifier)

PY_METHOD_VA(ExcludeRegionModifier, addSafePoint,
    "Params: key\n"
    "Adds a safe point key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addSafePoint expects a plKey");
        return nullptr;
    }
    self->fThis->addSafePoint(pyPlasma_get<plKey>(key));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ExcludeRegionModifier, clearSafePoints,
    "Removes all safe point keys")
{
    self->fThis->clearSafePoints();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ExcludeRegionModifier, delSafePoint,
    "Params: idx\n"
    "Removes a safe point key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delSafePoint expects an int");
        return nullptr;
    }
    if (size_t(idx) >= self->fThis->getSafePoints().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
    self->fThis->delSafePoint((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyExcludeRegionModifier_Methods[] = {
    pyExcludeRegionModifier_addSafePoint_method,
    pyExcludeRegionModifier_clearSafePoints_method,
    pyExcludeRegionModifier_delSafePoint_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(ExcludeRegionModifier, safePoints)
{
    const std::vector<plKey>& points = self->fThis->getSafePoints();
    PyObject* tup = PyTuple_New(points.size());
    for (size_t i = 0; i < points.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyKey_FromKey(points[i]));
    return tup;
}

PY_PROPERTY_SETTER_MSG(ExcludeRegionModifier, safePoints, "To add safePoints, use addSafePoint()")
PY_PROPERTY_GETSET_DECL(ExcludeRegionModifier, safePoints)

PY_PROPERTY(bool, ExcludeRegionModifier, seek, getSeek, setSeek)
PY_PROPERTY(float, ExcludeRegionModifier, seekTime, getSeekTime, setSeekTime)

static PyGetSetDef pyExcludeRegionModifier_GetSet[] = {
    pyExcludeRegionModifier_safePoints_getset,
    pyExcludeRegionModifier_seek_getset,
    pyExcludeRegionModifier_seekTime_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ExcludeRegionModifier, plExcludeRegionModifier,
               "plExcludeRegionModifier wrapper")

PY_PLASMA_TYPE_INIT(ExcludeRegionModifier)
{
    pyExcludeRegionModifier_Type.tp_new = pyExcludeRegionModifier_new;
    pyExcludeRegionModifier_Type.tp_methods = pyExcludeRegionModifier_Methods;
    pyExcludeRegionModifier_Type.tp_getset = pyExcludeRegionModifier_GetSet;
    pyExcludeRegionModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyExcludeRegionModifier_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ExcludeRegionModifier, "kBlockCameras",
                      plExcludeRegionModifier::kBlockCameras);

    Py_INCREF(&pyExcludeRegionModifier_Type);
    return (PyObject*)&pyExcludeRegionModifier_Type;
}

PY_PLASMA_IFC_METHODS(ExcludeRegionModifier, plExcludeRegionModifier)
