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

#include "pyDetectorModifier.h"

#include <PRP/Physics/plDetectorModifier.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Modifier/pyModifier.h"

PY_PLASMA_NEW_MSG(DetectorModifier, "plDetectorModifier is abstract")

PY_METHOD_VA(DetectorModifier, addReceiver,
    "Params: key\n"
    "Adds a notification receiver to this detector")
{
    PyObject* receiver;
    if (!(PyArg_ParseTuple(args, "O", &receiver) && pyKey_Check(receiver))) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return nullptr;
    }

    self->fThis->addReceiver(pyPlasma_get<plKey>(receiver));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DetectorModifier, clearReceivers,
    "Removes all receivers from this detector")
{
    self->fThis->clearReceivers();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DetectorModifier, delReceiver,
    "Params: idx\n"
    "Removes a receiver from this detector")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delReceiver expects an int");
        return nullptr;
    }

    self->fThis->delReceiver((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyDetectorModifier_Methods[] = {
    pyDetectorModifier_addReceiver_method,
    pyDetectorModifier_clearReceivers_method,
    pyDetectorModifier_delReceiver_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(DetectorModifier, receivers)
{
    plDetectorModifier* mod = self->fThis;
    PyObject* sequence = PyTuple_New(mod->getReceivers().size());
    for (size_t i = 0; i < mod->getReceivers().size(); ++i)
        PyTuple_SET_ITEM(sequence, i, pyKey_FromKey(mod->getReceivers()[i]));
    return sequence;
}

PY_PROPERTY_SETTER_MSG(DetectorModifier, receivers, "To add receivers, use addReceiver")
PY_PROPERTY_GETSET_DECL(DetectorModifier, receivers)

PY_PROPERTY(plKey, DetectorModifier, remoteMod, getRemoteMod, setRemoteMod)
PY_PROPERTY(plKey, DetectorModifier, proxy, getProxy, setProxy)

static PyGetSetDef pyDetectorModifier_GetSet[] = {
    pyDetectorModifier_receivers_getset,
    pyDetectorModifier_remoteMod_getset,
    pyDetectorModifier_proxy_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DetectorModifier, plDetectorModifier, "plDetectorModifier wrapper")

PY_PLASMA_TYPE_INIT(DetectorModifier)
{
    pyDetectorModifier_Type.tp_new = pyDetectorModifier_new;
    pyDetectorModifier_Type.tp_methods = pyDetectorModifier_Methods;
    pyDetectorModifier_Type.tp_getset = pyDetectorModifier_GetSet;
    pyDetectorModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyDetectorModifier_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDetectorModifier_Type);
    return (PyObject*)&pyDetectorModifier_Type;
}

PY_PLASMA_IFC_METHODS(DetectorModifier, plDetectorModifier)
