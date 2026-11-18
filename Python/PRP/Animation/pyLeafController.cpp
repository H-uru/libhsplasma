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
    PyObject* tup = PyTuple_New(2);
    PyTuple_SET_ITEM(tup, 0, pyPlasma_convert(self->fThis->getKeys()));
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
    if (!pyPlasma_check<std::vector<hsKeyFrame*>>(keySeq)|| !pyPlasma_check<unsigned int>(keyTypeObj)) {
        PyErr_SetString(PyExc_TypeError, "keys should be a tuple of: sequence (keyframes), int");
        return -1;
    }

    auto keyframes = pyPlasma_get<std::vector<hsKeyFrame*>>(keySeq);
    auto keyType = pyPlasma_get<unsigned int>(keyTypeObj);
    try {
        // The leaf controller copies the keyframes, so we do not need to transfer ownership here.
        self->fThis->setKeys(keyframes, keyType);
    } catch (const hsBadParamException& exc) {
        PyErr_SetString(PyExc_TypeError, exc.what());
        return -1;
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(LeafController, keys)

// EaseControllers are copied by the setter, so there is no need to worry
// about ownership transfer here.
PY_PROPERTY_VECTOR(plEaseController*, LeafController, easeControllers,
                   getEaseControllers, setEaseControllers)

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
