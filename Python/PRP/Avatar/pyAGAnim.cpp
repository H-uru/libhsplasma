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

extern "C" {

PY_PLASMA_NEW(AGAnim, plAGAnim)

PY_METHOD_NOARGS(AGAnim, clearApplicators, "Remove all plAGApplicators from the anim") {
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
        return NULL;
    }
    if (!pyAGApplicator_Check((PyObject*)app)) {
        PyErr_SetString(PyExc_TypeError, "addApplicator expects a plAGApplicator");
        return NULL;
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
        return NULL;
    }
    self->fThis->delApplicator(idx);
    Py_RETURN_NONE;
}

static PyObject* pyAGAnim_getApps(pyAGAnim* self, void*) {
    plAGAnim* anim = self->fThis;
    PyObject* list = PyList_New(anim->getApplicators().size());
    for (size_t i=0; i < anim->getApplicators().size(); i++)
        PyList_SET_ITEM(list, i, ICreate(anim->getApplicators()[i]));
    return list;
}

static int pyAGAnim_setApps(pyAGAnim* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add applicators, use addApplicator()");
    return -1;
}

static PyMethodDef pyAGAnim_Methods[] = {
    pyAGAnim_clearApplicators_method,
    pyAGAnim_addApplicator_method,
    pyAGAnim_delApplicator_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(float, AGAnim, blend, getBlend, setBlend)
PY_PROPERTY(float, AGAnim, start, getStart, setStart)
PY_PROPERTY(float, AGAnim, end, getEnd, setEnd)
PY_PROPERTY(plString, AGAnim, name, getName, setName)

static PyGetSetDef pyAGAnim_GetSet[] = {
    pyAGAnim_blend_getset,
    pyAGAnim_start_getset,
    pyAGAnim_end_getset,
    pyAGAnim_name_getset,
    { _pycs("applicators"), (getter)pyAGAnim_getApps, (setter)pyAGAnim_setApps, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AGAnim, plAGAnim, "plAGAnim wrapper")

PY_PLASMA_TYPE_INIT(AGAnim) {
    pyAGAnim_Type.tp_new = pyAGAnim_new;
    pyAGAnim_Type.tp_methods = pyAGAnim_Methods;
    pyAGAnim_Type.tp_getset = pyAGAnim_GetSet;
    pyAGAnim_Type.tp_base = &pySynchedObject_Type;
    if (PyType_Ready(&pyAGAnim_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(AGAnim, "kBodyUnknown", plAGAnim::kBodyUnknown);
    PY_TYPE_ADD_CONST(AGAnim, "kBodyUpper", plAGAnim::kBodyUpper);
    PY_TYPE_ADD_CONST(AGAnim, "kBodyFull", plAGAnim::kBodyFull);
    PY_TYPE_ADD_CONST(AGAnim, "kBodyLower", plAGAnim::kBodyLower);
    PY_TYPE_ADD_CONST(AGAnim, "kBodyMax", plAGAnim::kBodyMax);

    Py_INCREF(&pyAGAnim_Type);
    return (PyObject*)&pyAGAnim_Type;
}

PY_PLASMA_IFC_METHODS(AGAnim, plAGAnim)

}
