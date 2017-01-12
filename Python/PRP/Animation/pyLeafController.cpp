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

extern "C" {

PY_PLASMA_EMPTY_INIT(LeafController)
PY_PLASMA_NEW(LeafController, plLeafController)

PY_METHOD_NOARGS(LeafController, hasKeys, NULL) {
    return pyPlasma_convert(self->fThis->hasKeys());
}

PY_METHOD_NOARGS(LeafController, hasEaseControllers, NULL) {
    return pyPlasma_convert(self->fThis->hasEaseControllers());
}

PY_METHOD_NOARGS(LeafController, ExpandToKeyController, NULL) {
    return ICreate(self->fThis->ExpandToKeyController());
}

PY_METHOD_NOARGS(LeafController, CompactToLeafController, NULL) {
    return ICreate(self->fThis->CompactToLeafController());
}

static PyObject* pyLeafController_getKeys(pyLeafController* self, void*) {
    const std::vector<hsKeyFrame*>& keys = self->fThis->getKeys();
    PyObject* keyTup = PyTuple_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyTuple_SET_ITEM(keyTup, i, pyKeyFrame_FromKeyFrame(keys[i]));
    PyObject* tup = PyTuple_New(2);
    PyTuple_SET_ITEM(tup, 0, keyTup);
    PyTuple_SET_ITEM(tup, 1, pyPlasma_convert(self->fThis->getType()));
    return tup;
}

static PyObject* pyLeafController_getEaseControllers(pyLeafController* self, void*) {
    const std::vector<plEaseController*>& controllers = self->fThis->getEaseControllers();
    PyObject* list = PyList_New(controllers.size());
    for (size_t i=0; i<controllers.size(); i++)
        PyList_SET_ITEM(list, i, ICreate(controllers[i]));
    return list;
}

static int pyLeafController_setKeys(pyLeafController* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value) || PySequence_Size(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "keys should be a sequence of: sequence (keyframes), int");
        return -1;
    }

    PyObject* keySeq = PySequence_GetItem(value, 0);
    PyObject* keyTypeObj = PySequence_GetItem(value, 1);
    if (!PySequence_Check(keySeq) || !PyInt_Check(keyTypeObj)) {
        PyErr_SetString(PyExc_TypeError, "keys should be a sequence of: sequence (keyframes), int");
        return -1;
    }

    std::vector<hsKeyFrame*> keyframes;
    keyframes.reserve(PySequence_Size(keySeq));
    unsigned int keyType = PyInt_AsLong(keyTypeObj);
    for (Py_ssize_t i = 0; i < PySequence_Size(keySeq); ++i) {
        PyObject* key = PySequence_GetItem(keySeq, i);
        if (!pyKeyFrame_Check(key)) {
            PyErr_SetString(PyExc_TypeError, "keys should be a sequence of: sequence (keyframes), int");
            return -1;
        }
        hsKeyFrame* keyframe = ((pyKeyFrame*)key)->fThis;
        if (keyframe->getType() != keyType) {
            PyErr_SetString(PyExc_TypeError, plString::Format("keys should be of type %s, not %s",
                                                              hsKeyFrame::TypeNames[keyType],
                                                              hsKeyFrame::TypeNames[keyframe->getType()]
                                                              ).cstr());
            return -1;
        }
        keyframes.push_back(keyframe);
    }
    self->fThis->setKeys(keyframes, keyType);
    return 0;
}

static int pyLeafController_setEaseControllers(pyLeafController* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setEaseControllers(std::vector<plEaseController*>());
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "easeControllers should be a list of plEaseControllers");
        return -1;
    }
    std::vector<plEaseController*> controllers(PyList_Size(value));
    for (size_t i=0; i<controllers.size(); i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!pyEaseController_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "easeControllers should be a list of plEaseControllers");
            return -1;
        }
        controllers[i] = ((pyEaseController*)itm)->fThis;
    }
    self->fThis->setEaseControllers(controllers);
    return 0;
}

static PyMethodDef pyLeafController_Methods[] = {
    pyLeafController_hasKeys_method,
    pyLeafController_hasEaseControllers_method,
    pyLeafController_ExpandToKeyController_method,
    pyLeafController_CompactToLeafController_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_READ(LeafController, type, getType)
PY_PROPERTY_SETTER_MSG(LeafController, type, "To set the key type, use the keys setter")
PY_PROPERTY_GETSET_DECL(LeafController, type)

static PyGetSetDef pyLeafController_GetSet[] = {
    pyLeafController_type_getset,
    { _pycs("keys"), (getter)pyLeafController_getKeys,
        (setter)pyLeafController_setKeys, NULL, NULL },
    { _pycs("easeControllers"), (getter)pyLeafController_getEaseControllers,
        (setter)pyLeafController_setEaseControllers, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LeafController, plLeafController, "plLeafController wrapper")

PY_PLASMA_TYPE_INIT(LeafController) {
    pyLeafController_Type.tp_init = pyLeafController___init__;
    pyLeafController_Type.tp_new = pyLeafController_new;
    pyLeafController_Type.tp_methods = pyLeafController_Methods;
    pyLeafController_Type.tp_getset = pyLeafController_GetSet;
    pyLeafController_Type.tp_base = &pyController_Type;
    if (PyType_CheckAndReady(&pyLeafController_Type) < 0)
        return NULL;

    Py_INCREF(&pyLeafController_Type);
    return (PyObject*)&pyLeafController_Type;
}

PY_PLASMA_IFC_METHODS(LeafController, plLeafController)

}
