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

#include "pyWaveSet.h"

#include <PRP/Surface/plWaveSet.h>
#include "pyFixedWaterState7.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(WaveSet7, plWaveSet7)

PY_METHOD_VA(WaveSet7, addShore,
    "Params: key\n"
    "Add a shore")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addShore expects a plKey");
        return nullptr;
    }
    self->fThis->addShore(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(WaveSet7, clearShores, "Remove all shores")
{
    self->fThis->clearShores();
    Py_RETURN_NONE;
}

PY_METHOD_VA(WaveSet7, delShore,
    "Params: idx\n"
    "Remove a shore")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delShore expects an int");
        return nullptr;
    }
    if (size_t(idx) >= self->fThis->getShores().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
    self->fThis->delShore(idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(WaveSet7, addDecal,
    "Params: key\n"
    "Add a decal")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addDecal expects a plKey");
        return nullptr;
    }
    self->fThis->addDecal(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(WaveSet7, clearDecals, "Remove all decals")
{
    self->fThis->clearDecals();
    Py_RETURN_NONE;
}

PY_METHOD_VA(WaveSet7, delDecal,
    "Params: idx\n"
    "Remove a decal")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delDecal expects an int");
        return nullptr;
    }
    if (size_t(idx) >= self->fThis->getDecals().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
    self->fThis->delDecal(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyWaveSet7_Methods[] = {
    pyWaveSet7_addShore_method,
    pyWaveSet7_clearShores_method,
    pyWaveSet7_delShore_method,
    pyWaveSet7_addDecal_method,
    pyWaveSet7_clearDecals_method,
    pyWaveSet7_delDecal_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(WaveSet7, shores)
{
    const std::vector<plKey>& shores = self->fThis->getShores();
    PyObject* tuple = PyTuple_New(shores.size());
    for (size_t i = 0; i < shores.size(); ++i)
        PyTuple_SET_ITEM(tuple, i, pyKey_FromKey(shores[i]));
    return tuple;
}

PY_PROPERTY_SETTER_MSG(WaveSet7, shores, "To add shores, use addShore")
PY_PROPERTY_GETSET_DECL(WaveSet7, shores)

PY_GETSET_GETTER_DECL(WaveSet7, decals)
{
    const std::vector<plKey>& decals = self->fThis->getDecals();
    PyObject* tuple = PyTuple_New(decals.size());
    for (size_t i = 0; i < decals.size(); ++i)
        PyTuple_SET_ITEM(tuple, i, pyKey_FromKey(decals[i]));
    return tuple;
}

PY_PROPERTY_SETTER_MSG(WaveSet7, decals, "To add decals, use addDecal")
PY_PROPERTY_GETSET_DECL(WaveSet7, decals)

PY_PROPERTY_PROXY(plFixedWaterState7, WaveSet7, state, getState)
PY_PROPERTY(float, WaveSet7, maxLen, getMaxLen, setMaxLen)
PY_PROPERTY(plKey, WaveSet7, envMap, getEnvMap, setEnvMap)
PY_PROPERTY(plKey, WaveSet7, refObj, getRefObj, setRefObj)

static PyGetSetDef pyWaveSet7_GetSet[] = {
    pyWaveSet7_state_getset,
    pyWaveSet7_shores_getset,
    pyWaveSet7_decals_getset,
    pyWaveSet7_maxLen_getset,
    pyWaveSet7_envMap_getset,
    pyWaveSet7_refObj_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(WaveSet7, plWaveSet7, "plWaveSet7 wrapper")

PY_PLASMA_TYPE_INIT(WaveSet7)
{
    pyWaveSet7_Type.tp_new = pyWaveSet7_new;
    pyWaveSet7_Type.tp_methods = pyWaveSet7_Methods;
    pyWaveSet7_Type.tp_getset = pyWaveSet7_GetSet;
    pyWaveSet7_Type.tp_base = &pyWaveSetBase_Type;
    if (PyType_CheckAndReady(&pyWaveSet7_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(WaveSet7, "kHasRefObject", plWaveSet7::kHasRefObject);

    Py_INCREF(&pyWaveSet7_Type);
    return (PyObject*)&pyWaveSet7_Type;
}

PY_PLASMA_IFC_METHODS(WaveSet7, plWaveSet7)
