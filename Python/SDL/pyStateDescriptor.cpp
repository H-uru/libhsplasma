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

#include "pySDL.h"

#include <SDL/plStateDescriptor.h>

PY_PLASMA_DEALLOC(StateDescriptor)
PY_PLASMA_EMPTY_INIT(StateDescriptor)
PY_PLASMA_NEW(StateDescriptor, plStateDescriptor)

PY_PLASMA_REPR_DECL(StateDescriptor)
{
    return PyString_FromSTString(ST::format("<plStateDescriptor '{}'>", self->fThis->getName()));
}

PY_PLASMA_LENGTH_DECL(StateDescriptor)
{
    return self->fThis->getNumVars();
}

PY_PLASMA_SUBSCRIPT_DECL(StateDescriptor)
{
    if (pyPlasma_check<size_t>(key)) {
        size_t idx = pyPlasma_get<size_t>(key);
        if (self->fThis->getNumVars() <= idx) {
            PyErr_SetNone(PyExc_IndexError);
            return nullptr;
        }
        return pyVarDescriptor_FromVarDescriptor(self->fThis->get(idx));
    } else if (pyPlasma_check<ST::string>(key)) {
        plVarDescriptor* desc = self->fThis->get(pyPlasma_get<ST::string>(key));
        if (!desc) {
            PyErr_SetNone(PyExc_KeyError);
            return nullptr;
        }
        return pyVarDescriptor_FromVarDescriptor(desc);
    }

    PyErr_SetString(PyExc_TypeError, "StateDescriptor subscript should be an int or a string");
    return nullptr;
}

PY_PLASMA_ASS_SUBSCRIPT_DECL(StateDescriptor)
{
    if (!pyVarDescriptor_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "StateDescriptor subscript assignment expects a plVarDescriptor");
        return -1;
    }

    if (pyPlasma_check<size_t>(key)) {
        size_t idx = pyPlasma_get<size_t>(key);
        if (self->fThis->getNumVars() <= idx) {
            PyErr_SetNone(PyExc_IndexError);
            return -1;
        }

        self->fThis->set(idx, ((pyVarDescriptor*)value)->fThis);
        ((pyVarDescriptor*)value)->fPyOwned = false;
        return 0;
    } else if (pyPlasma_check<ST::string>(key)) {
        // Inserts the variable if it does not exist already
        ((pyVarDescriptor*)value)->fPyOwned = false;
        self->fThis->set(pyPlasma_get<ST::string>(key), ((pyVarDescriptor*)value)->fThis);
        return 0;
    }

    PyErr_SetString(PyExc_TypeError, "StateDescriptor subscript should be an int or a string");
    return -1;
}

PY_PLASMA_STR_DECL(StateDescriptor)
{
    return PyString_FromSTString(self->fThis->getName());
}

PY_METHOD_VA(StateDescriptor, addVariable,
    "Params: variable\n"
    "Adds the provided plVarDescriptor to this state descriptor")
{
    pyVarDescriptor* desc;
    if (!PyArg_ParseTuple(args, "O", &desc) || !pyVarDescriptor_Check((PyObject*)desc)) {
        PyErr_SetString(PyExc_TypeError, "addVariable expects a plVarDescriptor");
        return nullptr;
    }

    desc->fPyOwned = false;
    self->fThis->addVariable(desc->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(StateDescriptor, delVariable,
    "Params: variable\n"
    "Deletes the requested variable by name or index")
{
    Py_ssize_t idx;
    if (PyArg_ParseTuple(args, "n", &idx)) {
        if (self->fThis->getNumVars() <= size_t(idx)) {
            PyErr_SetNone(PyExc_IndexError);
            return nullptr;
        }

        self->fThis->delVariable(idx);
        Py_RETURN_NONE;
    }

    PyObject* str;
    if (PyErr_Clear(), PyArg_ParseTuple(args, "O", &str) && pyPlasma_check<ST::string>(str)) {
        self->fThis->delVariable(pyPlasma_get<ST::string>(str));
        Py_RETURN_NONE;
    }

    PyErr_SetString(PyExc_TypeError, "delVariable expects an int or a string");
    return nullptr;
}

PY_METHOD_NOARGS(StateDescriptor, clearVariables,
    "Removes all variable descriptors from this state descriptor")
{
    self->fThis->clearVariables();
    Py_RETURN_NONE;
}

static PyMethodDef pyStateDescriptor_Methods[] = {
    pyStateDescriptor_addVariable_method,
    pyStateDescriptor_delVariable_method,
    pyStateDescriptor_clearVariables_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(ST::string, StateDescriptor, name, getName, setName);
PY_PROPERTY(int, StateDescriptor, version, getVersion, setVersion);
PY_PROPERTY_RO(StateDescriptor, valid, isValid);

PY_GETSET_GETTER_DECL(StateDescriptor, variables)
{
    PyObject* tup = PyTuple_New(self->fThis->getNumVars());
    for (size_t i = 0; i < self->fThis->getNumVars(); ++i)
        PyTuple_SET_ITEM(tup, i, pyVarDescriptor_FromVarDescriptor(self->fThis->get(i)));
    return tup;
}

PY_PROPERTY_GETSET_RO_DECL(StateDescriptor, variables);

static PyGetSetDef pyStateDescriptor_GetSet[] = {
    pyStateDescriptor_name_getset,
    pyStateDescriptor_version_getset,
    pyStateDescriptor_valid_getset,
    pyStateDescriptor_variables_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(StateDescriptor, plStateDescriptor, "plStateDescriptor wrapper")
PY_PLASMA_TYPE_AS_MAPPING(StateDescriptor)

PY_PLASMA_TYPE_INIT(StateDescriptor)
{
    pyStateDescriptor_As_Mapping.mp_length = pyStateDescriptor_length;
    pyStateDescriptor_As_Mapping.mp_subscript = pyStateDescriptor_mp_subscript;
    pyStateDescriptor_As_Mapping.mp_ass_subscript = pyStateDescriptor_mp_ass_subscript;
    pyStateDescriptor_Type.tp_dealloc = pyStateDescriptor_dealloc;
    pyStateDescriptor_Type.tp_init = pyStateDescriptor___init__;
    pyStateDescriptor_Type.tp_new = pyStateDescriptor_new;
    pyStateDescriptor_Type.tp_repr = pyStateDescriptor_repr;
    pyStateDescriptor_Type.tp_as_mapping = &pyStateDescriptor_As_Mapping;
    pyStateDescriptor_Type.tp_str = pyStateDescriptor_str;
    pyStateDescriptor_Type.tp_methods = pyStateDescriptor_Methods;
    pyStateDescriptor_Type.tp_getset = pyStateDescriptor_GetSet;
    if (PyType_CheckAndReady(&pyStateDescriptor_Type) < 0)
        return nullptr;

    Py_INCREF(&pyStateDescriptor_Type);
    return (PyObject*)& pyStateDescriptor_Type;
}

PY_PLASMA_IFC_METHODS(StateDescriptor, plStateDescriptor)
