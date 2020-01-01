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

#include "pyLeafController.h"

#include <PRP/Animation/plLeafController.h>
#include <PRP/Animation/plKeyControllers.hpp>
#include "pyController.h"
#include "pyKeys.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_EMPTY_INIT(LeafController)
PY_PLASMA_NEW(LeafController, plLeafController)

PY_METHOD_NOARGS(LeafController, hasKeys, nullptr)
{
    return pyPlasma_convert(self->fThis->hasKeys());
}

PY_METHOD_NOARGS(LeafController, hasEaseControllers, nullptr)
{
    return pyPlasma_convert(self->fThis->hasEaseControllers());
}

PY_METHOD_NOARGS(LeafController, ExpandToKeyController, nullptr)
{
    return ICreate(self->fThis->ExpandToKeyController());
}

PY_METHOD_NOARGS(LeafController, CompactToLeafController, nullptr)
{
    return ICreate(self->fThis->CompactToLeafController());
}

static PyMethodDef pyLeafController_Methods[] = {
    pyLeafController_hasKeys_method,
    pyLeafController_hasEaseControllers_method,
    pyLeafController_ExpandToKeyController_method,
    pyLeafController_CompactToLeafController_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(LeafController, keys)
{
    const std::vector<hsKeyFrame*>& keys = self->fThis->getKeys();
    PyObject* keyTup = PyTuple_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyTuple_SET_ITEM(keyTup, i, pyPlasma_convert(keys[i]));
    PyObject* tup = PyTuple_New(2);
    PyTuple_SET_ITEM(tup, 0, keyTup);
    PyTuple_SET_ITEM(tup, 1, pyPlasma_convert(self->fThis->getType()));
    return tup;
}

PY_GETSET_SETTER_DECL(LeafController, keys)
{
    PY_PROPERTY_CHECK_NULL(keys)
    if (!PyTuple_Check(value) || PyTuple_Size(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "keys should be a tuple of: sequence (keyframes), int");
        return -1;
    }

    PyObject* keySeqObj = PyTuple_GET_ITEM(value, 0);
    PyObject* keyTypeObj = PyTuple_GET_ITEM(value, 1);
    pySequenceFastRef keySeq(keySeqObj);
    if (!keySeq.isSequence()|| !pyPlasma_check<unsigned int>(keyTypeObj)) {
        PyErr_SetString(PyExc_TypeError, "keys should be a tuple of: sequence (keyframes), int");
        return -1;
    }

    Py_ssize_t keyCount = keySeq.size();
    std::vector<hsKeyFrame*> keyframes;
    keyframes.reserve(keyCount);
    unsigned int keyType = pyPlasma_get<unsigned int>(keyTypeObj);
    for (Py_ssize_t i = 0; i < keyCount; ++i) {
        PyObject* key = keySeq.get(i);
        if (!pyKeyFrame_Check(key)) {
            PyErr_SetString(PyExc_TypeError, "keys should be a tuple of: sequence (keyframes), int");
            return -1;
        }
        hsKeyFrame* keyframe = ((pyKeyFrame*)key)->fThis;
        if (keyframe->getType() != keyType) {
            PyErr_SetString(PyExc_TypeError, ST::format("keys should be of type {}, not {}",
                                                        hsKeyFrame::TypeNames[keyType],
                                                        hsKeyFrame::TypeNames[keyframe->getType()]
                                                        ).c_str());
            return -1;
        }
        keyframes.push_back(keyframe);
        ((pyKeyFrame*)key)->fPyOwned = false;
    }
    self->fThis->setKeys(keyframes, keyType);
    return 0;
}

PY_PROPERTY_GETSET_DECL(LeafController, keys)

PY_GETSET_GETTER_DECL(LeafController, easeControllers)
{
    const std::vector<plEaseController*>& controllers = self->fThis->getEaseControllers();
    PyObject* list = PyTuple_New(controllers.size());
    for (size_t i=0; i<controllers.size(); i++)
        PyTuple_SET_ITEM(list, i, ICreate(controllers[i]));
    return list;
}

PY_GETSET_SETTER_DECL(LeafController, easeControllers)
{
    PY_PROPERTY_CHECK_NULL(easeControllers)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "easeControllers should be a sequence of plEaseControllers");
        return -1;
    }
    std::vector<plEaseController*> controllers(seq.size());
    for (size_t i=0; i<controllers.size(); i++) {
        PyObject* itm = seq.get(i);
        if (!pyEaseController_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "easeControllers should be a sequence of plEaseControllers");
            return -1;
        }
        controllers[i] = ((pyEaseController*)itm)->fThis;
        ((pyEaseController*)itm)->fPyOwned = false;
    }
    self->fThis->setEaseControllers(controllers);
    return 0;
}

PY_PROPERTY_GETSET_DECL(LeafController, easeControllers)

PY_PROPERTY_READ(LeafController, type, getType)
PY_PROPERTY_SETTER_MSG(LeafController, type, "To set the key type, use the keys setter")
PY_PROPERTY_GETSET_DECL(LeafController, type)

static PyGetSetDef pyLeafController_GetSet[] = {
    pyLeafController_type_getset,
    pyLeafController_keys_getset,
    pyLeafController_easeControllers_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LeafController, plLeafController, "plLeafController wrapper")

PY_PLASMA_TYPE_INIT(LeafController)
{
    pyLeafController_Type.tp_init = pyLeafController___init__;
    pyLeafController_Type.tp_new = pyLeafController_new;
    pyLeafController_Type.tp_methods = pyLeafController_Methods;
    pyLeafController_Type.tp_getset = pyLeafController_GetSet;
    pyLeafController_Type.tp_base = &pyController_Type;
    if (PyType_CheckAndReady(&pyLeafController_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLeafController_Type);
    return (PyObject*)&pyLeafController_Type;
}

PY_PLASMA_IFC_METHODS(LeafController, plLeafController)
