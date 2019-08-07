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

#include "pySoftVolume.h"

#include <PRP/Region/plSoftVolume.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW_MSG(SoftVolumeComplex, "plSoftVolumeComplex is abstract")

PY_METHOD_VA(SoftVolumeComplex, addSubVolume,
    "Params: key\n"
    "Adds a softvolume key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addSubVolume expects a plKey");
        return nullptr;
    }
    self->fThis->addSubVolume(pyPlasma_get<plKey>(key));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(SoftVolumeComplex, clearSubVolumes,
    "Removes all softvolume keys")
{
    self->fThis->clearSubVolumes();
    Py_RETURN_NONE;
}

PY_METHOD_VA(SoftVolumeComplex, delSubVolume,
    "Params: idx\n"
    "Removes a softvolume key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delSubVolume expects an int");
        return nullptr;
    }
    if (size_t(idx) >= self->fThis->getSubVolumes().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
    self->fThis->delSubVolume((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pySoftVolumeComplex_Methods[] = {
    pySoftVolumeComplex_addSubVolume_method,
    pySoftVolumeComplex_clearSubVolumes_method,
    pySoftVolumeComplex_delSubVolume_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(SoftVolumeComplex, subVolumes)
{
    const std::vector<plKey>& sv = self->fThis->getSubVolumes();
    PyObject* tup = PyTuple_New(sv.size());
    for (size_t i = 0; i < sv.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyKey_FromKey(sv[i]));
    return tup;
}

PY_PROPERTY_SETTER_MSG(SoftVolumeComplex, subVolumes, "To add subvolumes, use addSubVolume")
PY_PROPERTY_GETSET_DECL(SoftVolumeComplex, subVolumes)

PyGetSetDef pySoftVolumeComplex_GetSet[] = {
    pySoftVolumeComplex_subVolumes_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SoftVolumeComplex, plSoftVolumeComplex, "plSoftVolumeComplex wrapper")

PY_PLASMA_TYPE_INIT(SoftVolumeComplex)
{
    pySoftVolumeComplex_Type.tp_new = pySoftVolumeComplex_new;
    pySoftVolumeComplex_Type.tp_methods = pySoftVolumeComplex_Methods;
    pySoftVolumeComplex_Type.tp_getset = pySoftVolumeComplex_GetSet;
    pySoftVolumeComplex_Type.tp_base = &pySoftVolume_Type;
    if (PyType_CheckAndReady(&pySoftVolumeComplex_Type) < 0)
        return nullptr;

    Py_INCREF(&pySoftVolumeComplex_Type);
    return (PyObject*)&pySoftVolumeComplex_Type;
}

PY_PLASMA_IFC_METHODS(SoftVolumeComplex, plSoftVolumeComplex)
