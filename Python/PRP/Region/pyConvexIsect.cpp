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

#include "pyVolumeIsect.h"

#include <PRP/Region/plVolumeIsect.h>
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix.h"

/* pyConvexIsect */

PY_PLASMA_NEW(ConvexIsect, plConvexIsect)

PY_METHOD_VA(ConvexIsect, addPlane,
    "Adds or updates a given plane\n"
    "Params: normal, position, or a plConvexIsect.SinglePlane")
{
    PyObject* normal;
    PyObject* position;
    PyObject* plane;
    if (PyArg_ParseTuple(args, "OO", &normal, &position) && pyVector3_Check(normal) &&
        pyVector3_Check(position)) {
        self->fThis->addPlane(*((pyVector3*)normal)->fThis, *((pyVector3*)position)->fThis);
        Py_RETURN_NONE;
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "O", &plane) && pySinglePlane_Check(plane)) {
        self->fThis->addPlane(*(((pySinglePlane*)plane)->fThis));
        Py_RETURN_NONE;
    } else {
        PyErr_SetString(PyExc_TypeError, "addPlane expects hsVector3, hsVector3, or a plConvexIsect.SinglePlane");
        return nullptr;
    }
}

PY_METHOD_VA(ConvexIsect, transform,
    "Calculates worldspace transformation for this volume\n"
    "Params: localToWorld, worldToLocal")
{
    PyObject* l2w;
    PyObject* w2l;
    if (!PyArg_ParseTuple(args, "OO", &l2w, &w2l) || !pyMatrix44_Check(l2w) || !pyMatrix44_Check(w2l)) {
        PyErr_SetString(PyExc_TypeError, "transform expects hsMatrix44, hsMatrix44");
        return nullptr;
    }
    self->fThis->transform(*((pyMatrix44*)l2w)->fThis, *((pyMatrix44*)w2l)->fThis);
    Py_RETURN_NONE;
}

PyMethodDef pyConvexIsect_Methods[] = {
    pyConvexIsect_addPlane_method,
    pyConvexIsect_transform_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(ConvexIsect, planes)
{
    PyObject* list = PyTuple_New(self->fThis->getPlanes().size());
    for (size_t i = 0; i < self->fThis->getPlanes().size(); i++)
        PyTuple_SET_ITEM(list, i, pySinglePlane_FromSinglePlane(self->fThis->getPlanes()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(ConvexIsect, planes, "To add planes, use addPlane")
PY_PROPERTY_GETSET_DECL(ConvexIsect, planes)

PyGetSetDef pyConvexIsect_GetSet[] = {
    pyConvexIsect_planes_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ConvexIsect, plConvexIsect, "plConvexIsect wrapper")

PY_PLASMA_TYPE_INIT(ConvexIsect)
{
    pyConvexIsect_Type.tp_new = pyConvexIsect_new;
    pyConvexIsect_Type.tp_methods = pyConvexIsect_Methods;
    pyConvexIsect_Type.tp_getset = pyConvexIsect_GetSet;
    pyConvexIsect_Type.tp_base = &pyVolumeIsect_Type;
    if (PyType_CheckAndReady(&pyConvexIsect_Type) < 0)
        return nullptr;

    /* SinglePlane class */
    PyDict_SetItemString(pyConvexIsect_Type.tp_dict, "SinglePlane",
        Init_pySinglePlane_Type());

    Py_INCREF(&pyConvexIsect_Type);
    return (PyObject*)&pyConvexIsect_Type;
}

PY_PLASMA_IFC_METHODS(ConvexIsect, plConvexIsect)

/* pySinglePlane */

PY_PLASMA_VALUE_DEALLOC(SinglePlane)
PY_PLASMA_EMPTY_INIT(SinglePlane)
PY_PLASMA_VALUE_NEW(SinglePlane, plConvexIsect::SinglePlane)

PY_PROPERTY(hsVector3, SinglePlane, norm, getNorm, setNorm)
PY_PROPERTY(hsVector3, SinglePlane, pos, getPos, setPos)
PY_PROPERTY(hsVector3, SinglePlane, worldNorm, getWorldNorm, setWorldNorm)
PY_PROPERTY(float, SinglePlane, dist, getDist, setDist)
PY_PROPERTY(float, SinglePlane, worldDist, getWorldDist, setWorldDist)

PyGetSetDef pySinglePlane_GetSet[] = {
    pySinglePlane_norm_getset,
    pySinglePlane_pos_getset,
    pySinglePlane_worldNorm_getset,
    pySinglePlane_dist_getset,
    pySinglePlane_worldDist_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SinglePlane, plConvexIsect::SinglePlane, "plConvexIsect::SinglePlane wrapper")

PY_PLASMA_TYPE_INIT(SinglePlane)
{
    pySinglePlane_Type.tp_dealloc = pySinglePlane_dealloc;
    pySinglePlane_Type.tp_init = pySinglePlane___init__;
    pySinglePlane_Type.tp_new = pySinglePlane_new;
    pySinglePlane_Type.tp_getset = pySinglePlane_GetSet;
    if (PyType_CheckAndReady(&pySinglePlane_Type) < 0)
        return nullptr;

    Py_INCREF(&pySinglePlane_Type);
    return (PyObject*)&pySinglePlane_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(SinglePlane, plConvexIsect::SinglePlane)
