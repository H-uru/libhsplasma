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

#include "pyAGAnim.h"

#include <PRP/Avatar/plAGAnim.h>
#include "pyAGApplicator.h"
#include "PRP/pyCreatable.h"
#include "PRP/Object/pySynchedObject.h"

PY_PLASMA_NEW(AGAnim, plAGAnim)

PY_METHOD_NOARGS(AGAnim, clearApplicators, "Remove all plAGApplicators from the anim")
{
    self->fThis->clearApplicators();
    Py_RETURN_NONE;
}

PY_METHOD_VA(AGAnim, addApplicator,
    "Params: applicator\n"
    "Add a plAGApplicator to the anim")
{
    pyAGApplicator* app;
    if (!PyArg_ParseTuple(args, "O", &app)) {
        PyErr_SetString(PyExc_TypeError, "addApplicator expects a plAGApplicator");
        return nullptr;
    }
    if (!pyAGApplicator_Check((PyObject*)app)) {
        PyErr_SetString(PyExc_TypeError, "addApplicator expects a plAGApplicator");
        return nullptr;
    }
    self->fThis->addApplicator(app->fThis);
    app->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(AGAnim, delApplicator,
    "Params: idx\n"
    "Delete a plAGApplicator from the anim")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delApplicator expects an int");
        return nullptr;
    }
    self->fThis->delApplicator(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyAGAnim_Methods[] = {
    pyAGAnim_clearApplicators_method,
    pyAGAnim_addApplicator_method,
    pyAGAnim_delApplicator_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(AGAnim, applicators)
{
    plAGAnim* anim = self->fThis;
    PyObject* list = PyTuple_New(anim->getApplicators().size());
    for (size_t i=0; i < anim->getApplicators().size(); i++)
        PyTuple_SET_ITEM(list, i, ICreate(anim->getApplicators()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(AGAnim, applicators, "To add applicators, use addApplicator()")
PY_PROPERTY_GETSET_DECL(AGAnim, applicators)

PY_PROPERTY(float, AGAnim, blend, getBlend, setBlend)
PY_PROPERTY(float, AGAnim, start, getStart, setStart)
PY_PROPERTY(float, AGAnim, end, getEnd, setEnd)
PY_PROPERTY(ST::string, AGAnim, name, getName, setName)

static PyGetSetDef pyAGAnim_GetSet[] = {
    pyAGAnim_blend_getset,
    pyAGAnim_start_getset,
    pyAGAnim_end_getset,
    pyAGAnim_name_getset,
    pyAGAnim_applicators_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AGAnim, plAGAnim, "plAGAnim wrapper")

PY_PLASMA_TYPE_INIT(AGAnim)
{
    pyAGAnim_Type.tp_new = pyAGAnim_new;
    pyAGAnim_Type.tp_methods = pyAGAnim_Methods;
    pyAGAnim_Type.tp_getset = pyAGAnim_GetSet;
    pyAGAnim_Type.tp_base = &pySynchedObject_Type;
    if (PyType_CheckAndReady(&pyAGAnim_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(AGAnim, "kBodyUnknown", plAGAnim::kBodyUnknown);
    PY_TYPE_ADD_CONST(AGAnim, "kBodyUpper", plAGAnim::kBodyUpper);
    PY_TYPE_ADD_CONST(AGAnim, "kBodyFull", plAGAnim::kBodyFull);
    PY_TYPE_ADD_CONST(AGAnim, "kBodyLower", plAGAnim::kBodyLower);
    PY_TYPE_ADD_CONST(AGAnim, "kBodyMax", plAGAnim::kBodyMax);

    Py_INCREF(&pyAGAnim_Type);
    return (PyObject*)&pyAGAnim_Type;
}

PY_PLASMA_IFC_METHODS(AGAnim, plAGAnim)
