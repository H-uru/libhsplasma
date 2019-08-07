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

#include "pyKeys.h"

#include <PRP/Animation/hsKeys.h>
#include "Math/pyGeometry3.h"

PY_PLASMA_EMPTY_INIT(ScaleKey)
PY_PLASMA_NEW(ScaleKey, hsScaleKey)

PY_PROPERTY_MEMBER(hsVector3, ScaleKey, inTan, fInTan)
PY_PROPERTY_MEMBER(hsVector3, ScaleKey, outTan, fOutTan)

PY_GETSET_GETTER_DECL(ScaleKey, value)
{
    return Py_BuildValue("OO",
                         pyPlasma_convert(self->fThis->fS),
                         pyPlasma_convert(self->fThis->fQ));
}

PY_GETSET_SETTER_DECL(ScaleKey, value)
{
    PY_PROPERTY_CHECK_NULL(value)
    if (!PyTuple_Check(value) || PyTuple_Size(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "value should be a tuple (hsVector3, hsQuat)");
        return -1;
    }
    PyObject* s = PyTuple_GetItem(value, 0);
    PyObject* q = PyTuple_GetItem(value, 1);
    if (!pyVector3_Check(s) || !pyQuat_Check(q)) {
        PyErr_SetString(PyExc_TypeError, "value should be a tuple (hsVector3, hsQuat)");
        return -1;
    }
    self->fThis->fS = pyPlasma_get<hsVector3>(s);
    self->fThis->fQ = pyPlasma_get<hsQuat>(q);
    return 0;
}

PY_PROPERTY_GETSET_DECL(ScaleKey, value)

static PyGetSetDef pyScaleKey_GetSet[] = {
    pyScaleKey_inTan_getset,
    pyScaleKey_outTan_getset,
    pyScaleKey_value_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ScaleKey, hsScaleKey, "hsScaleKey wrapper")

PY_PLASMA_TYPE_INIT(ScaleKey)
{
    pyScaleKey_Type.tp_init = pyScaleKey___init__;
    pyScaleKey_Type.tp_new = pyScaleKey_new;
    pyScaleKey_Type.tp_getset = pyScaleKey_GetSet;
    pyScaleKey_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_CheckAndReady(&pyScaleKey_Type) < 0)
        return nullptr;

    Py_INCREF(&pyScaleKey_Type);
    return (PyObject*)&pyScaleKey_Type;
}

PY_PLASMA_IFC_METHODS(ScaleKey, hsScaleKey)
