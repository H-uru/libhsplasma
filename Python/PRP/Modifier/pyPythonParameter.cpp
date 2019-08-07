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
#include "PRP/KeyedObject/pyKey.h"
#include "Stream/pyStream.h"
#include "ResManager/pyResManager.h"

PY_PLASMA_VALUE_DEALLOC(PythonParameter)

PY_PLASMA_INIT_DECL(PythonParameter)
{
    PyObject* init = nullptr;

    if (PyArg_ParseTuple(args, "|O", &init)) {
        if (init == nullptr) {
            return 0;
        } else if (pyPythonParameter_Check(init)) {
            (*self->fThis) = *(((pyPythonParameter*)init)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects an optional plPythonParameter");
            return -1;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "__init__ expects an optional plPythonParameter");
        return -1;
    }

    return 0;
}

PY_PLASMA_VALUE_NEW(PythonParameter, plPythonParameter)

PY_METHOD_VA(PythonParameter, read,
    "Params: stream, mgr\n"
    "Reads this object from `stream`")
{
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plResManager");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plResManager");
        return nullptr;
    }
    self->fThis->read(stream->fThis, mgr->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(PythonParameter, write,
    "Params: stream, mgr\n"
    "Writes this object to `stream`")
{
    pyStream* stream;
    pyResManager* mgr;
    if (!PyArg_ParseTuple(args, "OO", &stream, &mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyResManager_Check((PyObject*)mgr)) {
        PyErr_SetString(PyExc_TypeError, "write expects hsStream, plResManager");
        return nullptr;
    }
    self->fThis->write(stream->fThis, mgr->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyPythonParameter_Methods[] = {
    pyPythonParameter_read_method,
    pyPythonParameter_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(unsigned int, PythonParameter, id, fID)
PY_PROPERTY_MEMBER(unsigned int, PythonParameter, valueType, fValueType)

PY_GETSET_GETTER_DECL(PythonParameter, value)
{
    switch (self->fThis->fValueType) {
    case plPythonParameter::kInt:
        return pyPlasma_convert(self->fThis->fIntValue);
    case plPythonParameter::kFloat:
        return pyPlasma_convert(self->fThis->fFloatValue);
    case plPythonParameter::kBoolean:
        return pyPlasma_convert(self->fThis->fBoolValue);
    case plPythonParameter::kString:
    case plPythonParameter::kAnimationName:
    case plPythonParameter::kGlobalSDLVar:
    case plPythonParameter::kSubtitle:
        return pyPlasma_convert(self->fThis->fStrValue);
    case plPythonParameter::kNone:
        Py_RETURN_NONE;
    default:
        return pyPlasma_convert(self->fThis->fObjKey);
    }
}

PY_GETSET_SETTER_DECL(PythonParameter, value)
{
    PY_PROPERTY_CHECK_NULL(value)

    switch (self->fThis->fValueType) {
    case plPythonParameter::kInt:
        if (!pyPlasma_check<int>(value)) {
            PyErr_SetString(PyExc_TypeError, "value should be an int");
            return -1;
        }
        self->fThis->fIntValue = pyPlasma_get<int>(value);
        return 0;
    case plPythonParameter::kFloat:
        if (!pyPlasma_check<float>(value)) {
            PyErr_SetString(PyExc_TypeError, "value should be a float");
            return -1;
        }
        self->fThis->fFloatValue = pyPlasma_get<float>(value);
        return 0;
    case plPythonParameter::kBoolean:
        if (!pyPlasma_check<bool>(value)) {
            PyErr_SetString(PyExc_TypeError, "value should be a boolean");
            return -1;
        }
        self->fThis->fBoolValue = pyPlasma_get<bool>(value);
        return 0;
    case plPythonParameter::kString:
    case plPythonParameter::kAnimationName:
    case plPythonParameter::kGlobalSDLVar:
    case plPythonParameter::kSubtitle:
        if (!pyPlasma_check<ST::string>(value)) {
            PyErr_SetString(PyExc_TypeError, "value should be a string");
            return -1;
        }
        self->fThis->fStrValue = pyPlasma_get<ST::string>(value);
        return 0;
    case plPythonParameter::kNone:
        PyErr_SetString(PyExc_RuntimeError, "cannot assign to a plPythonParameter whose type is kNone");
        return -1;
    default:
        if (!pyPlasma_check<plKey>(value)) {
            PyErr_SetString(PyExc_TypeError, "value should be a plKey");
            return -1;
        }
        self->fThis->fObjKey = pyPlasma_get<plKey>(value);
        return 0;
    }
}

PY_PROPERTY_GETSET_DECL(PythonParameter, value)

static PyGetSetDef pyPythonParameter_GetSet[] = {
    pyPythonParameter_id_getset,
    pyPythonParameter_valueType_getset,
    pyPythonParameter_value_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(PythonParameter, plPythonParameter, "plPythonParameter wrapper")

PY_PLASMA_TYPE_INIT(PythonParameter)
{
    pyPythonParameter_Type.tp_dealloc = pyPythonParameter_dealloc;
    pyPythonParameter_Type.tp_init = pyPythonParameter___init__;
    pyPythonParameter_Type.tp_new = pyPythonParameter_new;
    pyPythonParameter_Type.tp_methods = pyPythonParameter_Methods;
    pyPythonParameter_Type.tp_getset = pyPythonParameter_GetSet;
    if (PyType_CheckAndReady(&pyPythonParameter_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(PythonParameter, "kInt", plPythonParameter::kInt);
    PY_TYPE_ADD_CONST(PythonParameter, "kFloat", plPythonParameter::kFloat);
    PY_TYPE_ADD_CONST(PythonParameter, "kBoolean", plPythonParameter::kBoolean);
    PY_TYPE_ADD_CONST(PythonParameter, "kString", plPythonParameter::kString);
    PY_TYPE_ADD_CONST(PythonParameter, "kSceneObject", plPythonParameter::kSceneObject);
    PY_TYPE_ADD_CONST(PythonParameter, "kSceneObjectList", plPythonParameter::kSceneObjectList);
    PY_TYPE_ADD_CONST(PythonParameter, "kActivator", plPythonParameter::kActivator);
    PY_TYPE_ADD_CONST(PythonParameter, "kResponder", plPythonParameter::kResponder);
    PY_TYPE_ADD_CONST(PythonParameter, "kDynamicText", plPythonParameter::kDynamicText);
    PY_TYPE_ADD_CONST(PythonParameter, "kGUIDialog", plPythonParameter::kGUIDialog);
    PY_TYPE_ADD_CONST(PythonParameter, "kExcludeRegion", plPythonParameter::kExcludeRegion);
    PY_TYPE_ADD_CONST(PythonParameter, "kAnimation", plPythonParameter::kAnimation);
    PY_TYPE_ADD_CONST(PythonParameter, "kAnimationName", plPythonParameter::kAnimationName);
    PY_TYPE_ADD_CONST(PythonParameter, "kBehavior", plPythonParameter::kBehavior);
    PY_TYPE_ADD_CONST(PythonParameter, "kMaterial", plPythonParameter::kMaterial);
    PY_TYPE_ADD_CONST(PythonParameter, "kGUIPopUpMenu", plPythonParameter::kGUIPopUpMenu);
    PY_TYPE_ADD_CONST(PythonParameter, "kGUISkin", plPythonParameter::kGUISkin);
    PY_TYPE_ADD_CONST(PythonParameter, "kWaterComponent", plPythonParameter::kWaterComponent);
    PY_TYPE_ADD_CONST(PythonParameter, "kSwimCurrentInterface", plPythonParameter::kSwimCurrentInterface);
    PY_TYPE_ADD_CONST(PythonParameter, "kClusterComponent", plPythonParameter::kClusterComponent);
    PY_TYPE_ADD_CONST(PythonParameter, "kMaterialAnimation", plPythonParameter::kMaterialAnimation);
    PY_TYPE_ADD_CONST(PythonParameter, "kGrassShaderComponent", plPythonParameter::kGrassShaderComponent);
    PY_TYPE_ADD_CONST(PythonParameter, "kGlobalSDLVar", plPythonParameter::kGlobalSDLVar);
    PY_TYPE_ADD_CONST(PythonParameter, "kSubtitle", plPythonParameter::kSubtitle);
    PY_TYPE_ADD_CONST(PythonParameter, "kBlowerComponent", plPythonParameter::kBlowerComponent);
    PY_TYPE_ADD_CONST(PythonParameter, "kNone", plPythonParameter::kNone);

    Py_INCREF(&pyPythonParameter_Type);
    return (PyObject*)&pyPythonParameter_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(PythonParameter, plPythonParameter)
