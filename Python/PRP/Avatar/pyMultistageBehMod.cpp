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

#include "pyMultistageBehMod.h"

#include <PRP/Avatar/plMultistageBehMod.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(MultistageBehMod, plMultistageBehMod)

PY_METHOD_VA(MultistageBehMod, addStage,
    "Params: stage\n"
    "Add a plAnimStage to the behavior mod")
{
    pyAnimStage* anim;
    if (!PyArg_ParseTuple(args, "O", &anim)) {
        PyErr_SetString(PyExc_TypeError, "addStage expects a plAnimStage");
        return NULL;
    }
    if (!pyAnimStage_Check((PyObject*)anim)) {
        PyErr_SetString(PyExc_TypeError, "addStage expects a plAnimStage");
        return NULL;
    }
    self->fThis->addStage(anim->fThis);
    anim->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(MultistageBehMod, delStage,
    "Params: idx\n"
    "Remove a stage from the behavior mod")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delStage expects an int");
        return NULL;
    }
    self->fThis->delStage(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(MultistageBehMod, clearStages,
    "Remove all stages from the behavior mod")
{
    self->fThis->clearStages();
    Py_RETURN_NONE;
}

PY_METHOD_VA(MultistageBehMod, addReceiver,
    "Params: key\n"
    "Add a receiver key to the behavior mod")
{
    pyKey* rcvr;
    if (!PyArg_ParseTuple(args, "O", &rcvr)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)rcvr)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    self->fThis->addReceiver(*rcvr->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(MultistageBehMod, delReceiver,
    "Params: idx\n"
    "Remove a receiver from the behavior mod")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delReceiver expects an int");
        return NULL;
    }
    self->fThis->delReceiver(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(MultistageBehMod, clearReceivers,
    "Remove all receivers from the behavior mod")
{
    self->fThis->clearReceivers();
    Py_RETURN_NONE;
}

static PyObject* pyMultistageBehMod_getStages(pyMultistageBehMod* self, void*) {
    PyObject* list = PyList_New(self->fThis->getStages().size());
    for (size_t i=0; i<self->fThis->getStages().size(); i++)
        PyList_SET_ITEM(list, i, ICreate(self->fThis->getStages()[i]));
    return list;
}

static PyObject* pyMultistageBehMod_getReceivers(pyMultistageBehMod* self, void*) {
    PyObject* list = PyList_New(self->fThis->getReceivers().size());
    for (size_t i=0; i<self->fThis->getReceivers().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getReceivers()[i]));
    return list;
}

static int pyMultistageBehMod_setStages(pyMultistageBehMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add stages, use addStage()");
    return -1;
}

static int pyMultistageBehMod_setReceivers(pyMultistageBehMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add receivers, use addReceiver()");
    return -1;
}

static PyMethodDef pyMultistageBehMod_Methods[] = {
    pyMultistageBehMod_addStage_method,
    pyMultistageBehMod_delStage_method,
    pyMultistageBehMod_clearStages_method,
    pyMultistageBehMod_addReceiver_method,
    pyMultistageBehMod_delReceiver_method,
    pyMultistageBehMod_clearReceivers_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(bool, MultistageBehMod, freezePhys, getFreezePhys, setFreezePhys)
PY_PROPERTY(bool, MultistageBehMod, smartSeek, getSmartSeek, setSmartSeek)
PY_PROPERTY(bool, MultistageBehMod, reverseFBControlsOnRelease,
            getReverseFBControlsOnRelease, setReverseFBControlsOnRelease)

static PyGetSetDef pyMultistageBehMod_GetSet[] = {
    { _pycs("stages"), (getter)pyMultistageBehMod_getStages,
        (setter)pyMultistageBehMod_setStages, NULL, NULL },
    { _pycs("receivers"), (getter)pyMultistageBehMod_getReceivers,
        (setter)pyMultistageBehMod_setReceivers, NULL, NULL },
    pyMultistageBehMod_freezePhys_getset,
    pyMultistageBehMod_smartSeek_getset,
    pyMultistageBehMod_reverseFBControlsOnRelease_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(MultistageBehMod, plMultistageBehMod, "plMultistageBehMod wrapper")

PY_PLASMA_TYPE_INIT(MultistageBehMod) {
    pyMultistageBehMod_Type.tp_new = pyMultistageBehMod_new;
    pyMultistageBehMod_Type.tp_methods = pyMultistageBehMod_Methods;
    pyMultistageBehMod_Type.tp_getset = pyMultistageBehMod_GetSet;
    pyMultistageBehMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyMultistageBehMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyMultistageBehMod_Type);
    return (PyObject*)&pyMultistageBehMod_Type;
}

PY_PLASMA_IFC_METHODS(MultistageBehMod, plMultistageBehMod)

}
