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

#include "pyATCEaseCurves.h"

#include <PRP/Animation/plATCEaseCurves.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(SplineEaseCurve, plSplineEaseCurve)

PY_GETSET_GETTER_DECL(SplineEaseCurve, splineCoef)
{
    return Py_BuildValue("ffff", pyPlasma_convert(self->fThis->getSplineCoef(0)),
                                 pyPlasma_convert(self->fThis->getSplineCoef(1)),
                                 pyPlasma_convert(self->fThis->getSplineCoef(2)),
                                 pyPlasma_convert(self->fThis->getSplineCoef(3)));
}

PY_GETSET_SETTER_DECL(SplineEaseCurve, splineCoef)
{
    PY_PROPERTY_CHECK_NULL(splineCoef)
    if (!PyTuple_Check(value) || PyTuple_Size(value) != 4) {
        PyErr_SetString(PyExc_TypeError, "splineCoef should be a tuple of 4 floats");
        return -1;
    }
    for (size_t i=0; i<4; i++) {
        PyObject* itm = PyTuple_GetItem(value, i);
        if (!pyPlasma_check<float>(itm)) {
            PyErr_SetString(PyExc_TypeError, "splineCoef should be a tuple of 4 floats");
            return -1;
        }
        self->fThis->setSplineCoef(i, pyPlasma_get<float>(itm));
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(SplineEaseCurve, splineCoef)

static PyGetSetDef pySplineEaseCurve_GetSet[] = {
    pySplineEaseCurve_splineCoef_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SplineEaseCurve, plSplineEaseCurve, "plSplineEaseCurve wrapper")

PY_PLASMA_TYPE_INIT(SplineEaseCurve)
{
    pySplineEaseCurve_Type.tp_new = pySplineEaseCurve_new;
    pySplineEaseCurve_Type.tp_getset = pySplineEaseCurve_GetSet;
    pySplineEaseCurve_Type.tp_base = &pyATCEaseCurve_Type;
    if (PyType_CheckAndReady(&pySplineEaseCurve_Type) < 0)
        return nullptr;

    Py_INCREF(&pySplineEaseCurve_Type);
    return (PyObject*)&pySplineEaseCurve_Type;
}

PY_PLASMA_IFC_METHODS(SplineEaseCurve, plSplineEaseCurve)
