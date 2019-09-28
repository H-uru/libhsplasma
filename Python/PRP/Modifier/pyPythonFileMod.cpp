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

#include "pyPythonFileMod.h"

#include <PRP/Modifier/plPythonFileMod.h>
#include "pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(PythonFileMod, plPythonFileMod)

PY_METHOD_NOARGS(PythonFileMod, clearReceivers,
    "Remove all receivers from the Python File Mod")
{
    self->fThis->clearReceivers();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(PythonFileMod, clearParameters,
    "Remove all parameters from the Python File Mod")
{
    self->fThis->clearParameters();
    Py_RETURN_NONE;
}

PY_METHOD_VA(PythonFileMod, addReceiver,
    "Params: key\n"
    "Add a receiver to the Python File Mod")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return nullptr;
    }
    self->fThis->addReceiver(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(PythonFileMod, addParameter,
    "Params: parameter\n"
    "Add a parameter to the Python File Mod")
{
    pyPythonParameter* param;
    if (!PyArg_ParseTuple(args, "O", &param)) {
        PyErr_SetString(PyExc_TypeError, "addParameter expects a plPythonParameter");
        return nullptr;
    }
    if (!pyPythonParameter_Check((PyObject*)param)) {
        PyErr_SetString(PyExc_TypeError, "addParameter expects a plPythonParameter");
        return nullptr;
    }
    self->fThis->addParameter(*param->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyPythonFileMod_Methods[] = {
    pyPythonFileMod_clearReceivers_method,
    pyPythonFileMod_clearParameters_method,
    pyPythonFileMod_addReceiver_method,
    pyPythonFileMod_addParameter_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(PythonFileMod, receivers)
{
    PyObject* list = PyTuple_New(self->fThis->getReceivers().size());
    for (size_t i=0; i<self->fThis->getReceivers().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getReceivers()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(PythonFileMod, receivers, "To add receivers, use addReceiver")
PY_PROPERTY_GETSET_DECL(PythonFileMod, receivers)

PY_GETSET_GETTER_DECL(PythonFileMod, parameters)
{
    PyObject* list = PyTuple_New(self->fThis->getParameters().size());
    for (size_t i=0; i<self->fThis->getParameters().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPythonParameter_FromPythonParameter(self->fThis->getParameters()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(PythonFileMod, parameters, "To add parameters, use addParameter")
PY_PROPERTY_GETSET_DECL(PythonFileMod, parameters)

PY_PROPERTY_PATHLIKE(PythonFileMod, filename, getFilename, setFilename)

static PyGetSetDef pyPythonFileMod_GetSet[] = {
    pyPythonFileMod_filename_getset,
    pyPythonFileMod_receivers_getset,
    pyPythonFileMod_parameters_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(PythonFileMod, plPythonFileMod, "plPythonFileMod wrapper")

PY_PLASMA_TYPE_INIT(PythonFileMod)
{
    pyPythonFileMod_Type.tp_new = pyPythonFileMod_new;
    pyPythonFileMod_Type.tp_methods = pyPythonFileMod_Methods;
    pyPythonFileMod_Type.tp_getset = pyPythonFileMod_GetSet;
    pyPythonFileMod_Type.tp_base = &pyMultiModifier_Type;
    if (PyType_CheckAndReady(&pyPythonFileMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPythonFileMod_Type);
    return (PyObject*)&pyPythonFileMod_Type;
}

PY_PLASMA_IFC_METHODS(PythonFileMod, plPythonFileMod)
